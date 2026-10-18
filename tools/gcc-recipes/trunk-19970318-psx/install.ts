/* Install the pinned compiler/export only. Never repair compiler output. */
import { createHash } from "node:crypto";
import { chmodSync, copyFileSync, cpSync, existsSync, mkdirSync, readFileSync, readdirSync, rmSync, writeFileSync } from "node:fs";
import { dirname, join, relative, resolve } from "node:path";
import { fileURLToPath } from "node:url";
const NAME = "trunk-19970318-psx", VERSION = "trunk-19970318";
const here = dirname(fileURLToPath(import.meta.url)), root = resolve(here, "../../..");
const [directory, ...args] = process.argv.slice(2);
if (!directory || args.some(a => a !== "--replace")) throw new Error("Usage: npx tsx install.ts EXPORT_DIR [--replace]");
const exported = resolve(directory), replace = args.includes("--replace");
const sha = (bytes: Buffer | string) => createHash("sha256").update(bytes).digest("hex");
const hash = (file: string) => sha(readFileSync(file));
function filesUnder(top: string): string[] {
  return readdirSync(top, { withFileTypes: true }).flatMap(f => f.isDirectory() ? filesUnder(join(top, f.name)).map(p => `${f.name}/${p}`) : [f.name]).sort();
}
const json = (file: string, data: unknown) => writeFileSync(file, JSON.stringify(data, null, 2) + "\n");
const cc1 = join(exported, "cc1"), cpp = join(exported, "cccp"), actual = hash(cc1), actualCpp = hash(cpp);
for (const [name, value] of [["cc1", actual], ["cpp", actualCpp]]) {
  const expected = readFileSync(join(here, `expected-${name}.sha256`), "utf8").split(/\s/)[0];
  if (value !== expected) throw new Error(`${name} hashes ${value}, expected ${expected}; refusing installation`);
}
const bundle = join(exported, "compiler-source");
const upstream = Object.fromEntries(readFileSync(join(bundle, "upstream.sha256"), "utf8").trim().split("\n").map(line => {
  const [digest, name] = line.trim().split(/\s+/); return [name!, digest!];
}));
const runtime = join(root, "build/dependencies/compiler", `gcc-${NAME}`), vendor = join(root, "tools/vendor/gcc", NAME);
const sourceFiles = filesUnder(join(bundle, "src"));
if (!sourceFiles.length || !upstream["gcc-trunk-19970318.tar.gz"] || !upstream["cdk-gcc-b18.tar.gz"]) throw new Error("Incomplete compiler source export");
for (const dest of [runtime, vendor]) if (existsSync(dest) && !replace) throw new Error(`${dest} exists; pass --replace`);
for (const dest of [runtime, vendor]) { rmSync(dest, { recursive: true, force: true }); mkdirSync(dest, { recursive: true }); }
for (const [from, to] of [[cc1, "cc1"], [cpp, "cccp"]]) { copyFileSync(from!, join(runtime, to!)); chmodSync(join(runtime, to!), 0o755); }
const recipe = join(here, "Dockerfile");
json(join(runtime, "compiler-provenance.json"), { schemaVersion: 1, version: NAME, recipe: relative(root, recipe), recipeHash: hash(recipe), compilerHash: actual, preprocessorHash: actualCpp,
  tools: { cc1: actual, cpp: actualCpp }, buildLog: `build/compiler-provision/${NAME}.log`, evidence: "notes/research/compiler-identification-1997-trunk.md" });
cpSync(join(bundle, "src"), join(vendor, "src"), { recursive: true, dereference: true });
copyFileSync(join(bundle, "upstream.sha256"), join(vendor, "upstream.sha256"));
const recipeDir = join(vendor, "recipe"); mkdirSync(recipeDir);
for (const name of ["Dockerfile", "byacc-wrap", "expected-cc1.sha256", "expected-cpp.sha256", "install.ts", "provision.sh", "README.md"]) if (existsSync(join(here, name))) copyFileSync(join(here, name), join(recipeDir, name));
for (const sub of ["patches", "tests"]) cpSync(join(here, sub), join(recipeDir, sub), { recursive: true, dereference: true });
const src = join(vendor, "src"), files = filesUnder(src), tree = sha(files.map(f => `${hash(join(src, f))}  ${f}\n`).join(""));
const contextFiles = ["Dockerfile", "byacc-wrap", ...["patches", "tests"].flatMap(sub => filesUnder(join(here, sub)).map(f => `${sub}/${f}`))].sort();
const context = sha(JSON.stringify(contextFiles.map(f => [f, hash(join(here, f))])));
json(join(vendor, "pin.json"), {
  name: `gcc-${NAME}`, gccVersion: VERSION,
  correspondsTo: { binary: relative(root, join(runtime, "cc1")), binarySha256: actual, recipe: "recipe/Dockerfile", target: "mips-linux-gnu" },
  upstream: { url: "https://codeload.github.com/gcc-mirror/gcc/tar.gz/2b3600acb4eceda3000312002ec78fecd5a39d30", sha256: upstream["gcc-trunk-19970318.tar.gz"], description: "GCC development trunk, gcc-mirror commit 2b3600acb4ec (1997-03-18 18:38 UTC)" },
  scaffolding: { url: "https://github.com/ser-pounce/cdk-gcc/archive/refs/tags/b18.tar.gz", sha256: upstream["cdk-gcc-b18.tar.gz"],
    files: ["configure", "version.c", "obstack.c", "obstack.h", "c-gperf.h", "getopt.c", "gstab.h", "stab.def", "hash.c", "hash.h", "tlink.c", "move-if-change", "gcov-io.h", "config/xm-linux.h", "config/i386/xm-linux.h", "config/mips/xm-*.h"], description: "build infrastructure files absent from the git history; no code-generation content" },
  build: { recipeSha256: hash(recipe), contextSha256: context, sourceCaptureRecipeSha256: hash(recipe), rebuiltBinarySha256: actual, requiredFlags: ["-mmips-as", "-fno-exceptions"] },
  tree: { root: "src", sha256: tree, algorithm: "sha256 over LC_ALL=C-sorted lines of '<file sha256>  <path relative to src>\\n'", files: files.length },
  included: ["gcc top-level C, headers, machine/build inputs, including generated headers", "shared cc1 language-option/build include fragments", "MIPS target and i386 build-host configuration"],
  excluded: ["compiled binaries and object archives", "other language front-end implementations and unrelated targets", "runtime libraries, testsuites and generated documentation"],
  exclusionRisk: "Source queries cover the captured cc1/host/MIPS inputs, not other compiler programs. Source availability does not establish RTL/oracle adapter support.",
  identification: "notes/research/compiler-identification-1997-trunk.md",
});
console.log(`Installed ${runtime}/cc1 (${actual}), cccp (${actualCpp}) and ${vendor} (${files.length} source files, tree ${tree})`);
