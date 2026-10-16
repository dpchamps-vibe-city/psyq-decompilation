import json,collections,sys
R=json.load(open(sys.argv[1]))
print("total",len(R))
oc=collections.Counter(r['outcome'].split('(')[0] if r['outcome'].startswith('FAIL') else r['outcome'] for r in R); print("outcomes:",dict(oc))
by=collections.defaultdict(collections.Counter)
for r in R: by[r['lib']][r['outcome'].split('(')[0] if r['outcome'].startswith('FAIL') else r['outcome']]+=1
for l,c in sorted(by.items(),key=lambda kv:-sum(kv[1].values())): print(f"  {l:9}",dict(c))
nr=[r for r in R if r['outcome']=='noreorder-file']
print("noreorder-file: reorder attempt result:",collections.Counter(str(r.get('fallback_outcome')).split(':')[0] for r in nr))
print("  of which reorder form existed with islands:",sum(1 for r in nr if r.get('fallback_outcome')=='reorder-with-islands'))
print("  islands dist (reorder attempt):",collections.Counter(min(r['islands'],6) for r in nr if r.get('fallback_outcome')=='reorder-with-islands'))
re_=[r for r in R if r['outcome']=='reorder']
print("reorder-clean members:",len(re_),"explicit nops dist:",collections.Counter(min(r['explicit_nops'],6) for r in re_))
for r in re_: print("   ",r['tu'],"nops_orig",r['nops_orig'],"explicit",r['explicit_nops'])
bad=[r for r in R if r['outcome'].startswith(('FAIL','EXC','DIFF'))]
print("failures:",len(bad))
for r in bad: print("  ",r['tu'],r['outcome'][:60],str(r.get('diff') or r.get('fallback_error') or r.get('tb'))[:300])
