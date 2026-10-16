#!/usr/bin/env python3
"""Mechanical annotation pass over the hand-written assembly translation units.

Run from the project root.  For every one-part assembly TU under src/libraries:

  1. GTE spelling: `.include "gte_macros.inc"` becomes `.include "inline_a.inc"`
     and the GTE command mnemonics take the names of Sony's INLINE_A.H
     (RTPT, NCLIP, MVMVA sf,mx,v,cv,lm ...).  Encodings are unchanged.
  2. Header: the translator's one-line banner is replaced by the header shape
     settled on 2026-10-15 (see src/libraries/libgte/108-smd_00/smd_00.s):
     original library and object name, the SDK prototype of every function,
     and a "Register use" table seeded with the argument registers.  Files
     whose first line already starts with "/* LIB" keep their header.

Neither step changes an instruction, so every member must still verify:
    npm run check-all

Usage:  python3 notes/research/asmify/annotate.py            # rewrite all
        python3 notes/research/asmify/annotate.py --dry-run libgte/64-cmb_00 ...
"""
import glob, json, os, re, sys

ROOT = os.getcwd()
SDK_INCLUDE = 'library-input/converted/include'
MEMBERS = 'library-input/redux/original-members.json'

GTE_OPS = ['rtps', 'rtpt', 'dpcl', 'dpcs', 'dpct', 'intpl', 'ncs', 'nct', 'ncds', 'ncdt',
           'nccs', 'ncct', 'cdp', 'cc', 'nclip', 'avsz3', 'avsz4', 'mvmva', 'sqr', 'op',
           'gpf', 'gpl']
SONY_NAME = {op: op.upper() for op in GTE_OPS}
SONY_NAME['dpcl'] = 'DCPL'
OP_RE = re.compile(r'^\t(' + '|'.join(GTE_OPS) + r')(?=[\s#]|$)(.*)$')

# ---------------------------------------------------------------- SDK prototypes

def scan_prototypes(text, note, protos, header):
    for m in re.finditer(r'(?:extern\s+)?((?:unsigned|signed|const|struct|volatile)?\s*[A-Za-z_]\w*'
                         r'(?:\s+[A-Za-z_]\w*)?\s*\**)\s*([A-Za-z_]\w*)\s*\(([^()]*)\)\s*;', text):
        ret, name, args = m.group(1), m.group(2), m.group(3)
        ret = ' '.join(ret.split())
        args = ' '.join(args.split()).replace('u _long', 'u_long')
        if not ret or (len(ret.split()) == 1 and ret in ('return', 'sizeof', 'if', 'while', 'else', 'define', 'extern')):
            continue
        if name not in protos:
            protos[name] = {'ret': re.sub(r'^extern\s+', '', ret), 'args': args, 'note': note, 'header': header}
    # K&R declaration lists:  PACKET *a(), *b(), *c();
    for m in re.finditer(r'\n\s*((?:unsigned|struct)?\s*[A-Za-z_]\w*)\s*((?:\*?\s*[A-Za-z_]\w*\s*\(\s*\)\s*,\s*)+'
                         r'\*?\s*[A-Za-z_]\w*\s*\(\s*\)\s*);', text):
        ret = ' '.join(m.group(1).split())
        for d in m.group(2).split(','):
            d = d.strip()
            star = ' *' if d.startswith('*') else ''
            name = re.sub(r'[\*\s\(\)]', '', d)
            if name and name not in protos:
                protos[name] = {'ret': ret + star, 'args': None, 'note': note, 'header': header}


def load_prototypes():
    protos = {}
    headers = sorted(glob.glob(os.path.join(SDK_INCLUDE, '*.h')))
    for h in headers:
        raw = open(h, errors='replace').read()
        stripped = re.sub(r'//.*', '', re.sub(r'/\*.*?\*/', ' ', raw, flags=re.S))
        scan_prototypes(stripped, '', protos, os.path.basename(h))
    for h in headers:
        raw = open(h, errors='replace').read()
        comments = '\n'.join(re.findall(r'/\*(.*?)\*/', raw, flags=re.S))
        scan_prototypes(comments, 'declared only inside a comment block', protos, os.path.basename(h))
    return protos

# ---------------------------------------------------------------- HMD unit types

