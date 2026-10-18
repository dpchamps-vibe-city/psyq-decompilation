import assert from "node:assert/strict";
import { execFileSync } from "node:child_process";
import { mkdtempSync, readFileSync, rmSync, writeFileSync } from "node:fs";
import { tmpdir } from "node:os";
import { join, resolve } from "node:path";
const assembler = process.argv[2];
if (!assembler) throw new Error("Usage: check.ts PATH_TO_AS");
const dir = mkdtempSync(join(tmpdir(), "period-as-check-"));
function assemble(text: string) {
  writeFileSync(join(dir, "input.s"), text);
  execFileSync(resolve(assembler!), ["-EL", "-G0", "-mips1", join(dir, "input.s"), "-o", join(dir, "output.o")]);
  const b = readFileSync(join(dir, "output.o")); assert.equal(b.readUInt16LE(0), 0x162);
  const sections = new Map<string, Buffer>();
  for (let i = 0; i < b.readUInt16LE(2); i++) {
    const at = 20 + b.readUInt16LE(16) + i * 40, name = b.toString("ascii", at, at + 8).replace(/\0.*$/, "");
    sections.set(name, b.subarray(b.readUInt32LE(at + 20), b.readUInt32LE(at + 20) + b.readUInt32LE(at + 16)));
  }
  return sections;
}
try {
  assert.equal(assemble(".text\n.set noreorder\nmove $2,$4\n").get(".text")!.readUInt32LE(0), 0x00801021, "move must be addu");
  assert.equal(assemble(".text\n.set noreorder\ndiv $2,$4,$5\n").get(".text")!.readUInt32LE(0), 0x0085001a, "division must precede zero/overflow guards");
  assert.equal(assemble(".rdata\n.word 7\n").get(".rdata")!.readUInt32LE(0), 7, ".rdata must remain ECOFF rdata");
  console.log("period assembler: move, divide-first and rdata checks passed");
} finally { rmSync(dir, { recursive: true, force: true }); }
