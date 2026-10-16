#!/usr/bin/env python3
"""Semantic annotation of the RotSMD family (libgte SMD_00 .. SMD_15).
Rewrites header purpose + register table, renames labels by role and adds
line comments.  Instructions are never touched; comments are keyed by
instruction index and checked against the expected mnemonic."""
import json, os, re, sys
sys.path.insert(0, 'notes/research/asmify')
import annotate

PROTOS = annotate.load_prototypes()
MEMBERS = {m['id']: m for m in json.load(open(annotate.MEMBERS))}

PRIM = {'F3': ('POLY_F3 flat triangles', 4), 'G3': ('POLY_G3 Gouraud triangles', 6),
        'FT3': ('POLY_FT3 flat textured triangles', 7), 'GT3': ('POLY_GT3 Gouraud textured triangles', 9),
        'F4': ('POLY_F4 flat quads', 5), 'G4': ('POLY_G4 Gouraud quads', 8),
        'FT4': ('POLY_FT4 flat textured quads', 9), 'GT4': ('POLY_GT4 Gouraud textured quads', 12)}

# member dir -> (class, variant)
MEMBERS_SMD = {
 '108-smd_00': ('tri', 'F3'), '109-smd_01': ('tri', 'G3'), '110-smd_02': ('tri', 'FT3'), '111-smd_03': ('tri', 'GT3'),
 '112-smd_04': ('quad', 'F4'), '113-smd_05': ('quad', 'G4'), '114-smd_06': ('quad', 'FT4'), '115-smd_07': ('quad', 'GT4'),
 '116-smd_08': ('svtri', 'F3'), '117-smd_09': ('svtri', 'G3'), '118-smd_10': ('svtri', 'FT3'), '119-smd_11': ('svtri', 'GT3'),
 '120-smd_12': ('svquad', 'F4'), '121-smd_13': ('svquad', 'G4'), '122-smd_14': ('svquad', 'FT4'), '123-smd_15': ('svquad', 'GT4'),
}

LABELS = {
 'tri':    {1: 'flags', 2: 'packet', 3: 'next', 4: 'clip_v1', 5: 'clip_v2', 6: 'accept', 7: 'reject', 8: 'done'},
 'quad':   {1: 'flags', 2: 'packet', 3: 'next', 4: 'clip_v1', 5: 'clip_v2', 6: 'clip_v3', 7: 'accept', 8: 'emit', 9: 'reject', 10: 'done'},
 'svtri':  {1: 'next', 2: 'packet', 3: 'clip_v1', 4: 'clip_v2', 5: 'accept', 6: 'reject'},
 'svquad': {1: 'next', 2: 'packet', 3: 'clip_v1', 4: 'clip_v2', 5: 'clip_v3', 6: 'accept', 7: 'emit', 8: 'reject'},
}

