#!/usr/bin/env python3
"""Install a provisioned trunk-19970318 compiler into this project's ignored
runtime locations and write the source pin the harness verifies.

usage: install.py <docker export dir> [--replace]

The export directory is what `docker build --target export --output` of the
recipe produces: `cc1` plus `compiler-source/{src,upstream.sha256}`. The cc1
hash must equal expected-cc1.sha256; nothing is installed otherwise.
"""
import hashlib, json, os, shutil, sys

NAME = "trunk-19970318-psx"
VERSION = "trunk-19970318"
TRUNK_URL = "https://codeload.github.com/gcc-mirror/gcc/tar.gz/2b3600acb4eceda3000312002ec78fecd5a39d30"
CDK_URL = "https://github.com/ser-pounce/cdk-gcc/archive/refs/tags/b18.tar.gz"
SCAFFOLDING = ["configure", "version.c", "obstack.c", "obstack.h", "c-gperf.h", "getopt.c", "gstab.h", "stab.def",
               "hash.c", "hash.h", "tlink.c", "move-if-change", "gcov-io.h", "config/xm-linux.h",
               "config/i386/xm-linux.h", "config/mips/xm-*.h"]

here = os.path.dirname(os.path.abspath(__file__))
root = os.path.abspath(os.path.join(here, "..", "..", ".."))
export = os.path.abspath(sys.argv[1]); replace = "--replace" in sys.argv


def sha256(path):
    h = hashlib.sha256()
    with open(path, "rb") as f:
        for chunk in iter(lambda: f.read(1 << 20), b""):
            h.update(chunk)
    return h.hexdigest()


def files_under(top):
    out = []
    for d, _, names in os.walk(top):
        for n in names:
            out.append(os.path.relpath(os.path.join(d, n), top).replace(os.sep, "/"))
    return sorted(out)


cc1 = os.path.join(export, "cc1")
expected = open(os.path.join(here, "expected-cc1.sha256")).read().split()[0]
actual = sha256(cc1)
if actual != expected:
    sys.exit(f"install.py: cc1 hashes {actual}, expected {expected}; refusing to install")

bundle = os.path.join(export, "compiler-source")
upstream = {}
for line in open(os.path.join(bundle, "upstream.sha256")):
    digest, name = line.split()
    upstream[name] = digest

runtime = os.path.join(root, "build", "dependencies", "compiler", f"gcc-{NAME}")
vendor = os.path.join(root, "tools", "vendor", "gcc", NAME)
for dest in (runtime, vendor):
    if os.path.exists(dest):
        if not replace:
            sys.exit(f"install.py: {dest} exists; pass --replace to overwrite")
        shutil.rmtree(dest)

os.makedirs(runtime)
shutil.copy2(cc1, os.path.join(runtime, "cc1")); os.chmod(os.path.join(runtime, "cc1"), 0o755)
recipe = os.path.join(here, "Dockerfile")
recipe_rel = os.path.relpath(recipe, root)
json.dump({
    "schemaVersion": 1, "version": NAME, "recipe": recipe_rel, "recipeHash": sha256(recipe), "compilerHash": actual,
    "buildLog": f"build/compiler-provision/{NAME}.log",
    "evidence": "notes/research/compiler-identification-1997-trunk.md",
}, open(os.path.join(runtime, "compiler-provenance.json"), "w"), indent=2)

os.makedirs(vendor)
shutil.copytree(os.path.join(bundle, "src"), os.path.join(vendor, "src"))
shutil.copy2(os.path.join(bundle, "upstream.sha256"), os.path.join(vendor, "upstream.sha256"))
recipe_dir = os.path.join(vendor, "recipe"); os.makedirs(recipe_dir)
for name in ("Dockerfile", "byacc-wrap", "expected-cc1.sha256", "install.py", "provision.sh", "README.md"):
    if os.path.exists(os.path.join(here, name)):
        shutil.copy2(os.path.join(here, name), os.path.join(recipe_dir, name))
for sub in ("patches", "tests"):
    shutil.copytree(os.path.join(here, sub), os.path.join(recipe_dir, sub))

src = os.path.join(vendor, "src")
files = files_under(src)
tree = hashlib.sha256("".join(f"{sha256(os.path.join(src, f))}  {f}\n" for f in files).encode()).hexdigest()
context_files = sorted(
    [os.path.relpath(p, here) for p in [os.path.join(here, "Dockerfile"), os.path.join(here, "byacc-wrap")]]
    + [os.path.relpath(os.path.join(d, n), here) for sub in ("patches", "tests") for d, _, ns in os.walk(os.path.join(here, sub)) for n in ns])
context = hashlib.sha256(json.dumps(sorted([[f, sha256(os.path.join(here, f))] for f in context_files]), separators=(",", ":")).encode()).hexdigest()
pin = {
    "name": f"gcc-{NAME}", "gccVersion": VERSION,
    "correspondsTo": {"binary": os.path.relpath(os.path.join(runtime, "cc1"), root), "binarySha256": actual,
                      "recipe": "recipe/Dockerfile", "target": "mips-linux-gnu"},
    "upstream": {"url": TRUNK_URL, "sha256": upstream["gcc-trunk-19970318.tar.gz"],
                 "description": "GCC development trunk, gcc-mirror commit 2b3600acb4ec (1997-03-18 18:38 UTC)"},
    "scaffolding": {"url": CDK_URL, "sha256": upstream["cdk-gcc-b18.tar.gz"], "files": SCAFFOLDING,
                    "description": "build infrastructure files absent from the git history; no code-generation content"},
    "build": {"recipeSha256": sha256(recipe), "contextSha256": context, "sourceCaptureRecipeSha256": sha256(recipe),
              "rebuiltBinarySha256": actual, "requiredFlags": ["-mmips-as", "-fno-exceptions"]},
    "tree": {"root": "src", "sha256": tree,
             "algorithm": "sha256 over LC_ALL=C-sorted lines of '<file sha256>  <path relative to src>\\n'", "files": len(files)},
    "included": ["gcc top-level C, headers, machine/build inputs, including generated headers",
                 "MIPS target and i386 build-host configuration"],
    "excluded": ["compiled binaries and object archives", "other language front ends and unrelated targets",
                 "runtime libraries, testsuites and generated documentation"],
    "exclusionRisk": "Source queries cover the captured cc1/host/MIPS inputs, not other compiler programs. Source availability does not establish RTL/oracle adapter support.",
    "identification": "notes/research/compiler-identification-1997-trunk.md",
}
json.dump(pin, open(os.path.join(vendor, "pin.json"), "w"), indent=2)
open(os.path.join(vendor, "pin.json"), "a").write("\n")
print(f"installed {runtime}/cc1 ({actual}) and {vendor} ({len(files)} source files, tree {tree})")
