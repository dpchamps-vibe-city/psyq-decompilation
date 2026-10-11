#!/usr/bin/env node
// Read-only original/target investigation. Only writes below this project's build/.
// Requires the installed harness's tsx loader to import its checked LIB/ELF adapters.
import fs from 'node:fs';
import path from 'node:path';
import {fileURLToPath, pathToFileURL} from 'node:url';
import {spawnSync} from 'node:child_process';

const [harnessArg, originalsArg, mode] = process.argv.slice(2);
if (!harnessArg || !originalsArg || (mode && mode !== '--all')) {
  console.error('Usage: node --import <installed tsx loader> tools/explore-psyq-converters.mjs <harness-root> <original-LIB-dir> [--all]');
  process.exit(2);
}
const root = path.resolve(path.dirname(fileURLToPath(import.meta.url)), '..');
const harness = path.resolve(harnessArg), originals = path.resolve(originalsArg);
const {readPsyqLib, hash} = await import(pathToFileURL(path.join(harness, 'tools/lib/psyqMembers.ts')));
const {compareRelocatableObjects, readRelocatableObject} = await import(pathToFileURL(path.join(harness, 'tools/lib/relocatableObject.ts')));
const output = path.join(root, 'build/converters/exploration', mode === '--all' ? 'all' : 'focused');
fs.mkdirSync(output, {recursive:true});
const mkdir = p => fs.mkdirSync(p, {recursive:true});
const writeJSON = (p, value) => fs.writeFileSync(p, JSON.stringify(value,null,2)+'\n');
const members=[];
for (const filename of fs.readdirSync(originals).sort()) {
  const input=path.join(originals,filename);
  const extension=path.extname(filename).toLowerCase();
  if (!fs.statSync(input).isFile() || (extension!=='.lib' && extension!=='.obj')) continue;
  const bytes=fs.readFileSync(input);
  const library=path.basename(filename,path.extname(filename)).toLowerCase();
  const objects=extension==='.lib' ? readPsyqLib(bytes) : [{name:filename,ordinal:0,offset:0,bytes}];
  for (const object of objects) {
    const stem=path.basename(object.name,path.extname(object.name)).toLowerCase();
    const id=extension==='.lib' ? `${library}/${object.ordinal}-${stem}` : `standalone/${stem}`;
    const staged=path.join(output,'inputs',`${id}.obj`); mkdir(path.dirname(staged));
    fs.writeFileSync(staged,object.bytes);
    const baseline=path.join(root,'library-input/converted/lib',extension==='.lib' ? library : '',`${stem}.o`);
    members.push({id,input,inputSha256:hash(bytes),member:object.name,ordinal:object.ordinal,sourceOffset:object.offset,
      sourceSha256:hash(object.bytes),staged,baseline:fs.existsSync(baseline)?baseline:null});
  }
}
const nameCounts=new Map();
for (const member of members) {
  const key=`${member.input}::${member.member.toLowerCase()}`;
  nameCounts.set(key,(nameCounts.get(key)??0)+1);
}
for (const member of members) member.ambiguousNamedBaseline=nameCounts.get(`${member.input}::${member.member.toLowerCase()}`)>1;
const focused = new Set(['2mbyte','8mbyte','noheap','none3','snmain','c_002','sys','s_ini','ssopenp','adddf3']);
const selected = mode==='--all' ? members : members.filter(m=>focused.has(path.basename(m.staged,'.obj').replace(/^\d+-/,'')));
const pin='78e777e160d840c37b17872d864a8d896681d191';
const tools=[
  {name:'redux-default',executable:path.join(root,'build/converters/pcsx-redux',pin,'psyq-obj-parser'),flags:[]},
  {name:'redux-common',executable:path.join(root,'build/converters/pcsx-redux',pin,'psyq-obj-parser'),flags:['-c']},
  {name:'jype',executable:path.join(root,'build/converters/jype-cba9b60/psyq2elf'),flags:[]}
];
for (const tool of tools) tool.sha256=hash(fs.readFileSync(tool.executable));
writeJSON(path.join(output,'inputs.json'),members);
const rows=[];
for (const member of selected) {
  for (const tool of tools) {
    const dest=path.join(output,tool.name,`${member.id}.o`); mkdir(path.dirname(dest));
    // A previous successful output must not turn a failed retry into a success.
    if(fs.existsSync(dest)) fs.unlinkSync(dest);
    const argv=tool.name==='jype' ? [member.staged,dest] : [member.staged,...tool.flags,'-o',dest];
    const run=spawnSync(tool.executable,argv,{cwd:root,encoding:'utf8',timeout:10000,maxBuffer:16*1024*1024});
    const log=dest+'.log'; fs.writeFileSync(log,(run.stdout??'')+(run.stderr??''));
    const row={id:member.id,tool:tool.name,ambiguousNamedBaseline:member.ambiguousNamedBaseline,argv,status:run.status,signal:run.signal,error:run.error?.message,
      output:fs.existsSync(dest)?dest:null,log};
    if (run.status===0 && row.output) {
      const bytes=fs.readFileSync(dest); row.sha256=hash(bytes);
      try {
        const object=readRelocatableObject(bytes);
        row.object={flags:object.flags,sections:[...object.sections].filter(([,s])=>s.flags&2).map(([name,s])=>({name,type:s.type,flags:s.flags,size:s.size,alignment:s.alignment})),
          common:object.symbols.filter(s=>s.section==='COMMON'),relocations:object.relocations.length};
        if(member.baseline) {
          row.byteIdentical=bytes.equals(fs.readFileSync(member.baseline));
          row.comparison=compareRelocatableObjects(fs.readFileSync(member.baseline),bytes);
        }
      } catch(error) { row.adapterError=String(error); }
    } else {
      const text=(run.stderr??'')+(run.stdout??'');
      row.failure=text.match(/Conversion failed: ([^\r\n]+)/)?.[1]??text.trim().split('\n').slice(-2).join(' ')??'no output';
    }
    rows.push(row);
  }
}
const summary={scope:mode==='--all'?'all supplied originals':'focused originals',inputMembers:members.length,testedMembers:selected.length,tools:tools.map(t=>({...t})),byTool:{},rows};
for (const tool of tools) {
  const r=rows.filter(r=>r.tool===tool.name);
  const failures={}; for(const row of r.filter(r=>r.status!==0)) failures[row.failure]=(failures[row.failure]??0)+1;
  summary.byTool[tool.name]={attempted:r.length,succeeded:r.filter(r=>r.status===0&&r.output).length,failed:r.filter(r=>r.status!==0||!r.output).length,
    adapterRejected:r.filter(r=>r.adapterError).length,baselineCompared:r.filter(r=>r.comparison).length,
    wholeObjectMatches:r.filter(r=>r.comparison?.verdict==='match').length,rawByteIdentical:r.filter(r=>r.byteIdentical).length,
    objectsWithCommon:r.filter(r=>r.object?.common.length).length,failures};
}
writeJSON(path.join(output,'report.json'),summary);
console.log(JSON.stringify({scope:summary.scope,inputMembers:summary.inputMembers,testedMembers:summary.testedMembers,byTool:summary.byTool},null,2));
if(mode!=='--all') for(const row of rows) console.log(row.id,row.tool,row.status,row.failure??row.comparison?.verdict??'converted',row.object?.common.length??'');
console.log('Full report:',path.relative(root,path.join(output,'report.json')));
