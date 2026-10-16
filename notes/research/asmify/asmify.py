#!/usr/bin/env python3
"""Translate spimdisasm member dumps of hand-written members into natural gas
reorder-mode .s source, assemble with the project toolchain, and verify
byte + relocation identity against the original object.

Usage: asmify.py [member ...]   (default: all members in asm_members.json)
Writes out/<lib>/<tu>/<name>.s and results.json in the scratchpad.
"""
import re, json, os, sys, subprocess, struct, collections, glob

ROOT = '/home/dave/Documents/code/psyq-decomp'
SCR = os.path.dirname(os.path.abspath(__file__))
OUT = os.path.join(ROOT, 'build', 'asmify', 'out')
TMP = os.path.join(ROOT, 'build', 'asmify', 'tmp')
os.makedirs(OUT, exist_ok=True); os.makedirs(TMP, exist_ok=True)
AS = ['mips-linux-gnu-as', '-march=r3000', '-mtune=r3000', '-EL', '-G0', '-I', ROOT + '/include']

GTE_MACROS = set(re.findall(r'^\.macro\s+(\w+)', open(ROOT + '/include/gte_macros.inc').read(), re.M))
GTE_CMDS = GTE_MACROS - {'cop2op'}
BRANCH = {'b', 'beq', 'bne', 'beqz', 'bnez', 'blez', 'bgtz', 'bltz', 'bgez', 'bltzal', 'bgezal', 'j', 'jal', 'jr', 'jalr',
          'beql', 'bnel', 'bc2t', 'bc2f', 'bc0t', 'bc0f', 'bal'}
LOADS = {'lw', 'lh', 'lhu', 'lb', 'lbu', 'lwl', 'lwr'}
STORES = {'sw', 'sh', 'sb', 'swl', 'swr'}
REGS = ['$zero','$at','$v0','$v1','$a0','$a1','$a2','$a3','$t0','$t1','$t2','$t3','$t4','$t5','$t6','$t7','$s0','$s1','$s2','$s3','$s4','$s5','$s6','$s7','$t8','$t9','$k0','$k1','$gp','$sp','$fp','$ra']
INS_RE = re.compile(r'^\s*/\* ([0-9A-F]+) ([0-9A-F]+) ([0-9A-F]{8}) \*/\s+(\S+)\s*(.*?)\s*(/\*.*)?$')
DATA_RE = re.compile(r'^\s*/\* [0-9A-F ]+\*/\s*(\.\w+)\s*(.*?)\s*$')