# (index, mnemonic, comment template) per class; {size} {stride} {voff} {tagw} {prim}
COMMENTS = {
 'tri': [
  (7, 'lhu', 'packet count'), (8, 'addi', 'pa -> first packet'), (9, 'beqz', 'nothing to do'),
  (11, 'ori', 't8 = 0x00ffffff, OT link mask'), (12, 'li', 't7 = {tagw}-word tag of a {prim1}'),
  (13, 'lw', 'sclip'), (14, 'lw', 'hclip'), (15, 'lw', 'vclip'), (16, 'sll', 'hclip << 16, compared against sx << 16'),
  (17, 'lw', 'nclipmode'), (18, 'li', 'reject on FLAG bit 18'), (21, 'li', '... and on bit 17 when nclipmode is set'),
  (23, 'sub', 'a2 = 14 - otlen, the OTZ shift for the OT index'),
  (26, 'li', 'a3 = GPU packet offset: 0 for id 0, {size} otherwise'),
  (27, 'lwc2', "V0..V2 = the packet's three vertices (at {voff})"),
  (34, 'RTPT', 'project all three'), (35, 'add', 't3 = GPU packet of this SMD packet'),
  (37, 'lwc2', "preload the next packet's vertices while the GTE works"),
  (41, 'cfc2', 't2 = FLAG'), (42, 'NCLIP', 'winding test'), (45, 'mfc2', 't1 = MAC0, the nclip result'),
  (46, 'and', 'keep only the rejecting FLAG bits'), (47, 'blez', 'back-facing: drop'), (49, 'bnez', 'overflow: drop'),
  (50, 'mfc2', 'SXY0, SXY1, SXY2 (SXY0 loads in the delay slot)'), (53, 'beqz', 'no screen clipping: accept'),
  (54, 'sll', 'vertex 0: 0 <= sx < hclip and 0 <= sy < vclip ?'), (67, 'sll', 'vertex 1'),
  (80, 'sll', 'vertex 2; none inside drops the primitive'), (91, 'j', 'jump to the next instruction, as the original has it'),
  (94, 'AVSZ3', 'OTZ = average of SZ1..SZ3'), (95, 'sw', 'store the three screen points'),
  (98, 'mfc2', 't1 = OTZ'), (99, 'and', 'packet address without tag bits'), (100, 'srav', 'OT index = OTZ >> (14 - otlen)'),
  (102, 'add', 't2 = &ot[index]'), (103, 'lw', 'link the packet at the head of the OT bucket'),
  (109, 'addiu', 'next packet, {stride} bytes on'),
 ],
 'quad': [
  (7, 'lhu', 'packet count'), (8, 'addi', 'pa -> first packet'), (9, 'beqz', 'nothing to do'),
  (11, 'ori', 't8 = 0x00ffffff, OT link mask'), (12, 'li', 't7 = {tagw}-word tag of a {prim1}'),
  (13, 'lw', 'sclip'), (14, 'lw', 'hclip'), (15, 'lw', 'vclip'), (16, 'sll', 'hclip << 16, compared against sx << 16'),
  (17, 'lw', 'nclipmode'), (18, 'li', 'reject on FLAG bit 18'), (21, 'li', '... and on bit 17 when nclipmode is set'),
  (23, 'sub', 'a2 = 14 - otlen, the OTZ shift for the OT index'),
  (26, 'li', 'a3 = GPU packet offset: 0 for id 0, {size} otherwise'),
  (27, 'lwc2', "V1, V2 = vertices 1 and 2 of the first packet"),
  (31, 'lwc2', 'V0 = vertex 0 (vertices start at {voff})'), (33, 'add', 't3 = GPU packet of this SMD packet'),
  (35, 'RTPT', 'project vertices 0, 1 and 2'),
  (38, 'lwc2', "preload the next packet's vertices 1 and 2 while the GTE works"),
  (42, 'cfc2', 't2 = FLAG'), (43, 'NCLIP', 'winding test on the first three points'),
  (44, 'lwc2', 'V0 = vertex 3'), (46, 'mfc2', 't1 = MAC0, the nclip result'),
  (47, 'and', 'keep only the rejecting FLAG bits'), (48, 'blez', 'back-facing: drop'), (50, 'bnez', 'overflow: drop'),
  (51, 'mfc2', 'SXY0, SXY1, SXY2 (SXY0 loads in the delay slot)'),
  (54, 'RTPS', 'project vertex 3 while the first three are tested'), (55, 'beqz', 'no screen clipping: accept'),
  (56, 'sll', 'vertex 0: 0 <= sx < hclip and 0 <= sy < vclip ?'), (69, 'sll', 'vertex 1'), (82, 'sll', 'vertex 2'),
  (95, 'mfc2', "vertex 3: SXY2 now holds its screen point"), (97, 'sll', 'none of the first three inside: vertex 3 decides'),
  (110, 'mfc2', "SXY3, vertex 3's screen point (SXY2 after RTPS)"),
  (113, 'AVSZ4', 'OTZ = average of SZ0..SZ3'), (114, 'sw', 'store the four screen points'),
  (118, 'mfc2', 't1 = OTZ'), (119, 'and', 'packet address without tag bits'), (120, 'srav', 'OT index = OTZ >> (14 - otlen)'),
  (122, 'add', 't2 = &ot[index]'), (123, 'lw', 'link the packet at the head of the OT bucket'),
  (129, 'addiu', 'next packet, {stride} bytes on'),
 ],
 'svtri': [
  (7, 'lhu', 'packet count'), (8, 'addi', 'pa -> first packet'), (9, 'lw', 'id'),
  (10, 'lw', "the first packet's three vertex offsets (at {voff}) ..."), (13, 'add', '... turned into pointers into va'),
  (16, 'lw', 'sclip'), (17, 'lw', 'hclip'), (18, 'lw', 'vclip'), (19, 'sll', 'hclip << 16, compared against sx << 16'),
  (20, 'lw', 'nclipmode'), (21, 'li', 'reject on FLAG bit 18'), (24, 'li', '... and on bit 17 when nclipmode is set'),
  (25, 'lwc2', 'V0..V2 = the three shared vertices'), (32, 'RTPT', 'project all three'),
  (33, 'move', 't3 = this packet (its first GPU packet)'), (34, 'addi', 'a0 -> next packet, {stride} bytes on'),
  (35, 'lw', "prefetch the next packet's vertex pointers while the GTE works"),
  (41, 'cfc2', 't2 = FLAG'), (42, 'NCLIP', 'winding test'), (43, 'and', 'keep only the rejecting FLAG bits'),
  (44, 'bnez', 'overflow: drop'), (46, 'mfc2', 't1 = MAC0, the nclip result'),
  (47, 'mfc2', 'SXY0 (s4 is free again: nclipmode is folded into v0)'), (48, 'blez', 'back-facing: drop'),
  (49, 'mfc2', 'SXY1'), (50, 'beqz', 'id 0 uses the first GPU packet'), (51, 'mfc2', 'SXY2'),
  (52, 'addi', 'id 1 uses the second, {size} bytes on'),
  (53, 'beqz', 'no screen clipping: accept'), (54, 'sll', 'vertex 0: 0 <= sx < hclip and 0 <= sy < vclip ?'),
  (67, 'sll', 'vertex 1'), (80, 'sll', 'vertex 2; none inside drops the primitive'),
  (92, 'AVSZ3', 'OTZ = average of SZ1..SZ3'), (93, 'sw', 'store the three screen points'),
  (97, 'sub', 't2 = 14 - otlen, the OTZ shift for the OT index'), (98, 'mfc2', 't1 = OTZ'),
  (100, 'srav', 'OT index = OTZ >> (14 - otlen)'), (102, 'add', 't5 = &ot[index]'),
  (103, 'lw', 'link the packet at the head of the OT bucket'), (105, 'and', 'packet address without tag bits'),
  (106, 'li', '{tagw}-word tag of a {prim1}'),
  (110, 'slti', 'loop while packets remain'),
 ],
 'svquad': [
  (8, 'lhu', 'packet count'), (9, 'addi', 'pa -> first packet'), (10, 'lw', 'id'),
  (11, 'lw', "the first packet's four vertex offsets (at {voff}) ..."), (15, 'add', '... turned into pointers into va'),
  (19, 'lw', 'sclip'), (20, 'lw', 'hclip'), (21, 'lw', 'vclip'), (22, 'sll', 'hclip << 16, compared against sx << 16'),
  (23, 'lw', 'nclipmode'), (24, 'li', 'reject on FLAG bit 18'), (27, 'li', '... and on bit 17 when nclipmode is set'),
  (28, 'lwc2', 'V0..V2 = shared vertices 0, 1 and 2'), (35, 'RTPT', 'project the first three'),
  (36, 'move', 't3 = this packet (its first GPU packet)'), (37, 'addi', 'a0 -> next packet, {stride} bytes on'),
  (38, 'lw', "prefetch the next packet's first three vertex pointers"),
  (44, 'cfc2', 't2 = FLAG'), (45, 'NCLIP', 'winding test on the first three points'),
  (46, 'lwc2', 'V0 = shared vertex 3'), (48, 'mfc2', 't1 = MAC0, the nclip result'),
  (49, 'and', 'keep only the rejecting FLAG bits'), (50, 'blez', 'back-facing: drop'), (52, 'bnez', 'overflow: drop'),
  (54, 'beqz', 'id 0 uses the first GPU packet'), (56, 'addi', 'id 1 uses the second, {size} bytes on'),
  (57, 'mfc2', 'SXY0 (s4 is free again: nclipmode is folded into v0)'), (58, 'mfc2', 'SXY1'), (59, 'mfc2', 'SXY2'),
  (60, 'RTPS', 'project vertex 3 while the first three are stored'), (61, 'sw', 'store the first three screen points'),
  (64, 'beqz', 'no screen clipping: accept'), (65, 'sll', 'vertex 0: 0 <= sx < hclip and 0 <= sy < vclip ?'),
  (78, 'sll', 'vertex 1'), (91, 'sll', 'vertex 2'),
  (104, 'mfc2', 'vertex 3: SXY2 now holds its screen point'), (106, 'sll', 'none of the first three inside: vertex 3 decides'),
  (119, 'mfc2', "SXY3, vertex 3's screen point (SXY2 after RTPS)"),
  (122, 'AVSZ4', 'OTZ = average of SZ0..SZ3'), (123, 'sw', 'store the fourth screen point'),
  (125, 'sub', 't2 = 14 - otlen, the OTZ shift for the OT index'), (126, 'mfc2', 't1 = OTZ'),
  (128, 'srav', 'OT index = OTZ >> (14 - otlen)'), (130, 'add', 't5 = &ot[index]'),
  (131, 'lw', 'link the packet at the head of the OT bucket'), (133, 'and', 'packet address without tag bits'),
  (134, 'li', '{tagw}-word tag of a {prim1}'),
  (138, 'lw', "next packet's vertex 3 pointer"), (140, 'bgtz', 'loop while packets remain'),
 ],
}

