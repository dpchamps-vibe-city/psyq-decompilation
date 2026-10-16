#!/usr/bin/env python3
"""Install the byte-verified translations as assembly translation units.

For every member in build/asmify/results.json: copy build/asmify/out/<lib>/<tu>/<name>.s
into src/libraries/<lib>/<tu>/<name>.s, remove the C stub parts the old manifest listed,
and rewrite tu.json as the one-part assembly form the harness expects:
  { "schemaVersion": 1, "member": ID, "parts": [{ "path": "<name>.s", "symbols": [...] }] }
Run from the project root. Idempotent; refuses to touch a part that is not a canonical stub.
"""
import json, os, re, shutil, sys
ROOT = os.getcwd()
results = json.load(open("build/asmify/results.json"))
members = {v["tu"]: v for v in json.load(open("notes/research/asmify/asm_members.json")).values()}
STUB = re.compile(r'^\s*INCLUDE_ASM\("build/libraries/nonmatchings/(lib_[0-9a-f]{16}_\d+)",\s*(\w+)\);\s*$')
# Members whose matched C parts are replaced by the whole-file assembly form: the
# member also holds hand-written code, so its original source was one .s file.
# libapi/74-patch: EnablePAD/DisablePAD were matched as PSX_BIOS_TAILJUMP_LOAD C
# thunks beside the hand-written _patch_pad; the file form is the faithful one.
REPLACE_C = {"src/libraries/libapi/74-patch": {"EnablePAD", "DisablePAD"}}
installed = skipped = 0
for r in results:
    tu, lib, member = r["tu"], r["lib"], r["member"]
    info = members[tu]
    name = re.sub(r"^\d+-", "", os.path.basename(tu))
    src = os.path.join("build/asmify/out", tu.replace("src/libraries/", "", 1), f"{name}.s")
    if not os.path.exists(src): sys.exit(f"missing translation {src}")
    manifest_path = os.path.join(tu, "tu.json")
    manifest = json.load(open(manifest_path))
    if manifest["member"] != member: sys.exit(f"{tu}: manifest member {manifest['member']} != {member}")
    want = {"schemaVersion": 1, "member": member, "parts": [{"path": f"{name}.s", "symbols": info["functions"]}]}
    if manifest == want and open(os.path.join(tu, f"{name}.s")).read() == open(src).read():
        skipped += 1; continue
    # Every C function part must still be its canonical stub: real C is never discarded.
    for part in manifest["parts"]:
        path = os.path.join(tu, part["path"])
        if part["path"].endswith(".s"): continue
        if "symbol" in part:
            lines = [l for l in open(path).read().splitlines() if l.strip() and not l.strip().startswith("/*") and not l.strip().startswith("*") and not l.strip().startswith("#include")]
            if (len(lines) != 1 or not STUB.match(lines[0])) and part["symbol"] not in REPLACE_C.get(tu, set()):
                sys.exit(f"{path}: not a canonical stub; review before replacing")
    names = set(info["functions"])
    manifest_syms = {p["symbol"] for p in manifest["parts"] if "symbol" in p and p["symbol"] != "__library_member_data"}
    if manifest_syms != names: sys.exit(f"{tu}: manifest functions {sorted(manifest_syms)} != {sorted(names)}")
    for part in manifest["parts"]:
        if not part["path"].endswith(".s"): os.remove(os.path.join(tu, part["path"]))
    shutil.copyfile(src, os.path.join(tu, f"{name}.s"))
    with open(manifest_path, "w") as f: json.dump(want, f, indent=2); f.write("\n")
    leftovers = sorted(set(os.listdir(tu)) - {"tu.json", f"{name}.s"})
    if leftovers: sys.exit(f"{tu}: unexpected files left: {leftovers}")
    installed += 1
print(f"installed {installed}, already current {skipped}")