HMD_FLAG_WORDS = [(0x01000000, 'shared'), (0x00200000, 'semi-trans'), (0x00100000, 'back-face'),
                  (0x00080000, 'active-div'), (0x00040000, 'nonLight'), (0x00020000, 'fog'),
                  (0x00010000, 'div')]
HMD_FLAG_MASK = sum(b for b, _ in HMD_FLAG_WORDS)
HMD_SYNONYMS = {'tri': 'triangle', 'gour': 'gouraud', 'tex': 'texture', 'noLgt': 'nonLight',
                'stp': 'semi-trans', 'shrd': 'shared', 'back-f': 'back-face'}


def load_hmd_types():
    types = {}
    for ln in open(os.path.join(SDK_INCLUDE, 'libhmd.h'), errors='replace'):
        m = re.match(r'#define\s+(Gs\w+)\s+0x([0-9a-fA-F]{8})\s*(?:/\*(.*?)\*/)?', ln)
        if m and m.group(2).lower() != 'ffffffff':
            words = [HMD_SYNONYMS.get(w, w) for w in (m.group(3) or '').split()]
            types.setdefault(int(m.group(2), 16), (m.group(1), words))
    return types


def describe_hmd_type(code, types):
    """Return (define name or None, description words) for a GsU_ unit type."""
    if code in types:
        return types[code]
    best = None
    for c, (name, words) in types.items():
        if (c & ~HMD_FLAG_MASK) != (code & ~HMD_FLAG_MASK):
            continue
        diff = c ^ code
        if diff & ~HMD_FLAG_MASK:
            continue
        n = bin(diff).count('1')
        if best is None or n < best[0]:
            best = (n, c, name, words)
    if best is None:
        return None, []
    _, c, name, words = best
    words = [w for w in words if not any(bit & c & ~code and w == word for bit, word in HMD_FLAG_WORDS)]
    extra = [word for bit, word in HMD_FLAG_WORDS if bit & code & ~c]
    return None, extra + words

# ---------------------------------------------------------------- header text

BASIC_TYPES = {'char', 'short', 'int', 'long', 'unsigned', 'signed', 'u_char', 'u_short', 'u_int',
               'u_long', 'void', 'const', 'volatile', 'struct', 'register'}


def split_args(args):
    out, depth, cur = [], 0, ''
    for ch in args:
        if ch == ',' and depth == 0:
            out.append(cur.strip()); cur = ''
        else:
            if ch in '([': depth += 1
            if ch in ')]': depth -= 1
            cur += ch
    if cur.strip():
        out.append(cur.strip())
    return out


def arg_label(arg):
    """Name of a parameter, or its type when the prototype gives no name."""
    a = re.sub(r'\[.*?\]', '', arg).strip()
    toks = re.findall(r'[A-Za-z_]\w*|\*', a)
    idents = [t for t in toks if t != '*']
    if len(idents) >= 2 or (len(idents) == 1 and idents[0] not in BASIC_TYPES and '*' not in a and len(toks) == 1 and False):
        return idents[-1]
    if len(idents) == 1 and idents[0] in BASIC_TYPES:
        return a
    if len(idents) == 1 and '*' in a:
        return a
    return idents[-1] if idents else a


def format_prototype(name, p):
    ret = p['ret']
    if p['args'] is None:
        return [f'{ret}{"" if ret.endswith("*") else " "}{name}();']
    args = ', '.join(split_args(p['args'])) if p['args'] and p['args'] != 'void' else 'void'
    head = f'{ret}{"" if ret.endswith("*") else " "}{name}('
    line = head + args + ');'
    if len(line) <= 72:
        return [line]
    lines, cur = [], head
    parts = split_args(p['args'])
    indent = ' ' * len(head)
    for i, part in enumerate(parts):
        piece = part + (', ' if i < len(parts) - 1 else ');')
        if len(cur) + len(piece) > 74 and cur.strip() != head.strip():
            lines.append(cur.rstrip()); cur = indent
        cur += piece
    lines.append(cur.rstrip())
    return lines


def register_rows(name, p):
    rows = []
    if p['args'] not in (None, '', 'void'):
        for i, arg in enumerate(split_args(p['args'])):
            reg = f'a{i}' if i < 4 else f'0x{0x10 + 4 * (i - 4):x}(sp)'
            rows.append((reg, arg_label(arg)))
    ret = p['ret']
    if ret != 'void':
        rows.append(('v0', f'result ({ret})'))
    return rows


