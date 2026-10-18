/* Install only the recipe's pinned binary; no input/output repair. */
import { createHash } from "node:crypto";
import { chmodSync, copyFileSync, existsSync, mkdirSync, readFileSync, writeFileSync } from "node:fs";
import { dirname, join, resolve, relative } from "node:path";
import { fileURLToPath } from "node:url";
const here = dirname(fileURLToPath(import.meta.url)), root = resolve(here, "../../.."), [exportDir, ...args] = process.argv.slice(2);
if (!exportDir || args.some(a => a !== "--replace")) throw new Error("Usage: install.ts EXPORT_DIR [--replace]");
const hash = (path: string) => createHash("sha256").update(readFileSync(path)).digest("hex");
const binary = join(exportDir, "as"), expected = readFileSync(join(here, "expected-as.sha256"), "utf8").split(/\s/)[0];
if (hash(binary) !== expected) throw new Error("Assembler hash differs from expected-as.sha256; refusing installation");
const manifest = JSON.parse(readFileSync(join(here, "rollback/manifest.json"), "utf8"));
for (const patch of manifest.patches) if (hash(join(here, "rollback", patch.file)) !== patch.sha256) throw new Error(`Rollback patch changed: ${patch.file}`);
const dest = join(root, "build/dependencies/assembler/gas-19970318-psx"), output = join(dest, "as");
if (existsSync(output) && !args.includes("--replace")) throw new Error(`${output} exists; pass --replace`);
mkdirSync(dest, { recursive: true }); copyFileSync(binary, output); chmodSync(output, 0o755);
writeFileSync(join(dest, "assembler-provenance.json"), JSON.stringify({ schemaVersion: 1, name: "gas-19970318-psx", binarySha256: expected,
  source: manifest.source, pin: manifest.pin, release: manifest.release,
  recipe: relative(root, here), files: Object.fromEntries(["Dockerfile", "build.sh", "sanitize.sh", "rollback/manifest.json"].map(p => [p, hash(join(here, p))])),
  environment: process.env.BUILD_IMAGE ?? "ubuntu:focal (see build log)",
  evidence: "notes/research/assembler-identification-1997-trunk.md",
}, null, 2) + "\n");
console.log(`Installed ${output} (${expected})`);
