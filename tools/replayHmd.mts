/** Replay Sony's MAKE1/2/3 rules through the configured production chain.
 * Run from the harness: npx tsx ../psyq-decomp/tools/replayHmd.mts
 * An optional first argument selects the staging project before switchover. */
import { readFileSync, writeFileSync, mkdirSync, readdirSync } from 'node:fs';
import { dirname, join, resolve } from 'node:path';
import { fileURLToPath, pathToFileURL } from 'node:url';
const root = resolve(dirname(fileURLToPath(import.meta.url)), '..');
const settings = JSON.parse(readFileSync(join(root, '.pi/settings.json'), 'utf8'));
const harness = resolve(root, '.pi', settings.packages.find((p: unknown) => typeof p === 'string' && p.includes('psx-decompilation-harness')));
const load = (path: string) => import(pathToFileURL(join(harness, 'tools/lib', path + '.ts')).href);
const { contextForProject, inRuntimeContext } = await load('runtimeContext');
const { configuredTool, configuredFlags, configuredAssemblyCppFlags } = await load('toolchain');
const { assemble } = await load('assembler');
const { acceptanceToolchain } = await load('toolProvenance');
const { compareObjectBytes } = await load('objectFormats/byteCompare');
const { readPsyqLib, hash } = await load('psyqMembers');
const { execFileSync } = await import('node:child_process');
const buildRoot = process.argv[2] ? resolve(process.argv[2]) : root;
inRuntimeContext(contextForProject(buildRoot), () => {
  const output = join(root, 'build/toolchain-provenance/hmd-production-replay');
  const source = join(output, 'source'), include = join(output, 'include');
  const origins: Array<{ input: string; sha256: string; view: string; viewSha256: string }> = [];
  const view = (from: string, to: string, recursive = false) => {
    mkdirSync(to, { recursive: true });
    for (const entry of readdirSync(from, { withFileTypes: true })) {
      if (entry.isDirectory()) { if (recursive) view(join(from, entry.name), join(to, entry.name.toLowerCase()), true); continue; }
      if (!/\.(h|c|asm)$/i.test(entry.name)) continue;
      const input = join(from, entry.name), destination = join(to, entry.name.toLowerCase());
      const original = readFileSync(input), normalized = Buffer.from(original.toString('latin1').replace(/\r\n/g, '\n'), 'latin1');
      writeFileSync(destination, normalized); origins.push({ input, sha256: hash(original), view: destination, viewSha256: hash(normalized) });
    }
  };
  const sdk = join(root, 'library-input/psyq'), hmd = join(sdk, 'SRC/LIB/HMD');
  view(join(sdk, 'INCLUDE'), include, true); view(hmd, source);
  const rules: Array<{ object: string; source: string; defines: string[]; dmpsx: boolean; makefile: string }> = [];
  const makefiles = [];
  for (const makefile of ['MAKE1.MAK', 'MAKE2.MAK', 'MAKE3.MAK']) {
    const bytes = readFileSync(join(hmd, makefile)), text = bytes.toString('latin1').replace(/\r/g, '');
    makefiles.push({ input: join(hmd, makefile), sha256: hash(bytes) });
    const listed = new Set([...text.matchAll(/^\s*([\da-z_]+\.(?:o2|obj))\s*\\?\s*$/gim)].map(m => m[1]!.toLowerCase()));
    const lines = text.split('\n');
    for (let i = 0; i < lines.length; i++) {
      const head = /^([\da-z_]+)\.obj:\s*([\da-z_]+\.(?:c|asm))\s*$/i.exec(lines[i]!);
      if (!head) continue;
      const object = head[1]!.toLowerCase(), dmpsx = listed.has(object + '.o2');
      if (!dmpsx && !listed.has(object + '.obj')) continue;
      const command = /\$\(CC\)\s+\$\(CFLAGS\)\s+-c\s+(.*?)\s*([\da-z_]+\.(?:c|asm))\s+-o\s+([\da-z_]+\.obj)/i.exec(lines[i + 1] ?? '');
      if (!command || command[2]!.toLowerCase() !== head[2]!.toLowerCase() || command[3]!.toLowerCase() !== object + '.obj') throw Error(`Unparsed rule ${makefile}:${i + 1}`);
      const defines = command[1]!.split(/\s+/).filter(Boolean);
      if (defines.some(d => !/^-D\w+(?:=\w+)?$/.test(d))) throw Error(`Unexpected rule flags: ${defines}`);
      rules.push({ object, source: head[2]!.toLowerCase(), defines, dmpsx, makefile });
    }
  }
  if (new Set(rules.map(r => r.object)).size !== rules.length) throw Error('Duplicate makefile object');
  writeFileSync(join(output, 'manifest.json'), JSON.stringify({ makefiles, origins, rules }, null, 2) + '\n');
  const tools = acceptanceToolchain(buildRoot, undefined, true);
  const originals = new Map(readPsyqLib(readFileSync(join(sdk, 'LIB/LIBHMD.LIB'))).map((m: any) => [m.name.toLowerCase(), m.bytes]));
  const rows = [];
  const run = (name: 'cpp' | 'cc1', args: string[]) => execFileSync(configuredTool(name, buildRoot), args, { cwd: source, stdio: 'pipe' });
  for (const rule of rules) {
    const base = join(output, rule.object), isC = rule.source.endsWith('.c');
    try {
      const cpp = (isC ? configuredFlags('cpp', undefined, buildRoot) : configuredAssemblyCppFlags(undefined, buildRoot)).filter((f: string) => !f.startsWith('-I'));
      run('cpp', [...cpp, ...rule.defines, '-I' + include, rule.source, '-o', base + (isC ? '.i' : '.s')]);
      if (isC) run('cc1', [...configuredFlags('cc1', undefined, buildRoot), base + '.i', '-o', base + '.s']);
      const receipt = assemble(undefined, base + '.s', base + '.OBJ', buildRoot);
      if (!rule.dmpsx && receipt.stages.some((s: any) => s.name === 'psyq-dmpsx' && s.replacements.length)) throw Error('Unexpected DMPSX use in a non-DMPSX rule');
      const original = originals.get(rule.object + '.obj');
      if (!original) throw Error('No original LIBHMD member');
      const comparison = compareObjectBytes(original, readFileSync(base + '.OBJ'));
      rows.push({ ...rule, ...comparison });
    } catch (error) { rows.push({ ...rule, verdict: 'error', error: String(error) }); }
  }
  const exact = rows.filter(r => r.verdict === 'match').length;
  writeFileSync(join(output, 'report.json'), JSON.stringify({ tools, total: rows.length, exact, rows }, null, 2) + '\n');
  console.log(`HMD: ${exact}/${rows.length} whole-file hash-identical; ${rows.filter(r => r.verdict === 'error').length} build errors`);
  for (const r of rows.filter(r => r.verdict !== 'match')) console.log(`${r.object}: ${r.verdict}${'error' in r ? ' ' + r.error : ''}`);
  if (rows.length !== 575 || exact !== 551 || rows.some(r => r.verdict === 'error')) {
    console.error('HMD replay regression: expected 551/575 identical objects and zero build errors.');
    process.exitCode = 1;
  }
});