def function_block(name, p, hmd_line=None):
    out = []
    if p is None:
        if name.startswith('func_'):
            out.append(f'{name}: private routine, unnamed in the original; the name is its offset.')
        else:
            out.append(f'{name}: no prototype in the SDK headers.')
        if hmd_line:
            out.append(hmd_line)
        return out
    out += format_prototype(name, p)
    if p['args'] is None:
        out.append(f'  (declared without parameters in {p["header"]})')
    if p['note']:
        out.append(f'  ({p["note"]} of {p["header"]})')
    if hmd_line:
        out.append('')
        out.append(hmd_line)
    rows = register_rows(name, p)
    if rows:
        out.append('')
        out.append('Register use:')
        width = max(len(r) for r, _ in rows)
        for reg, label in rows:
            out.append(f'  {reg:<{width}}  {label}')
    return out


def build_header(lib_name, obj_name, symbols, protos, hmd_types):
    lines = [f'/* {lib_name}, member {obj_name} (hand-written assembly)']
    for sym in symbols:
        hmd_line = None
        m = re.fullmatch(r'GsU_([0-9a-f]{8})', sym)
        if m:
            code = int(m.group(1), 16)
            define, words = describe_hmd_type(code, hmd_types)
            desc = ' '.join(words) if words else 'unit type not described in libhmd.h'
            if define:
                hmd_line = f'HMD primitive driver for unit type 0x{code:08x} ({define}): {desc}.'
            else:
                hmd_line = f'HMD primitive driver for unit type 0x{code:08x}: {desc} (no define in libhmd.h; read from the flag bits).'
        lines.append(' *')
        for text in function_block(sym, protos.get(sym), hmd_line):
            lines.append((' * ' + text).rstrip())
    has_stack = any('(sp)  ' in l for l in lines)
    if has_stack:
        lines.append(' *')
        lines.append(' * Stack offsets are relative to sp on entry.')
    lines.append(' */')
    return lines

# ---------------------------------------------------------------- rewriting

def respell(lines):
    out = []
    for ln in lines:
        if ln.strip() == '.include\t"gte_macros.inc"' or ln.strip() == '.include "gte_macros.inc"':
            out.append('\t.include\t"inline_a.inc"'); continue
        m = OP_RE.match(ln)
        if m:
            out.append('\t' + SONY_NAME[m.group(1)] + m.group(2)); continue
        out.append(ln)
    return out


def rewrite(tu_dir, protos, hmd_types, members):
    tu = json.load(open(os.path.join(tu_dir, 'tu.json')))
    part = tu['parts'][0]
    path = os.path.join(tu_dir, part['path'])
    rel = os.path.relpath(tu_dir, 'src/libraries')
    rec = members[rel]
    lib_name = os.path.basename(rec['input'])
    obj_name = rec['member']
    lines = open(path).read().split('\n')
    lines = respell(lines)
    if not lines[0].startswith('/* LIB'):
        if lines[0].startswith('/* ') and lines[0].endswith('*/'):
            lines = lines[1:]
        lines = build_header(lib_name, obj_name, part['symbols'], protos, hmd_types) + lines
    return path, '\n'.join(lines)


def main(argv):
    dry = '--dry-run' in argv
    selected = [a for a in argv if not a.startswith('--')]
    protos = load_prototypes()
    hmd_types = load_hmd_types()
    members = {m['id']: m for m in json.load(open(MEMBERS))}
    dirs = []
    for tu in sorted(glob.glob('src/libraries/*/*/tu.json')):
        parts = json.load(open(tu))['parts']
        if len(parts) == 1 and parts[0]['path'].endswith('.s'):
            dirs.append(os.path.dirname(tu))
    if selected:
        dirs = [d for d in dirs if os.path.relpath(d, 'src/libraries') in selected]
    changed = 0
    for d in dirs:
        path, text = rewrite(d, protos, hmd_types, members)
        if dry:
            print(f'===== {path}')
            print('\n'.join(text.split('\n')[:40]))
            continue
        if open(path).read() != text:
            open(path, 'w').write(text); changed += 1
    if not dry:
        print(f'{len(dirs)} assembly TUs, {changed} files rewritten')


if __name__ == '__main__':
    main(sys.argv[1:])
