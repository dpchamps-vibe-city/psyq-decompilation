/* Maintainer-only generator. Requires a locally populated binutils-gdb clone
 * and the official release tarball. Never fetches objects from the network. */
import { execFileSync, spawnSync } from "node:child_process";
import { createHash } from "node:crypto";
import { mkdirSync, mkdtempSync, readFileSync, readdirSync, rmSync, writeFileSync } from "node:fs";
import { dirname, join, resolve } from "node:path";
import { fileURLToPath } from "node:url";
const here = dirname(fileURLToPath(import.meta.url)), [repository, archive] = process.argv.slice(2);
if (!repository || !archive) throw new Error("Usage: make-rollback.ts BINUTILS-GDB.GIT binutils-2.8.tar.gz");
const sha = (b: Buffer | string) => createHash("sha256").update(b).digest("hex");
if (sha(readFileSync(archive)) !== "803733c8f748268875bfea542a55fa7cad24be9fb390d4584939f8122be97379") throw new Error("Release hash mismatch");
const env = { ...process.env, GIT_NO_LAZY_FETCH: "1" };
const git = (...args: string[]) => execFileSync("git", ["-c", "remote.origin.url=/nonexistent", "-C", resolve(repository), ...args], { env, maxBuffer: 64 * 1024 * 1024, stdio: ["ignore", "pipe", "pipe"] }).toString();
const pin = "939b216956668489c979bdc55cfaadc25e28e025", release = git("rev-parse", "412dfaedc8").trim();
const available = new Set(git("cat-file", "--batch-all-objects", "--batch-check=%(objectname)").trim().split("\n"));
const source = (revision: string, file: string) => {
  const oid = git("rev-parse", `${revision}:${file}`).trim();
  if (!available.has(oid)) throw new Error(`Historical blob ${oid} for ${revision}:${file} is not present locally (network disabled)`);
  return git("show", `${revision}:${file}`);
};
const sanitize = (text: string) => {
  const stack: string[] = [], lines: string[] = [];
  for (const line of text.split(/(?<=\n)/)) {
    const start = /start-sanitize-([\w-]+)/.exec(line), end = /end-sanitize-([\w-]+)/.exec(line);
    if (start) stack.push(start[1]!);
    else if (end) { if (stack.pop() !== end[1]) throw new Error("Mismatched sanitize blocks"); }
    else if (!stack.length) lines.push(line);
  }
  if (stack.length) throw new Error("Unclosed sanitize block");
  return lines.join("");
};
const scratch = mkdtempSync(join(here, ".rollback-")), output = join(here, "rollback");
const excluded = (f: string) => /(?:^|\/)(?:ChangeLog[^/]*|doc|testsuite)(?:\/|$)/.test(f);
try {
  execFileSync("tar", ["-xzf", resolve(archive), "-C", scratch]);
  const tree = join(scratch, "binutils-2.8");
  const commits = git("log", release, `^${pin}`, "--format=%H", "--", "gas", "bfd", "opcodes", "include").trim().split("\n");
  const commitPaths = new Map(commits.map(commit => [commit, git("diff-tree", "--no-commit-id", "--name-only", "-r", commit).split("\n")]));
  const changed = new Set(git("log", release, `^${pin}`, "--format=", "--name-only", "--", "gas", "bfd", "opcodes", "include").split("\n").filter(f => f && !excluded(f)));
  const files = (dir: string): string[] => readdirSync(join(tree, dir), { withFileTypes: true }).flatMap(e => e.isDirectory() ? files(`${dir}/${e.name}`) : [`${dir}/${e.name}`]);
  const patches = new Map<string, { commit: string; message: string; date: string; files: string[]; diffs: string[] }>();
  const entries: any[] = [];
  const difference = (file: string, before: string, after: string) => {
    writeFileSync(join(scratch, "before"), before); writeFileSync(join(scratch, "after"), after);
    const r = spawnSync("diff", ["-u", "--label", `a/${file}`, "--label", `b/${file}`, join(scratch, "before"), join(scratch, "after")], { encoding: "utf8" });
    if (r.status !== 0 && r.status !== 1) throw new Error(r.stderr);
    return r.stdout;
  };
  for (const file of ["gas", "bfd", "opcodes", "include"].flatMap(files).sort()) {
    const content = sanitize(readFileSync(join(tree, file), "latin1")), releaseSha256 = sha(Buffer.from(content, "latin1"));
    if (!changed.has(file)) { entries.push({ file, status: "unchanged", releaseSha256, resultSha256: releaseSha256, basis: "No change in the scoped upstream history; release content retained" }); continue; }
    const row: any = { file, releaseRevision: release, pinRevision: pin, releaseSha256 };
    try {
      const current = sanitize(source(release, file));
      const reviewed = file === "gas/config/tc-mips.c" && releaseSha256 === "b1a8ed7f4cff037ba519156c0b600f3b6d256f276c5305c0753256c3a6ea7ed4" && sha(current) === "2f855594a958f446eb7102362b0ff0fbafacad80f09a0787b0debd506fec2aec";
      if (current !== content && !reviewed) throw new Error("Release differs from sanitized upstream release revision; no reviewed delta");
      const pending: Array<{ commit: string; diff: string }> = [];
      if (reviewed) pending.push({ commit: "reviewed-release-delta", diff: difference(file, content, current) });
      let state = current;
      for (const commit of commits) {
        if (!commitPaths.get(commit)!.includes(file)) continue;
        const before = sanitize(source(commit, file)), after = sanitize(source(`${commit}^`, file));
        if (before !== state) throw new Error(`Nonlinear or incomplete history at ${commit}`);
        const diff = difference(file, before, after); if (diff) pending.push({ commit, diff }); state = after;
      }
      if (state !== sanitize(source(pin, file))) throw new Error("Reversed history does not reach pin revision");
      for (const { commit, diff } of pending) {
        let p = patches.get(commit);
        if (!p) {
          p = { commit, message: commit === "reviewed-release-delta" ? "Reviewed release-only delta: tc-mips.c nopic_need_relax #ifdef/zero-value condition; research section 3. Exact input/output hashes are in manifest.json." : git("show", "-s", "--format=%B", commit).trim(), date: commit === "reviewed-release-delta" ? "19970430" : git("show", "-s", "--format=%cs", commit).trim().replaceAll("-", ""), files: [], diffs: [] }; patches.set(commit, p);
        }
        p.files.push(file); p.diffs.push(diff);
      }
      entries.push({ ...row, status: "rolled-back", upstreamReleaseSha256: sha(current), resultSha256: sha(state), commits: pending.map(p => p.commit), ...(reviewed ? { reviewedDelta: "Exact six-line release delta identified in assembler research section 3; patch 0000" } : {}) });
    } catch (error) { entries.push({ ...row, status: "kept", resultSha256: releaseSha256, reason: String(error).split("\n").slice(0, 3).join("\n") }); }
  }
  for (const file of changed) if (!entries.some(e => e.file === file)) entries.push({ file, status: "kept", reason: "Not present in the official release; no file introduced" });
  rmSync(output, { recursive: true, force: true }); mkdirSync(output);
  const ordered = ["reviewed-release-delta", ...commits].flatMap(c => patches.has(c) ? [patches.get(c)!] : []);
  const patchRecords = ordered.map((p, i) => {
    const file = `${String(i).padStart(4, "0")}-${p.date}-${p.commit.slice(0, 12)}.patch`;
    const text = `Upstream commit: ${p.commit}\nChangeLog / commit message:\n${p.message}\nFiles: ${p.files.join(", ")}\n\n${p.diffs.join("\n")}`;
    writeFileSync(join(output, file), text); return { file, sha256: sha(text), commit: p.commit, files: p.files };
  });
  writeFileSync(join(output, "manifest.json"), JSON.stringify({ schemaVersion: 1, source: { archive: "binutils-2.8.tar.gz", sha256: sha(readFileSync(archive)) }, pin, release, pinInstant: "1997-03-18T18:38:00Z", commitsInWindow: commits.length, changedSourceFiles: changed.size, network: "disabled; missing historical blobs are explicitly kept", patches: patchRecords, files: entries }, null, 2) + "\n");
  writeFileSync(join(output, "result.sha256"), entries.filter(e => e.resultSha256).map(e => `${e.resultSha256}  ${e.file}\n`).join(""));
  writeFileSync(join(output, "patches.sha256"), patchRecords.map(p => `${p.sha256}  ${p.file}\n`).join(""));
  console.log(JSON.stringify({ files: entries.length, changed: changed.size, patches: ordered.length, statuses: entries.reduce((a, e) => ({ ...a, [e.status]: (a[e.status] ?? 0) + 1 }), {}) }));
} finally { rmSync(scratch, { recursive: true, force: true }); }