PURPOSE = {
 'tri': ('Rotate, project and sort the {prim} of an SMD packet array into an\n'
         'ordering table.  pa starts with a halfword packet count; each packet is\n'
         '{stride} bytes holding two {size}-byte GPU packets (selected by id) and the\n'
         'three SVECTOR vertices at {voff}.  A primitive is dropped when it is\n'
         'back-facing, when the GTE flags an overflow, or, with sclip set, when\n'
         'none of its three screen points lies inside [0,hclip) x [0,vclip).'),
 'quad': ('Rotate, project and sort the {prim} of an SMD packet array into an\n'
          'ordering table.  pa starts with a halfword packet count; each packet is\n'
          '{stride} bytes holding two {size}-byte GPU packets (selected by id) and the\n'
          'four SVECTOR vertices at {voff}.  Vertices 0-2 go through RTPT and vertex 3\n'
          'through RTPS; the winding test uses the first three points.  A primitive\n'
          'is dropped when it is back-facing, when the GTE flags an overflow, or,\n'
          'with sclip set, when none of its four screen points lies inside\n'
          '[0,hclip) x [0,vclip).'),
 'svtri': ('Shared-vertex form of RotSMD_{var}: rotate, project and sort the {prim}\n'
           'of an SMD packet array into an ordering table.  pa starts with a halfword\n'
           'packet count; each packet is {stride} bytes holding two {size}-byte GPU\n'
           'packets (selected by id) and, at {voff}, three byte offsets into the shared\n'
           'SVECTOR array va.  A primitive is dropped when it is back-facing, when the\n'
           'GTE flags an overflow, or, with sclip set, when none of its three screen\n'
           'points lies inside [0,hclip) x [0,vclip).'),
 'svquad': ('Shared-vertex form of RotSMD_{var}: rotate, project and sort the {prim}\n'
            'of an SMD packet array into an ordering table.  pa starts with a halfword\n'
            'packet count; each packet is {stride} bytes holding two {size}-byte GPU\n'
            'packets (selected by id) and, at {voff}, four byte offsets into the shared\n'
            'SVECTOR array va.  Vertices 0-2 go through RTPT and vertex 3 through RTPS;\n'
            'the winding test uses the first three points.  A primitive is dropped\n'
            'when it is back-facing, when the GTE flags an overflow, or, with sclip\n'
            'set, when none of its four screen points lies inside [0,hclip) x [0,vclip).'),
}

