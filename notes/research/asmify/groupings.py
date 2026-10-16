#!/usr/bin/env python3
"""Generate family-level sections for notes/file-groupings.md covering every
hand-written assembly translation unit.  Run from the project root; prints the
sections to stdout (append them to the notes file, or diff against it).

A family is a run of objects that Sony numbered from one stem (SMD_00 ...
SMD_15), or, for LIBHMD primitive drivers, the objects sharing the upper half
of the unit-type code (the flag bits).  Singletons get a section of their own
so that every assembly member is covered.
"""
import collections, glob, json, os, re, sys

sys.path.insert(0, os.path.dirname(os.path.abspath(__file__)))
import annotate  # noqa: E402  (HMD flag vocabulary)

RESULTS = 'build/asmify/results.json'
GTE_NAMES = {op.upper() for op in annotate.GTE_OPS} | {'DCPL'}


def family_key(lib, name):
    if lib == 'libhmd' and re.fullmatch(r'[0-9a-f]{8}', name):
        return 'block_' + name[:4]
    return re.sub(r'_[0-9]+(_[0-9]+)?$', '', name)


def instruction_stream(path):
    ops, sect = [], 'text'
    for ln in open(path):
        s = ln.split('#')[0].strip()
        if s.startswith(('.data', '.rdata', '.sdata', '.bss', '.sbss')):
            sect = 'data'; continue
        if s.startswith('.text'):
            sect = 'text'; continue
        if not s or s.endswith(':') or s.startswith(('.', '/', '*')):
            continue
        if sect == 'text':
            ops.append(s)
    return ops


def markers(path):
    text = open(path).read()
    prev, gte1, sw_s, def_s = [], 0, set(), set()
    priv = jrx = ldra = False
    for ln in text.split('\n'):
        s = ln.split('#')[0].strip()
        if not s or s.startswith(('.', '/', '*')) or s.endswith(':'):
            continue
        m = s.split()[0]; args = s[len(m):].strip()
        if m in GTE_NAMES:
            n = 0
            for q in reversed(prev):
                if q == 'nop': n += 1
                else: break
            before = prev[-(n + 1)] if len(prev) > n else ''
            if n == 1 and before not in ('mtc2', 'ctc2'):
                gte1 += 1
        if m == 'sw' and re.match(r'\$(s[0-7]),\s*-?0x?[0-9A-Fa-f]*\(\$sp\)', args):
            sw_s.add(re.match(r'\$(s[0-7])', args).group(1))
        elif m not in ('lw', 'jr', 'beqz', 'bnez', 'blez', 'bgtz', 'bltz', 'bgez', 'beq', 'bne', 'sw', 'sh', 'sb', 'swc2', 'mtc2', 'ctc2') and args:
            d = re.match(r'\$(s[0-7])\b', args)
            if d: def_s.add(d.group(1))
        if m == 'jr' and args != '$ra': jrx = True
        if m == 'lw' and args.startswith('$ra') and '($sp)' not in args: ldra = True
        if m in ('syscall', 'mfc0', 'mtc0', 'rfe', 'break'): priv = True
        prev.append(m)
    return {
        '`$at` used as a scratch register': '$at' in text,
        'GTE commands with a single hazard nop': gte1 > 0,
        'callee-saved registers written without being saved': bool(def_s - sw_s),
        'privileged or trap instructions': priv,
        'jump through a register other than `$ra`': jrx,
        'return address loaded from a buffer': ldra,
    }


def annotated(path):
    return any(re.match(r'^\t\S.*\t# ', ln) for ln in open(path))