# ---------------------------------------------------------------- ELF
def read_elf(path):
    d = open(path, 'rb').read()
    shoff, = struct.unpack_from('<I', d, 0x20); shentsize, shnum, shstrndx = struct.unpack_from('<HHH', d, 0x2E)
    sh = [struct.unpack_from('<IIIIIIIIII', d, shoff + i * shentsize) for i in range(shnum)]
    def strtab(idx):
        off, size = sh[idx][4], sh[idx][5]; return d[off:off + size]
    shstr = strtab(shstrndx)
    def nm(tab, i): return tab[i:tab.index(b'\0', i)].decode()
    names = [nm(shstr, s[0]) for s in sh]
    secs = {}
    for i, s in enumerate(sh):
        name, typ, flags, addr, off, size = names[i], s[1], s[2], s[3], s[4], s[5]
        if typ == 8: secs[name] = dict(size=size, data=None, align=s[8])
        elif typ == 1: secs[name] = dict(size=size, data=d[off:off + size], align=s[8])
    syms = []
    symi = names.index('.symtab') if '.symtab' in names else None
    if symi is not None:
        st = strtab(sh[symi][6]); off, size = sh[symi][4], sh[symi][5]
        for i in range(size // 16):
            n, v, sz, info, other, shndx = struct.unpack_from('<IIIBBH', d, off + i * 16)
            syms.append(dict(name=nm(st, n), value=v, size=sz, bind=info >> 4, type=info & 15, shndx=shndx))
    relocs = collections.defaultdict(list)
    for i, s in enumerate(sh):
        if s[1] != 9: continue  # SHT_REL
        target = names[s[7]]; off, size = s[4], s[5]
        for j in range(size // 8):
            r_off, r_info = struct.unpack_from('<II', d, off + j * 8)
            sym = syms[r_info >> 8]
            tgt = names[sym['shndx']] if sym['type'] == 3 else sym['name']
            relocs[target].append((r_off, r_info & 0xff, tgt))
    return dict(secs=secs, syms=syms, relocs=relocs, secnames=names)

def words(b): return list(struct.unpack('<%dI' % (len(b) // 4), b[:len(b) // 4 * 4]))

# ---------------------------------------------------------------- parse member.s
def parse_member(path):
    """Return list of sections: dict(name, align, items). item kinds: func(name) endfunc(name) label(name, alt)
    insn(mn, ops, word, off) data(directive, args) dlabel(name)."""
    secs = []; cur = None
    for raw in open(path, errors='replace'):
        line = raw.rstrip('\n')
        s = line.strip()
        if not s or s.startswith('/*') and s.endswith('*/') and not INS_RE.match(line) and not DATA_RE.match(line):
            continue
        if s.startswith('.include'): continue
        if s.startswith('.set'): continue
        if s.startswith('.section'):
            cur = dict(name=s.split()[1], align=None, items=[]); secs.append(cur); continue
        if s.startswith('.align'):
            cur['align'] = int(s.split()[1]); continue
        if s.startswith('nonmatching'): continue
        m = re.match(r'^(glabel|endlabel|alabel|dlabel|enddlabel|jlabel|ehlabel)\s+(\S+)', s)
        if m:
            k, n = m.groups()
            if k == 'glabel': cur['items'].append(dict(kind='func', name=n))
            elif k == 'endlabel': cur['items'].append(dict(kind='endfunc', name=n))
            elif k == 'alabel': cur['items'].append(dict(kind='label', name=n, alt=True))
            elif k in ('jlabel', 'ehlabel'): cur['items'].append(dict(kind='label', name=n, alt=False))
            elif k == 'dlabel': cur['items'].append(dict(kind='dlabel', name=n))
            continue
        m = re.match(r'^(\.L[0-9A-Fa-f_]+):$', s)
        if m: cur['items'].append(dict(kind='label', name=m.group(1), alt=False)); continue
        m = INS_RE.match(line)
        if m and not m.group(4).startswith('.'):
            off, vram, w, mn, ops = m.group(1), m.group(2), m.group(3), m.group(4), m.group(5)
            ops = re.sub(r'\s*/\*.*$', '', ops).strip()
            wv = int.from_bytes(bytes.fromhex(w), 'little')
            if mn == 'move' and (wv & 0x3f) == 0x25 and (wv >> 26) == 0:
                rd = (wv >> 11) & 31; rs = (wv >> 21) & 31
                mn = 'or'; ops = f'{REGS[rd]}, {REGS[rs]}, $zero'
            cur['items'].append(dict(kind='insn', mn=mn, ops=ops, word=wv, off=int(vram, 16))); continue
        m = DATA_RE.match(line)
        if m: cur['items'].append(dict(kind='data', d=m.group(1), args=m.group(2))); continue
        raise ValueError(f'unparsed line in {path}: {line}')
    return secs

def synthesize_labels(secs):
    defined = set()
    for sec in secs:
        for it in sec['items']:
            if it['kind'] in ('func', 'label', 'dlabel'): defined.add(it['name'])
    refs = set()
    for sec in secs:
        for it in sec['items']:
            if it['kind'] == 'insn': refs.update(re.findall(r'\b([DBTL]_[0-9A-F]{8})\b', it['ops']))
            if it['kind'] == 'data': refs.update(re.findall(r'\b([DBTL]_[0-9A-F]{8})\b', it['args']))
    for name in sorted(refs - defined):
        addr = int(name[2:], 16)
        for sec in secs:
            if sec['name'] != '.text': continue
            for i, it in enumerate(sec['items']):
                if it['kind'] == 'insn' and it['off'] == addr:
                    # an existing label right before this instruction? alias the reference to it
                    j = i - 1; alias = None
                    while j >= 0 and sec['items'][j]['kind'] in ('label', 'dlabel', 'func'):
                        if sec['items'][j]['kind'] in ('label', 'func'): alias = sec['items'][j]['name']
                        j -= 1
                    if alias:
                        for s2 in secs:
                            for it2 in s2['items']:
                                if it2['kind'] == 'insn': it2['ops'] = re.sub(r'\b' + name + r'\b', alias, it2['ops'])
                                if it2['kind'] == 'data': it2['args'] = re.sub(r'\b' + name + r'\b', alias, it2['args'])
                    else:
                        sec['items'].insert(i, dict(kind='label', name=name, alt=False))
                    defined.add(name); break
            if name in defined: break

# ---------------------------------------------------------------- natural rewriting
def is_branch(u): return u['kind'] == 'insn' and u['mn'] in BRANCH
def is_nop(u): return u['kind'] == 'insn' and u['mn'] == 'nop'
def is_gte_cmd(u): return u['kind'] == 'insn' and u['mn'] in GTE_CMDS

def uses_at(items): return any(u['kind'] == 'insn' and re.search(r'\$at\b', u['ops']) for u in items)

def fold_pairs(units, allow_at_macros):
    """Fold lui/%lo pairs and immediates into gas macros. Only adjacent plain instruction pairs that are not
    branches or slot instructions."""
    out = []; i = 0
    while i < len(units):
        u = units[i]; v = units[i + 1] if i + 1 < len(units) else None
        if u['kind'] == 'insn' and v and v['kind'] == 'insn' and not u.get('slot') and not v.get('slot') and not is_branch(v) \
                and not u.get('hoisted') and not v.get('hoisted'):
            m1 = re.match(r'^(\$\w+), %hi\((.+)\)$', u['ops']) if u['mn'] == 'lui' else None
            if m1:
                r, sym = m1.groups()
                m2 = re.match(r'^(\$\w+), %lo\((.+)\)\((\$\w+)\)$', v['ops'])
                if m2 and v['mn'] in LOADS and m2.group(2) == sym and m2.group(1) == r and m2.group(3) == r:
                    out.append(dict(kind='insn', mn=v['mn'], ops=f'{r}, {sym}', word=None, words=[u['word'], v['word']], off=u['off'], folded=[u, v])); i += 2; continue
                if m2 and v['mn'] in STORES and m2.group(2) == sym and r == '$at' and m2.group(3) == '$at' and allow_at_macros:
                    out.append(dict(kind='insn', mn=v['mn'], ops=f'{m2.group(1)}, {sym}', word=None, words=[u['word'], v['word']], off=u['off'], folded=[u, v])); i += 2; continue
                m3 = re.match(r'^(\$\w+), (\$\w+), %lo\((.+)\)$', v['ops'])
                if m3 and v['mn'] == 'addiu' and m3.group(3) == sym and m3.group(1) == r and m3.group(2) == r:
                    out.append(dict(kind='insn', mn='la', ops=f'{r}, {sym}', word=None, words=[u['word'], v['word']], off=u['off'], folded=[u, v])); i += 2; continue
            m1 = re.match(r'^(\$\w+), \((-?0x[0-9A-Fa-f]+|\d+) >> 16\)$', u['ops']) if u['mn'] == 'lui' else None
            if m1:
                r, val = m1.group(1), int(m1.group(2), 0)
                m2 = re.match(r'^(\$\w+), (\$\w+), \((-?0x[0-9A-Fa-f]+|\d+) & 0xFFFF\)$', v['ops'])
                if m2 and v['mn'] == 'ori' and m2.group(1) == r and m2.group(2) == r and int(m2.group(3), 0) == val:
                    out.append(dict(kind='insn', mn='li', ops=f'{r}, {val:#x}', word=None, words=[u['word'], v['word']], off=u['off'], folded=[u, v])); i += 2; continue
        if u['kind'] == 'insn' and not u.get('folded'):
            m = re.match(r'^(\$\w+), \$zero, (-?0x[0-9A-Fa-f]+|-?\d+)$', u['ops'])
            if u['mn'] in ('addiu', 'ori') and m:
                nu = dict(u); nu['mn'] = 'li'; nu['ops'] = f'{m.group(1)}, {m.group(2)}'; nu['folded'] = [u]; out.append(nu); i += 1; continue
            m = re.match(r'^(\$\w+), \((-?0x[0-9A-Fa-f]+|\d+) >> 16\)$', u['ops'])
            if u['mn'] == 'lui' and m and int(m.group(2), 0) & 0xFFFF == 0 and int(m.group(2), 0) != 0:
                nu = dict(u); nu['mn'] = 'li'; nu['ops'] = f'{m.group(1)}, {int(m.group(2), 0):#x}'; nu['folded'] = [u]; out.append(nu); i += 1; continue
            m = re.match(r'^(\$\w+), (\$\w+), \$zero$', u['ops'])
            if u['mn'] == 'addu' and m:
                nu = dict(u); nu['mn'] = 'move'; nu['ops'] = f'{m.group(1)}, {m.group(2)}'; nu['folded'] = [u]; out.append(nu); i += 1; continue
            m = re.match(r'^(\$\w+), \$zero, (\$\w+)$', u['ops'])
            if u['mn'] == 'subu' and m:
                nu = dict(u); nu['mn'] = 'negu'; nu['ops'] = f'{m.group(1)}, {m.group(2)}'; nu['folded'] = [u]; out.append(nu); i += 1; continue
        out.append(u); i += 1
    return out

def unfold(u):
    """Revert a folded unit to its explicit instructions."""
    res = []
    for o in u['folded']:
        o = dict(o); o.pop('folded', None); res.append(o)
    return res

def build_units(items, fn_offsets, text_end):
    """Turn a text section's items into reorder-mode units."""
    units = []
    at_funcs = set()
    # per-function $at usage
    cur = None; buf = collections.defaultdict(list)
    for it in items:
        if it['kind'] == 'func': cur = it['name']
        if cur: buf[cur].append(it)
    for fn, its in buf.items():
        if uses_at(its): at_funcs.add(fn)
    i = 0; cur = None
    while i < len(items):
        it = items[i]
        if it['kind'] in ('func', 'endfunc', 'label', 'dlabel', 'data'):
            if it['kind'] == 'func': cur = it['name']
            units.append(dict(it)); i += 1; continue
        # instruction
        if is_nop(it):
            nxt = next((x for x in items[i + 1:] if x['kind'] == 'insn'), None)
            prev = next((x for x in reversed(units) if x['kind'] == 'insn'), None)
            # keep nops explicit before GTE commands (gas never inserts those) -- hazard nops elsewhere are dropped
            # trailing nops of a function (after an unconditional jump + slot) are padding
            rest = items[i + 1:]
            rest_insns = [x for x in rest if x['kind'] == 'insn']
            trailing = all(is_nop(x) for x in rest_insns) or (rest and rest[0]['kind'] == 'endfunc') or \
                       all(is_nop(x) for x in itertools_takewhile_insns(rest))
            if trailing:
                units.append(dict(kind='pad', word=0, off=it['off'])); i += 1; continue
            labelled = len(units) > 0 and units[-1]['kind'] in ('label', 'func', 'dlabel')
            if (nxt is not None and is_gte_cmd(nxt)) or labelled:
                units.append(dict(kind='insn', mn='nop', ops='', word=0, off=it['off'], explicit=True)); i += 1; continue
            units.append(dict(kind='dropnop', word=0, off=it['off'])); i += 1; continue
        if is_branch(it):
            # find slot instruction (next item must be insn)
            j = i + 1
            slot = items[j] if j < len(items) and items[j]['kind'] == 'insn' else None
            b = dict(it)
            if slot is None:
                units.append(b); i += 1; continue
            if is_nop(slot):
                b['slot'] = None; units.append(b); i += 2; continue
            s = dict(slot); s['hoisted'] = True
            b['slot'] = s
            units.append(s); units.append(b); i += 2; continue
        units.append(dict(it)); i += 1
    return units, at_funcs

def itertools_takewhile_insns(rest):
    out = []
    for x in rest:
        if x['kind'] == 'endfunc': break
        if x['kind'] == 'insn': out.append(x)
    return out

# ---------------------------------------------------------------- emission
def clean_ops(ops):
    ops = re.sub(r'\((-?0x[0-9A-Fa-f]+|\d+) >> 16\)', lambda m: f'{(int(m.group(1), 0) >> 16) & 0xffff:#x}', ops)
    ops = re.sub(r'\((-?0x[0-9A-Fa-f]+|\d+) & 0xFFFF\)', lambda m: f'{int(m.group(1), 0) & 0xffff:#x}', ops)
    ops = re.sub(r'\b0x0\(', '0(', ops)
    ops = re.sub(r', 0x0$', ', 0', ops)
    return ops

def fmt_insn(u):
    return f"\t{u['mn']}\t{clean_ops(u['ops'])}".rstrip()

def emit_text(units, at_funcs, globals_, sec_align, label_map, noreorder_all=False, orig_items=None):
    lines = []
    lines.append('\t.text')
    lines.append(f'\t.align\t{sec_align}')
    if noreorder_all:
        lines.append('\t.set\tnoreorder')
    cur = None; in_noat = False; depth = 0
    seq = units if not noreorder_all else orig_items
    def subst(ops):
        for a, b in label_map.items(): ops = re.sub(r'(?<![\w.])' + re.escape(a) + r'(?![\w])', b, ops)
        return ops
    for idx, u in enumerate(seq):
        k = u['kind']
        if k == 'func':
            cur = u['name']; lines.append('')
            if cur in globals_: lines.append(f'\t.globl\t{cur}')
            lines.append(f'\t.ent\t{cur}')
            lines.append(f'{cur}:')
            if cur in at_funcs: lines.append('\t.set\tnoat'); in_noat = True
        elif k == 'endfunc':
            if in_noat: lines.append('\t.set\tat'); in_noat = False
            lines.append(f"\t.end\t{u['name']}")
        elif k == 'label':
            lines.append(f"{label_map.get(u['name'], u['name'])}:")
        elif k == 'dlabel':
            if u['name'] in globals_: lines.append(f"\t.globl\t{u['name']}")
            lines.append(f"{u['name']}:")
        elif k == 'data':
            lines.append(f"\t{u['d']}\t{subst(u['args'])}")
        elif k == 'pad':
            if noreorder_all: lines.append('\tnop')
        elif k == 'dropnop':
            if noreorder_all: lines.append('\tnop')
        elif k == 'align':
            lines.append(f"\t.align\t{u['n']}")
        elif k == 'insn':
            uu = dict(u); uu['ops'] = subst(u['ops'])
            if noreorder_all:
                lines.append(fmt_insn(uu)); continue
            if u.get('hoisted') and u.get('owner_island'):
                continue  # emitted inside the island of its branch
            if u.get('nr_start') and depth == 0:
                lines.append('\t.set\tnoreorder'); depth = 1
            lines.append(fmt_insn(uu))
            if u.get('island'):
                s = u.get('slot')
                if s is None: lines.append('\tnop')
                else:
                    ss = dict(s); ss['ops'] = subst(s['ops']); lines.append(fmt_insn(ss))
            if u.get('nr_end') and depth == 1:
                lines.append('\t.set\treorder'); depth = 0
    if noreorder_all: lines.append('\t.set\treorder')
    return lines

def emit_data(sec, globals_, label_map, commons=()):
    lines = ['', f"\t.section\t{sec['name']}" if sec['name'] not in ('.data', '.bss', '.rodata', '.sdata', '.sbss') else f"\t{sec['name']}" if sec['name'] in ('.data', '.bss') else f"\t.section\t{sec['name']}"]
    lines.append(f"\t.align\t{sec['align'] if sec['align'] is not None else 2}")
    skip = False
    for it in sec['items']:
        if it['kind'] == 'dlabel':
            n = it['name']; skip = n in commons
            if skip: continue
            if n in globals_: lines.append(f'\t.globl\t{n}')
            lines.append(f'{n}:')
        elif it['kind'] == 'data':
            if skip: continue
            lines.append(f"\t{it['d']}\t{it['args']}")
        elif it['kind'] == 'label':
            lines.append(f"{it['name']}:")
    return lines

# ---------------------------------------------------------------- assemble + compare
def assemble(src_text, tag):
    src = src_text
    src = re.sub(r'^(\s*)move\t(\$\w+), (\$\w+)$', r'\1addu\t\2, \3, $zero', src, flags=re.M)  # harness move-addu rewrite
    sp = os.path.join(TMP, tag + '.s'); op = os.path.join(TMP, tag + '.o')
    open(sp, 'w').write(src)
    r = subprocess.run(AS + [sp, '-o', op], capture_output=True, text=True)
    if r.returncode != 0: return None, r.stderr
    return read_elf(op), r.stderr

PROGRAM = ('.text', '.data', '.rodata', '.rdata', '.sdata', '.bss', '.sbss')
def sext16(v): return v - 0x10000 if v & 0x8000 else v

def canon_relocs(elf, sec):
    """Canonical relocation list for a section: (offset, type, target) where target is
    ('import', name, addend) for undefined symbols or (section, absolute offset) for defined ones.
    HI16/LO16 pairing follows the harness rule. Returns (list, masked_data)."""
    data = bytearray(elf['secs'][sec]['data'] or b'')
    syms = {s['name']: s for s in elf['syms']}
    secnames = {s['name'] for s in elf['syms'] if s['type'] == 3}
    rl = elf['relocs'].get(sec, [])
    out = []; masked = bytearray(data)
    def word(off): return struct.unpack_from('<I', data, off)[0]
    for i, (off, typ, tgt) in enumerate(rl):
        w = word(off)
        if typ == 4: add = (w & 0x3ffffff) * 4; masked[off:off + 4] = struct.pack('<I', w & ~0x3ffffff)
        elif typ == 2: add = w; masked[off:off + 4] = b'\0\0\0\0'
        elif typ == 6:
            # find pairing HI16 (same target, same base register) before this LO16, after the previous LO16 of same target
            base = (w >> 21) & 31; add = sext16(w & 0xffff)
            for j in range(i - 1, -1, -1):
                o2, t2, g2 = rl[j]
                if t2 == 6 and g2 == tgt: break
                if t2 == 5 and g2 == tgt and ((word(o2) >> 16) & 31) == base:
                    add += (word(o2) & 0xffff) * 0x10000; break
            masked[off:off + 4] = struct.pack('<I', w & 0xffff0000)
        elif typ == 5:
            add = (w & 0xffff) * 0x10000
            for j in range(i + 1, len(rl)):
                o2, t2, g2 = rl[j]
                if t2 == 6 and g2 == tgt: add += sext16(word(o2) & 0xffff); break
            masked[off:off + 4] = struct.pack('<I', w & 0xffff0000)
        else: add = sext16(w & 0xffff); masked[off:off + 4] = struct.pack('<I', w & 0xffff0000)
        if tgt in secnames or tgt.startswith('.'):
            target = (tgt, add)
        else:
            s_ = syms.get(tgt)
            if s_ is None or s_['shndx'] == 0: target = ('import', tgt, add)
            elif s_['shndx'] == 0xfff2: target = ('common', tgt, add)
            else:
                secname = [n for n, x in elf['secs'].items()]  # placeholder
                target = (section_of(elf, s_), s_['value'] + add)
        out.append((off, typ, target))
    return sorted(out), bytes(masked)

def section_of(elf, sym):
    i = sym['shndx']
    return 'ABS' if i == 0xfff1 else 'COMMON' if i == 0xfff2 else 'UND' if i == 0 else elf['secnames'][i]

def sig(elf):
    out = {}
    for name, s in elf['secs'].items():
        if name in PROGRAM and s['size'] > 0:
            rel, masked = canon_relocs(elf, name)
            out[name] = dict(size=s['size'], data=masked if s['data'] is not None else None, relocs=rel, kind='zero' if s['data'] is None else 'init')
    out['globals'] = sorted((s['name'], section_of(elf, s) if s['shndx'] not in (0, 0xfff1, 0xfff2) else 'UND', s['value']) for s in elf['syms'] if s['bind'] != 0 and s['type'] != 4 and not s['name'].endswith('.NON_MATCHING'))
    return out

def compare(o, r):
    """Return None if identical under canonical relocations, else a dict describing the first difference."""
    for name in PROGRAM:
        a = o.get(name); b = r.get(name)
        if (a is None) != (b is None): return dict(what='section-presence', sec=name, orig=a is not None, mine=b is not None)
        if a is None: continue
        if a['kind'] != b['kind'] or a['size'] != b['size']:
            if name == '.text':
                wa, wb = words(a['data']), words(b['data'])
                for k in range(min(len(wa), len(wb))):
                    if wa[k] != wb[k]: return dict(what='text-word', k=k, orig=wa, mine=wb)
                return dict(what='text-length', k=min(len(wa), len(wb)), orig=wa, mine=wb)
            return dict(what='size', sec=name, orig=a['size'], mine=b['size'])
        if a['data'] is not None and a['data'] != b['data']:
            if name == '.text':
                wa, wb = words(a['data']), words(b['data'])
                for k in range(min(len(wa), len(wb))):
                    if wa[k] != wb[k]: return dict(what='text-word', k=k, orig=wa, mine=wb)
            return dict(what='data-bytes', sec=name, orig=a['data'][:48].hex(), mine=b['data'][:48].hex())
        if a['relocs'] != b['relocs']:
            da = [x for x in a['relocs'] if x not in b['relocs']][:6]; db = [x for x in b['relocs'] if x not in a['relocs']][:6]
            return dict(what='relocs', sec=name, orig_only=da, mine_only=db)
    if o['globals'] != r['globals']:
        return dict(what='globals', orig_only=[x for x in o['globals'] if x not in r['globals']][:6], mine_only=[x for x in r['globals'] if x not in o['globals']][:6])
    return None

# ---------------------------------------------------------------- alignment of assembled output to units
def expected_sequence(units):
    """Expected output order of instruction-producing units assuming every hoist swaps and no gas nops."""
    seq = []
    i = 0
    while i < len(units):
        u = units[i]
        if u['kind'] == 'data':
            if u['d'] == '.word':
                for tok in u['args'].split(','):
                    tok = tok.strip()
                    try: v = int(tok, 0) & 0xffffffff
                    except ValueError: v = 0
                    seq.append(dict(kind='insn', mn='.word', ops=tok, word=v, synthetic=True))
            else:
                seq.append(dict(kind='insn', mn=u['d'], ops=u['args'], word=-1, synthetic=True))  # unalignable
            i += 1; continue
        if u['kind'] == 'insn':
            if u.get('hoisted'):
                b = units[i + 1]
                if b.get('island'):
                    seq.append(b); seq.append(u)
                else:
                    seq.append(b); seq.append(u)
                i += 2; continue
            seq.append(u)
            if u.get('island') and u.get('slot') is None: seq.append(dict(kind='insn', mn='nop', ops='', word=0, synthetic=True))
        i += 1
    return seq

def unit_words(u):
    if u.get('words'): return list(u['words'])
    return [u['word']]

def weq(a, b):
    """Instruction identity ignoring branch displacement, jump index and 16-bit immediate fields of relocatable forms."""
    if a == b: return True
    op = a >> 26
    if op != (b >> 26): return False
    if op in (1, 4, 5, 6, 7, 20, 21, 22, 23) or (op == 0x10 and ((a >> 16) & 0x1f) in (8,)) or (op == 0x12 and ((a >> 21) & 0x1f) == 8):
        return (a & 0xffff0000) == (b & 0xffff0000)
    if op in (2, 3): return True
    if op in (0x0f, 0x09, 0x08, 0x0d, 0x23, 0x2b, 0x21, 0x25, 0x20, 0x24, 0x29, 0x28, 0x32, 0x3a):  # lui/addiu/addi/ori/loads/stores: relocatable immediates
        return (a & 0xffff0000) == (b & 0xffff0000)
    return False

def align_output(seq, R, upto=None):
    """Map output word index -> unit (None for a gas-inserted nop), walking R up to index `upto`.
    Handles gas-inserted nops, refused swaps (exp [B,S] vs R [S,B,...]) and unexpected swaps (exp [P,B] vs R [B,P])."""
    owner = []; i = 0; j = 0
    exp = []
    for u in seq:
        for w in unit_words(u): exp.append((u, w))
    limit = len(R) if upto is None else min(len(R), upto + 1)
    while j < limit:
        if i < len(exp) and weq(exp[i][1], R[j]):
            owner.append(exp[i][0]); i += 1; j += 1; continue
        if R[j] == 0:
            owner.append(None); j += 1; continue
        if i + 1 < len(exp) and j + 1 < len(R) and weq(exp[i + 1][1], R[j]) and weq(exp[i][1], R[j + 1]):
            # either refused swap (exp[i] is the branch) or unexpected swap (exp[i+1] is the branch)
            owner.append(exp[i + 1][0]); owner.append(exp[i][0]); i += 2; j += 2; continue
        if os.environ.get('DEBUG'):
            def desc(u): return f"{u['mn']} {u['ops']}" if u['kind']=='insn' else u['kind']
            print(f"ALIGN FAIL at i={i} j={j}: exp={[ (f'{w:08x}', desc(u)) for u,w in exp[i:i+4] ]} R={[f'{w:08x}' for w in R[j:j+4]]}")
        return None
    return owner

# ---------------------------------------------------------------- main per-member driver
def process(member, info, verbose=False):
    tu = info['tu']; lib = info['lib']
    name = os.path.basename(tu).split('-', 1)[1]
    ms = f'{ROOT}/build/libraries/disassembly/{member}/member.s'
    opath = glob.glob(f'{ROOT}/build/libraries/originals/{member}/*.o')[0]
    orig = read_elf(opath); osig = sig(orig)
    globals_ = {s['name'] for s in orig['syms'] if s['bind'] == 1 and s['shndx'] != 0}
    commons = {s['name']: (s['size'], s['value']) for s in orig['syms'] if s['shndx'] == 0xfff2}
    secs = parse_member(ms)
    text = next(s for s in secs if s['name'] == '.text')
    synthesize_labels(secs)
    others = [s for s in secs if s['name'] != '.text']
    # section alignment: largest power of two <= 16 dividing the original text size
    tsize = orig['secs']['.text']['size']
    sec_align = max(k for k in (2, 3, 4) if tsize % (1 << k) == 0)
    # label renaming: .L00000xxx -> .L<n>
    label_map = {}; n = 0
    for it in text['items']:
        if it['kind'] == 'label' and it['name'].startswith('.L'):
            n += 1; label_map[it['name']] = f'.L{n}'
    units, _ = build_units(text['items'], None, None)
    # inter-function padding -> .align
    text_base = next(u['off'] for u in text['items'] if u['kind'] == 'insn')
    units = insert_aligns(units, tsize, text_base)
    units = fold_pairs(units, allow_at_macros=True)
    # functions that still use $at explicitly after folding must not use $at-needing store macros
    at_funcs = set(); cur = None
    for u in units:
        if u['kind'] == 'func': cur = u['name']
        if u['kind'] == 'insn' and cur and re.search(r'\$at\b', u['ops']): at_funcs.add(cur)
    units = fix_at_macros(units, at_funcs)
    relink_slots(units)
    uses_gte = any(u['kind'] == 'insn' and (u['mn'] in GTE_MACROS or u['mn'] in ('lwc2', 'swc2', 'mfc2', 'mtc2', 'cfc2', 'ctc2')) for u in text['items'])
    header = [f'/* {lib}/{os.path.basename(tu)}: {", ".join(info["functions"])} */']
    if any(u['kind'] == 'insn' and u['mn'] in GTE_MACROS for u in text['items']): header.append('\t.include\t"gte_macros.inc"')
    data_lines = []
    for s in others: data_lines += emit_data(s, globals_, label_map, commons)
    for n, (size, align) in commons.items(): data_lines.append(f'\t.comm\t{n}, {size}, {align}')

    stats = dict(explicit_nops=0, islands=0, pair_islands=0, unfolds=0, iterations=0)
    outcome = None; src = None
    for it in range(400):
      try:
          stats['iterations'] = it + 1
          lines = header + emit_text(units, at_funcs, globals_, sec_align, label_map) + data_lines + ['']
          src = '\n'.join(lines)
          elf, err = assemble(src, member)
          if elf is None:
              outcome = 'ASM-ERROR'; stats['error'] = err.strip()[:300]; break
          diff = compare(osig, sig(elf))
          if diff is None:
              outcome = 'reorder'; break
          if diff['what'] not in ('text-word', 'text-length'):
              outcome = 'DIFF:' + diff['what']; stats['diff'] = {k: (v if not isinstance(v, list) or len(v) < 10 else v[:10]) for k, v in diff.items()}; break
          O = diff['orig']; R = diff['mine']
          k = next((i for i in range(min(len(O), len(R))) if not weq(O[i], R[i])), min(len(O), len(R)))
          if k == min(len(O), len(R)) and len(O) == len(R):
              outcome = 'DIFF:immediates-only'; stats['diff'] = dict(k=diff['k'], orig=f"{O[diff['k']]:08x}", mine=f"{R[diff['k']]:08x}"); break
          seq = expected_sequence(units)
          owner = align_output(seq, R, upto=k + 1)
          if owner is None:
              outcome = 'ALIGN-FAIL'; stats['diff'] = dict(k=k, orig=[f'{w:08x}' for w in O[max(0,k-3):k+4]], mine=[f'{w:08x}' for w in R[max(0,k-3):k+4]]); break
          ok = repair(units, owner, k, O, R, stats)
          if not ok and os.environ.get('DEBUG'):
              def desc(u): return None if u is None else (f"{u['mn']} {u['ops']}" + (' [hoisted]' if u.get('hoisted') else '') + (' [island]' if u.get('island') else '') if u['kind']=='insn' else u['kind'])
              print(f"REPAIR FAIL k={k}: O={[f'{w:08x}' for w in O[max(0,k-2):k+3]]} R={[f'{w:08x}' for w in R[max(0,k-2):k+3]]} owners={[desc(owner[i]) if i < len(owner) else '?' for i in range(max(0,k-2),k+2)]}")
          if not ok:
              outcome = 'REPAIR-FAIL'; stats['diff'] = dict(k=k, orig=[f'{w:08x}' for w in O[max(0,k-3):k+4]], mine=[f'{w:08x}' for w in R[max(0,k-3):k+4]]); break
      except Exception as e:
        outcome = 'EXC:' + repr(e)[:120]; break
    stats['reorder_form'] = outcome if outcome == 'reorder' else None
    if outcome == 'reorder' and (stats['islands'] or stats['pair_islands']):
        outcome = 'reorder-with-islands'
    if outcome != 'reorder':
        # fallback: whole-file noreorder, verbatim
        vu = verbatim_units(text['items'])
        at2 = set(); cur = None
        for u in vu:
            if u['kind'] == 'func': cur = u['name']
            if u['kind'] == 'insn' and cur and re.search(r'\$at\b', u['ops']): at2.add(cur)
        vu = fix_at_macros(vu, at2)
        lines = header + emit_text(vu, at2, globals_, sec_align, label_map, noreorder_all=True, orig_items=vu) + data_lines + ['']
        src2 = '\n'.join(lines)
        elf, err = assemble(src2, member + '_nr')
        if elf is not None and compare(osig, sig(elf)) is None:
            stats['fallback_outcome'] = outcome; outcome = 'noreorder-file'; src = src2
        else:
            stats['fallback_error'] = (err or '').strip()[:300] if elf is None else str(compare(osig, sig(elf)))[:400]
            outcome = 'FAIL(' + outcome + ')'
    od = os.path.join(OUT, lib, os.path.basename(tu)); os.makedirs(od, exist_ok=True)
    open(os.path.join(od, name + '.s'), 'w').write(src)
    return dict(member=member, tu=tu, lib=lib, outcome=outcome, nops_orig=sum(1 for u in text['items'] if is_nop(u)), ninstr=sum(1 for u in text['items'] if u['kind'] == 'insn'), **stats)

def verbatim_units(items):
    """Units for the whole-file noreorder form: every original instruction in place, macros folded
    except in delay slots."""
    out = []; prev_branch = False
    for it in items:
        u = dict(it)
        if u['kind'] == 'insn':
            if prev_branch: u['slot'] = True
            prev_branch = u['mn'] in BRANCH
        out.append(u)
    return fold_pairs(out, allow_at_macros=True)

def insert_aligns(units, tsize, text_base):
    """Replace runs of padding nops with .align when the alignment reproduces exactly that many words;
    otherwise keep them as explicit nops. Section-end padding beyond the section alignment stays explicit."""
    out = []; i = 0
    sec_align = max(k for k in (2, 3, 4) if tsize % (1 << k) == 0)
    while i < len(units):
        u = units[i]
        if u['kind'] == 'pad':
            j = i
            while j < len(units) and units[j]['kind'] in ('pad', 'endfunc'): j += 1
            run = [x for x in units[i:j] if x['kind'] == 'pad']; N = len(run)
            start = run[0]['off'] - text_base; end = start + 4 * N
            for x in units[i:j]:
                if x['kind'] == 'endfunc': out.append(x)
            nxt = units[j] if j < len(units) else None
            if nxt is None:
                produced = ((-start) % (1 << sec_align)) // 4
                for _ in range(N - produced): out.append(dict(kind='insn', mn='nop', ops='', word=0, off=None, explicit=True))
            else:
                chosen = None
                for n in (4, 3):
                    if end % (1 << n) == 0 and ((-start) % (1 << n)) // 4 == N: chosen = n; break
                if chosen: out.append(dict(kind='align', n=chosen))
                else:
                    for _ in range(N): out.append(dict(kind='insn', mn='nop', ops='', word=0, off=None, explicit=True))
            i = j; continue
        out.append(u); i += 1
    return out

def relink_slots(units):
    for i, u in enumerate(units):
        if u['kind'] == 'insn' and u['mn'] in BRANCH and u.get('slot') is not None:
            if i > 0 and units[i - 1].get('hoisted'): u['slot'] = units[i - 1]

def fix_at_macros(units, at_funcs):
    out = []; cur = None
    for u in units:
        if u['kind'] == 'func': cur = u['name']
        if u['kind'] == 'insn' and u.get('folded') and cur in at_funcs and u['mn'] in STORES and len(u['folded']) == 2:
            out += unfold(u); continue
        out.append(u)
    return out

def is_br(u): return u is not None and u['kind'] == 'insn' and u['mn'] in BRANCH

def repair(units, owner, k, O, R, stats):
    """Mutate units so the next assembly moves past position k. Returns False if no rule applies."""
    ok = O[k] if k < len(O) else None; rk = R[k] if k < len(R) else None
    prev_owner = owner[k - 1] if k > 0 else None
    cur_owner = owner[k] if k < len(owner) else None
    nxt_owner = owner[k + 1] if k + 1 < len(owner) else None
    def idx(u): return next(i for i, x in enumerate(units) if x is u)
    def island(b):
        b['island'] = True; b['nr_start'] = True; b['nr_end'] = True
        if b.get('slot') is not None: b['slot']['owner_island'] = True
        stats['islands'] += 1
    def insert_pos(u):
        # an explicit nop meant to precede a branch must go before its hoisted slot instruction
        if is_br(u) and u.get('slot') is not None and u['slot'].get('hoisted') and not u.get('island'):
            i = idx(u['slot'])
        else:
            i = idx(u)
        # and before any labels attached to that instruction (gas would place the label after a hazard nop)
        while i > 0 and units[i - 1]['kind'] in ('label', 'dlabel'): i -= 1
        return i
    # Case A: original has a nop here, mine has an instruction
    if ok == 0 and rk not in (0, None):
        if is_br(prev_owner) and not prev_owner.get('island'):
            # original slot is empty but gas swapped something in
            if prev_owner.get('slot') is not None: return False
            island(prev_owner); return True
        if cur_owner is None: return False
        units.insert(insert_pos(cur_owner), dict(kind='insn', mn='nop', ops='', word=0, off=None, explicit=True)); stats['explicit_nops'] += 1; return True
    # Case B: mine has a gas nop here, original has an instruction
    if rk == 0 and ok not in (0, None):
        if is_br(prev_owner) and not prev_owner.get('island'):
            if prev_owner.get('slot') is None: return False
            island(prev_owner); return True
        if is_br(nxt_owner) and not nxt_owner.get('island'):
            # hazard nop caused by the hoisted slot instruction (or by the branch itself) -> island with explicit slot
            island(nxt_owner)
            if nxt_owner.get('slot') is None and prev_owner is not None:
                prev_owner['nr_start'] = True  # keep X adjacent to the branch
            return True
        if prev_owner is not None and nxt_owner is not None and prev_owner['kind'] == 'insn' and nxt_owner['kind'] == 'insn':
            if prev_owner.get('nr_end'): prev_owner['nr_end'] = False
            else: prev_owner['nr_start'] = True; stats['pair_islands'] += 1
            nxt_owner['nr_end'] = True; return True
        return False
    # Case C: both instructions, different
    if ok not in (0, None) and rk not in (0, None):
        if is_br(cur_owner) and not cur_owner.get('island') and k + 1 < len(O) and k + 1 < len(R) and weq(O[k + 1], rk) and weq(O[k], R[k + 1]):
            # gas swapped the preceding instruction into an originally empty slot
            if cur_owner.get('slot') is not None: return False
            island(cur_owner); return True
        if cur_owner is not None and cur_owner.get('hoisted') and is_br(nxt_owner) and not nxt_owner.get('island'):
            # gas refused the swap: S, B, nop ; original B, S
            island(nxt_owner); return True
        if cur_owner is not None and cur_owner.get('folded'):
            i = idx(cur_owner); units[i:i + 1] = unfold(cur_owner); stats['unfolds'] += 1; return True
        return False
    return False

if __name__ == '__main__':
    am = json.load(open(os.path.join(SCR, 'asm_members.json')))
    sel = sys.argv[1:] or list(am)
    results = []
    for m in sel:
        if m not in am:
            # allow tu-dir suffix match
            cands = [x for x, v in am.items() if v['tu'].endswith(m)]
            if not cands: print('unknown', m); continue
            m = cands[0]
        try:
            r = process(m, am[m])
        except Exception as e:
            import traceback; r = dict(member=m, tu=am[m]['tu'], lib=am[m]['lib'], outcome='EXC:' + repr(e)[:200], tb=traceback.format_exc()[-600:])
        results.append(r)
        if len(sel) <= 5: print(json.dumps(r, indent=1))
    json.dump(results, open(os.environ.get('RESULTS', os.path.join(ROOT, 'build', 'asmify', 'results.json')), 'w'), indent=1)
    c = collections.Counter(r['outcome'].split('(')[0] if r['outcome'].startswith('FAIL') else r['outcome'] for r in results)
    print('OUTCOMES:', dict(c))