REGISTERS = {
 'tri': ['a0  current packet              s0  hclip << 16     t0  packets left',
         'a1  ot                          s1  vclip           t3  GPU packet',
         'a2  14 - otlen (OTZ shift)      s4  nclipmode       t7  {tag} tag',
         'a3  GPU packet offset           s5  sclip           t8  0x00ffffff mask',
         'v0  FLAG bits that reject a primitive',
         't4, t5, t2  SXY0, SXY1, SXY2 once the points are read back'],
 'quad': ['a0  current packet              s0  hclip << 16     t0  packets left',
          'a1  ot                          s1  vclip           t3  GPU packet',
          'a2  14 - otlen (OTZ shift)      s4  nclipmode       t7  {tag} tag',
          'a3  GPU packet offset           s5  sclip           t8  0x00ffffff mask',
          'v0  FLAG bits that reject a primitive',
          't4, t5, t2, t6  SXY0..SXY3 once the points are read back'],
 'svtri': ['a0  next packet (advanced early)   s0  hclip << 16   t0  packets left',
           'a1  va, the shared vertex array    s1  vclip         t3  GPU packet',
           'a2  ot                             s5  sclip         t4  id',
           'a3  otlen                          s4  nclipmode, then SXY0',
           'v0  FLAG bits that reject a primitive',
           't7, t8, t9  vertex pointers of the packet being set up',
           's4, t5, t2  SXY0, SXY1, SXY2 once the points are read back'],
 'svquad': ['a0  next packet (advanced early)   s0  hclip << 16   t0  packets left',
            'a1  va, the shared vertex array    s1  vclip         t3  GPU packet',
            'a2  ot                             s5  sclip         t4  id',
            'a3  otlen                          s4  nclipmode, then SXY0',
            'v0  FLAG bits that reject a primitive',
            't7, t8, t9, v1  vertex pointers of the packet being set up',
            's4, t5, t2, s6  SXY0..SXY3 once the points are read back'],
}