def main():
    members = {m['id']: m for m in json.load(open(annotate.MEMBERS))}
    outcomes = {x['tu']: x['outcome'] for x in json.load(open(RESULTS))}
    ids = {}
    for f in glob.glob('build/libraries/verified/*.json'):
        r = json.load(open(f))
        if r.get('form') == 'assembly':
            ids[os.path.dirname(r['source'])] = os.path.basename(f)[:-5]
    rows = []
    for tu in sorted(glob.glob('src/libraries/*/*/tu.json')):
        parts = json.load(open(tu))['parts']
        if not (len(parts) == 1 and parts[0]['path'].endswith('.s')):
            continue
        d = os.path.dirname(tu)
        lib, dirname = d.split('/')[2], d.split('/')[3]
        ordinal, name = dirname.split('-', 1)
        rec = members[f'{lib}/{dirname}']
        path = os.path.join(d, parts[0]['path'])
        rows.append({
            'lib': lib, 'dir': d, 'ordinal': int(ordinal), 'name': name, 'path': path,
            'libname': os.path.basename(rec['input']), 'obj': rec['member'],
            'symbols': parts[0]['symbols'], 'id': ids.get(d, '?'),
            'family': family_key(lib, name), 'outcome': outcomes.get(d, '?'),
            'stream': instruction_stream(path), 'markers': markers(path), 'annotated': annotated(path),
        })
    fams = collections.OrderedDict()
    for r in sorted(rows, key=lambda r: (r['lib'], r['ordinal'])):
        fams.setdefault((r['lib'], r['family']), []).append(r)
    out = []
    for (lib, fam), ms in fams.items():
        first, last = ms[0], ms[-1]
        if len(ms) == 1:
            out.append(f"## {first['libname']} — {first['obj']} (ordinal {first['ordinal']})")
        else:
            ords = sorted(m['ordinal'] for m in ms)
            contiguous = ords == list(range(ords[0], ords[-1] + 1))
            span = f"ordinals {ords[0]}–{ords[-1]}" if contiguous else 'ordinals ' + ', '.join(map(str, ords))
            out.append(f"## {first['libname']} — {first['obj']} … {last['obj']} ({span})")
        out.append('')
        dirs = f"`{first['dir']}/` … `{last['dir']}/`" if len(ms) > 1 else f"`{first['dir']}/`"
        out.append(f"- Form: hand-written assembly, one `.s` translation unit per object ({dirs}); "
                   f"{len(ms)} member{'s' if len(ms) > 1 else ''}, "
                   f"{sum(len(m['symbols']) for m in ms)} function{'s' if sum(len(m['symbols']) for m in ms) != 1 else ''}.")
        if lib == 'libhmd' and fam.startswith('block_'):
            bits = int(fam[6:], 16) << 16
            words = [w for b, w in annotate.HMD_FLAG_WORDS if b & bits]
            out.append(f"- HMD primitive drivers whose unit-type flag bits are 0x{bits:08x}"
                       f"{' (' + ', '.join(words) + ')' if words else ' (no flags: the basic drivers)'}; "
                       f"the low half of each code selects the primitive shape (see the file headers).")
        # The ledger parser (tools/agent/fileGroupings.ts) reads a group as the
        # `- <symbol> (m|s|?)` bullets that follow a line starting with "Members".
        out.append('Members (byte-exact assembly, one object each):')
        for m in ms:
            for s in m['symbols']:
                shared = '' if len(m['symbols']) == 1 else '; shares the object with ' + ', '.join(f'`{x}`' for x in m['symbols'] if x != s)
                out.append(f"- {s} (m) — `{m['obj']}`, ordinal {m['ordinal']}, target `{m['id']}`{shared}")
        if len(ms) > 1:
            classes = collections.OrderedDict()
            for m in ms:
                key = ' '.join(op.split()[0] for op in m['stream'])
                classes.setdefault(key, []).append(m)
            if len(classes) == len(ms):
                out.append(f"- Family structure: {len(ms)} variants with distinct instruction streams; "
                           "they are edited copies of one another, not operand-only variants of a template.")
            else:
                desc = '; '.join('{' + ', '.join(f'`{s}`' for m in c for s in m['symbols']) + '}' for c in classes.values())
                out.append(f"- Family structure: {len(ms)} variants over {len(classes)} distinct instruction streams "
                           f"(members in one stream differ only in operands): {desc}.")
        found = collections.Counter()
        for m in ms:
            for k, v in m['markers'].items():
                if v: found[k] += 1
        noreorder = sum(m['outcome'] == 'noreorder-file' for m in ms)
        ev = [f"{k} in {n}/{len(ms)}" for k, n in found.most_common()]
        text = '; '.join(ev) if ev else (
            'no instruction-level marker; classed by the GTE hazard-nop convention '
            '(0 or 1 nop before GTE commands, where the SDK C macros emit 2) and by family')
        if noreorder:
            text += f"; whole-file `.set noreorder` reproduces the bytes in {noreorder}/{len(ms)}"
        out.append('- Hand-written evidence: ' + text + '.')
        out.append(f"- Membership evidence: `library-input/redux/original-members.json`, entr{'ies' if len(ms) > 1 else 'y'} "
                   + ', '.join(f"`{m['lib']}/{os.path.basename(m['dir'])}`" for m in ms) + '.')
        out.append(f"- Verification: {'all ' if len(ms) > 1 else ''}{len(ms)} member{'s' if len(ms) > 1 else ''} byte-exact as {'assembly TUs' if len(ms) > 1 else 'an assembly TU'} "
                   "(`npm run library -- check --member ID`); verified records carry `form: \"assembly\"`.")
        ann = [s for m in ms if m['annotated'] for s in m['symbols']]
        out.append('- Annotation: header and INLINE_A.H spelling pass applied; '
                   + (f"semantic comments and named labels on {', '.join(f'`{s}`' for s in ann)}"
                      + ('; siblings pending' if len(ann) < sum(len(m['symbols']) for m in ms) else '')
                      if ann else 'semantic comments and named labels pending') + '.')
        out.append('')
    print('\n'.join(out).rstrip())


if __name__ == '__main__':
    main()