def params(cls, var):
    prim, tagw = PRIM[var]
    prim1 = prim.split(' ', 1)[1].rstrip('s')
    size = (tagw + 1) * 4
    if cls == 'tri':
        voff, stride = 2 * size, 2 * size + 3 * 8
    elif cls == 'quad':
        voff, stride = 2 * size, 2 * size + 4 * 8
    elif cls == 'svtri':
        voff, stride = 2 * size, 2 * size + 3 * 4
    else:
        voff, stride = 2 * size, 2 * size + 4 * 4
    return dict(prim=prim, prim1=prim1, tagw=tagw, tag=f'0x{tagw:02x}000000', size=f'0x{size:x}',
                voff=f'0x{voff:x}', stride=f'0x{stride:x}', var=var)

def annotate_file(d, cls, var):
    p = params(cls, var)
    path = f'src/libraries/libgte/{d}/{d.split("-")[1]}.s'
    lines = open(path).read().split('\n')
    # header
    end = lines.index(' */')
    sym = f'RotSMD_{"SV_" if cls.startswith("sv") else ""}{var}'
    rec = MEMBERS[f'libgte/{d}']
    hdr = [f'/* {os.path.basename(rec["input"])}, member {rec["member"]} (hand-written assembly)', ' *']
    hdr += [(' * ' + l).rstrip() for l in annotate.format_prototype(sym, PROTOS[sym])]
    hdr += [' *'] + [(' * ' + l).rstrip() for l in PURPOSE[cls].format(**p).split('\n')]
    hdr += [' *', ' * Register use:'] + [(' *   ' + l.format(**p)).rstrip() for l in REGISTERS[cls]]
    hdr += [' */']
    body = lines[end + 1:]
    # strip old comments, rename labels
    labels = LABELS[cls]
    out = []
    for ln in body:
        if ln.startswith('\t') and '\t# ' in ln:
            ln = ln.split('\t# ')[0]
        ln = re.sub(r'\.L(\d+)\b', lambda m: '.L' + labels[int(m.group(1))] if int(m.group(1)) in labels else m.group(0), ln)
        out.append(ln)
    # comments by instruction index
    idx = [i for i, ln in enumerate(out) if re.match(r'^\t[A-Za-z]', ln)]
    for k, mnem, text in COMMENTS[cls]:
        li = idx[k]
        actual = out[li].strip().split()[0]
        assert actual == mnem, (d, k, mnem, actual, out[li])
        out[li] = out[li] + '\t# ' + text.format(**p)
    # sanity: key operands match the derived parameters
    text = '\n'.join(out)
    assert f"{p['tag']}" .replace('0x0', '0x').lower() in text.lower().replace('0x0', '0x'), (d, p['tag'])
    open(path, 'w').write('\n'.join(hdr + out))
    return path

for d, (cls, var) in MEMBERS_SMD.items():
    print(annotate_file(d, cls, var))
