# Which toolchain built the early-layout members: Sony NEWS-OS MIPS RISCompiler 2.11

Date: 2026-10-18.

**Scope.** The four members in the `early` LNK layout:

- `POWERON.OBJ`;
- `LIBGUN.LIB` `GUN.OBJ` and `NEWGUN.OBJ`;
- `LIBTAP.LIB` `TAP.OBJ`.

LIBGUN and LIBTAP were dropped from the selection on 2026-10-18 because no assembler the
project had reproduced them. The harness task that brings them back is
`plans/toolchain-provenance/older-build-assembler.md`.

**Method.** This follows [assembler-identification-methodology.md](assembler-identification-methodology.md)
and [compiler-identification-methodology.md](compiler-identification-methodology.md):

1. Read the producer's behaviour from the originals alone.
2. Run real candidate tools on the same input.
3. Compare their output with the original LNK members, whole-file where the source is
   complete.

**Evidence.** Local and git-ignored:

- `build/toolchain-provenance/fix-research/newsos-cc/` (this work: tools, probes, scripts and
  `verify.sh`);
- `build/toolchain-provenance/fix-research/early/` (the record census and the GNU as
  candidates).

The probe sources are reproduced in appendix A, so this note stands without them.

## 1. Bottom line

**Identification.** The members were built with the native compiler suite of Sony's NEWS
workstations:

- **Release:** MIPS RISCompiler 2.11, as shipped in package `CC.211` on the NEWS-OS 4.2.1aRD
  CD.
- **Version strings:** `@(#)MIPS RISCompiler 2.11 (from NEWS-OS 4.0R)`, built 1993-02-03/04.
- **Passes:** `cpp`, `ccom`, `uopt`, `ugen`, `as0` and `as1`.

| Member | Source | Command (driver `cc`, defaults `-mips1 -g0`) |
| --- | --- | --- |
| `POWERON.OBJ` (1995-03-23) | C | `cc -c -O2 -G 0 -EL` |
| `GUN.OBJ` (1997-09-22) | C | `cc -c -O2 -G 0 -EL` |
| `TAP.OBJ` (1997-09-22) | C | `cc -c -O2 -G 0 -EL` |
| `NEWGUN.OBJ` (1997-09-22) | assembly | `cc -c -G 0 -EL` on a `.s` (`cpp` → `as0` → `as1 -O1`) |

**Host and output.** The tools ran on a big-endian NEWS host. Their ECOFF output has
big-endian headers around little-endian code (`file`: "MIPSEL-BE ECOFF"). An early
version of Sony's ECOFF → LNK converter packaged it.

**Results.**

| Check | Result |
| --- | --- |
| POWERON from 5 lines of C through cc 2.11 and `psyq-lnk`'s early layout | **whole-file SHA-256 identical** to `POWERON.OBJ` |
| Three GUN ranges from first-pass C (`0x000–0x0c8`, `0x598–0x6ac`, `0x6ac–0x7a4`) | 181 words equal outside relocated fields; all 55 relocations in GUN's order, including the out-of-byte-order sites GNU as cannot produce |
| TAP `0x000–0x0c8` | 50 words equal; 11 relocations in order |
| NEWGUN `0x204–0x22c`, the site that defined the problem | 10 words equal; 6 relocations in its out-of-byte order |

**Ruled out by running them:**

- GNU as 2.6–2.9.1 and the 1996–97 binutils trunk;
- SN ASPSX 2.86;
- SGI IDO 5.3 and 7.1;
- the older NEWS compiler, MIPS cmplrs 2.0.

**Not yet done.** No whole-file rebuild of GUN, TAP or NEWGUN (section 10).

## 2. What the originals show without any candidate

| Shape | Where | Producer behaviour |
| --- | --- | --- |
| Relocations out of byte order outside jump delay slots | GUN 5, NEWGUN 1, TAP 1. None in the 2,163 standard members (`early/inversions.mts`) | `as1` schedules after expanding macros, and writes relocations in pre-scheduling order |
| Temporaries allocated `$14, $15, $24, $25, $8, $9, …` | GUN, TAP; POWERON calls through `$14` | `ugen`'s allocation order. GCC output starts at `$2`/`$3` |
| A volatile read discarded into `$0` (`lbu $0, 0($17)`) | GUN `0x160`, `0x204` | `ugen` |
| A load hoisted into the previous load's delay slot | NEWGUN `0x20c` (`lw $26, Y` moved above `addi`/`sw`) | `as1`'s basic-block reorganizer |
| Lone REFLO (a REFLO with no REFHI of its own) | 11 sites: GUN 7, TAP 4, NEWGUN 0 | Stores to two parts of one static object share one `lui $1` under cc 2.11 (`probes/lone.c`, appendix A). The 2.11 assembly path keeps both `lui`s |
| JMPADDR to a global defined in the object, with a zero field | 3 sites, all GUN | `as1` keeps the relocation against the external symbol (`JMPADDR ext[StopGun]`, field 0). A call to a static gets a local relocation with the target in the field |
| Hidden IDs ahead of the first visible symbol | GUN 1–17; TAP 1–8, 10–15, 17–18, 20; POWERON none | External-table entries for forward-declared statics (`st StaticProc`, `sc Nil`) take IDs. In assembly, 2.11 also lists referenced `.lcomm` symbols, as `st Nil`, `sc Nil` |
| Uninitialised data in section `f002`, accessed with HI/LO, arrays included | GUN `0x110`, NEWGUN `0xf0`, TAP `0x80` | At `-G 0`, statics are ECOFF `.bss`. The early converter writes ECOFF `.bss` as `f002`, which its section table names `.sbss` |
| Relocated fields hold ECOFF virtual addresses (`.data` after `.text`, `.bss` after `.data`) | GUN, NEWGUN, TAP. POWERON has only an external jump | An ECOFF producer, as for the standard members |

The register order and the `$0` read rule out GCC as the compiler, and with it the earlier
hypothesis of "the MIPS assembler targeted by cc1's `-mmips-as`". The code came from the
MIPS compiler's own `ugen`.

## 3. Candidates

| Candidate | How it was run | Result |
| --- | --- | --- |
| GNU as 2.6, 2.7, 2.8, 2.8.1, 2.9.1, and 1996–97 trunk snapshots | Earlier research, `early/multi.mts` | Every relocation stays in source order. GNU as moves an instruction only into a jump's delay slot |
| SN ASPSX 2.86 (`bin/ASPSX.EXE`, 1999-08-11, from btn-decompilation's vendored PSY-Q SDK) | wine 9.0, on a probe of the NEWGUN site | Inserts `nop`s in load delay slots instead of reordering. Writes an 8-section table with IDs 1–8, `.ctors` and `.dtors`. ASPSX 2.34 (a DOS build) was not run |
| SGI IDO 5.3 and 7.1 (decompals/ido-static-recomp v1.2, Linux builds) | `cc -non_shared -mips1 -EL`; `as1 -coff` writes ECOFF | Same family: `as1` reproduces the NEWGUN site, relocation order included. The C differs: `-O2` reuses one base register for a global's load and store; volatile `n--` reads once where GUN reads twice; at `-G 0`, a pointer stored in `.data` is reloaded after every store through it. IDO 5.3 stamps 3.19 |
| NEWS-OS MIPS cmplrs 2.0 (`CC.200`, `@(#)MIPS cmplrs 2.0 (from NewsOS-4.0) Tue Jul 17 1990`) | The same probes | GUN `0x000–0x0c8` is identical, but `func_598` differs in 60 of 69 words: loop induction and register allocation. Stamps 2.0 |
| **NEWS-OS MIPS RISCompiler 2.11 (`CC.211`)** | The same probes | Every comparison in section 4 passes |

## 4. Controlled comparisons

**How the comparison works.** Each probe is compiled or assembled by the candidate. The
probe's `.text` is compared with the same range of the original LNK member:

- instruction words are compared with their relocated fields masked. Those fields hold
  addresses that depend on section sizes, and the probes don't reproduce those;
- the relocation list is compared in table order, by offset and kind.

The probes are partial reconstructions written for this comparison. Names, declarations
and data layout don't reproduce the members. For example, `g2.c` declares `func_c8` and
`func_598` extern.

| Original range | Probe | cc 2.11 | cc 2.0 |
| --- | --- | --- | --- |
| GUN `0x000–0x0c8`: the getter/setter at `0x0`, SIO set-up at `0x18`, `delay` at `0x8c` | `g1.c` | 50/50 words, 11/11 relocations in order | 50/50 |
| GUN `0x598–0x6ac` (`func_598`, with two hoisted-`lui` regions) | `g4.c` | 69/69 words, 22/22 relocations in order | 9/69, order differs |
| GUN `0x6ac–0x7a4` (`func_6ac`, `RemoveGUN`) | `g2.c` | 62/62 words, 22/22 relocations in order | not run |
| TAP `0x000–0x0c8` | `g1.c` | 50/50 words, 11/11 relocations in order | not run |
| NEWGUN `0x204–0x22c` | `sched.s`, through as0/as1 and through the driver | 10/10 words, 6/6 relocations in order | 2.0 `as1` gives the same order |

**Discriminating details reproduced only by 2.11:**

- `delay` reads the volatile counter twice per iteration (`lw $2, 0($29); lw $14, 0($29)`).
- The setter at `0x0` keeps the old value in `$3`, moves it to `$2` in the return delay
  slot, and builds the global's address twice.
- `func_598`'s loop keeps its pointers in `$3`/`$4`, advanced by 2, and reloads the
  `pos[n]` and `cnt[n]` array elements every iteration. This is where 2.0 differs.
- An explicit `& 0xffff` on an already zero-extended `lhu` survives into the output
  (GUN `0x630`).

## 5. Whole-file result: POWERON

`probes/poweron2.c`:

```c
void go_poweron(void)
{
	EnterCriticalSection();
	(*(void (*)())0xbfc00000)();
}
```

**Pipeline.**

1. `cc -c -O2 -G 0 -EL` under 2.11.
2. Rewrite the ECOFF headers little-endian (`scripts/ecoffle.mts`).
3. Run the harness's `finalizeLnk(…, "early")`, from a copy of `tools/lib/stages/psyqLnk.ts`.

**Output.** 185 bytes, sha256 `f3d7ecabb8efd0ba88e9da52d3639151d85d394b9511766806f7c548fdb463e0`,
the same as `POWERON.OBJ`.

**Symbol order.** The external table follows declaration order. With
`extern void EnterCriticalSection();` above the function, `EnterCriticalSection` takes ID
1, and the object differs from the original. The original declares nothing first, so
`go_poweron` is ID 1 and `EnterCriticalSection` ID 2. Under this toolchain a C member's IDs
start at 1, so the harness's "IDs 1–2 mean assembly" rule doesn't apply.

The project already rebuilt POWERON with GNU as and the early layout. Both tools give the
same bytes for this one function. The register choice (`$14`) and this result show which
one Sony used.

## 6. Supporting provenance

**`MCGUI.O`.** The vendored PSY-Q SDK contains `psx/lib/MCGUI.O`, sha256
`80a17d9a464b560baeeda393c8eabcbd34c458188bada5cfce53a719df03f2cb`, under
`btn-decompilation/tools/vendor/psyq_sdk/psyq/`. It's a Sony object with:

- big-endian ECOFF headers around little-endian code;
- several file descriptors (an `ld -r` result);
- GCC's `gcc2_compiled.` markers;
- version stamp 2.11.

GNU binutils also stamps 2.11, as do the period gas outputs in `early/work/`. But BFD writes
headers in the target's byte order, so a big-endian header on a little-endian object comes
from MIPS tools on a big-endian host. 2.0 stamps 2.0. Sony's environment therefore had the
2.11 tools, at least `ld`.

**The other SDK ECOFF files.** `H2500.IMG`, `CLEANMEM`, `PFLASH` and `CARDFRMT` are
little-endian ECOFF executables stamped 2.11. They don't discriminate.

**The NEWS-OS 4.2.1R `cc(1)` page.** It documents `ccom` as the C front end (IDO uses
`cfe`), `-EL`/`-EB`, `-G` defaulting to 8, and `-O2` invoking `uopt`.

**History.** Sony supplied NEWS workstations for early PlayStation development.

## 7. The tools

### Source and hashes

**The CD.** Sony NEWS-OS 4.2.1aRD:

- volume `NEWS_OS`, volume set `RELEASE_421A_RD`;
- publisher "SONY CORPORATION SM SYSTEMS GROUP";
- created 1993-06-30.

| Input | sha256 |
| --- | --- |
| WinWorld "Sony NEWS-OS 4.2.1R.7z" | `8974b448c915410d9df5122e9f156af97c1093e6be005f131216e579e6cb2891` |
| The ISO inside it (`newsos4.2.1Rad.iso`) | `1d1696a75045c7aa21fdffab7327e10ee974ffdbe2afbd97f0c18a8f48d69899` |
| `CC.211` (compress'd tar) | `f4212fe6c8b6666b0a1e77fae93f1b3e18419fc9a4a03ec205cd35175a466ec9` |
| `CC.200` | `1d6580697a560a0272f0cb2192e5e471b0aaff5c82ecd0d8e1ecfdd1ab1fd1fa` |
| `cc2.11/driver2.11` | `154e8d20f58f2e5cbddda6099bd79d250b39918ee92d1a13ed39446af8dcc5d5` |
| `cc2.11/cpp2.11` | `8585e59414a7bc97eb1043f2dd54799679ac780f27acdbdccdbc8dd07b8c059a` |
| `cc2.11/ccom2.11` | `0cff298fb14db017812ac9690d1853f6b04f0954512729c5eb54d3bfe74d352a` |
| `cc2.11/uopt2.11` | `8308bdc393515f33684a7017b30686626c3cd70012f85cec0f231d7c4618d7c2` |
| `cc2.11/ugen2.11` | `d9c0fc9981af638a01d2851a83afa944321a2edcf5aa8606ab1469ff50455ea9` |
| `cc2.11/as02.11` | `cab40778450c6495738b9cc9e84f4460f19ccaf3b2e1a5bc880f372aec8763a9` |
| `cc2.11/as12.11` | `8ff383f17c129bd09e69fe65915f637eb5099a17c2e4983a3aae47a22df0a859` |
| `cc2.11/ld2.11` | `3e7b8e2329f618820003a12181756b12a6d61d8f1d354d0684b7a7b12099aab0` |
| `POWERON.OBJ` | `f3d7ecabb8efd0ba88e9da52d3639151d85d394b9511766806f7c548fdb463e0` |
| `LIBGUN.LIB` | `c9074581340554b8977ff1cab711f6accf9af2366f4a62121c1e7d218886afc1` |
| `LIBTAP.LIB` | `a06100668af8eb65622036d441413e301f3ffe3e90166ace78e31f701922f7ca` |

**Other files on the CD.** It also carries `FREE_OBJ/GCC.OBJ`, a GCC build for NEWS, and its
source in `FREE_SRC/GCC.SRC`. Neither was used.

**Licensing.** The binaries are proprietary. Like the SDK, they stay out of git.

### Pass command lines

These come from `cc -v` under 2.11. `<root>` is the tree that `COMP_HOST_ROOT` and
`COMP_TARGET_ROOT` name.

```
<root>/usr/lib/cmplrs/cc/cpp -v in.c -DLANGUAGE_C -D_LANGUAGE_C -Dunix -D__unix -D -D__ -D -D__ -Dsony_news -Dsony -Dmips -Dhost_mips -D__sony_news -D__sony -D__mips -DSYSTYPE_BSD -D_SYSTYPE_BSD -I -DMIPSEL -D_MIPSEL -I<root>/usr/include2.11 -I<root>/usr/include > ctmp
<root>/usr/lib/cmplrs/cc/ccom -Xv -EL -Xg0 -O2 -XSctmst < ctmp > ctmf
<root>/usr/lib/cmplrs/cc/uopt -v -G 0 -EL -g0 -O2 ctmf ctmo -t ctmst ctmos
<root>/usr/lib/cmplrs/cc/ugen -v -G 0 -EL -g0 -O2 ctmo -o ctmc -t ctmst -temp ctmgt
<root>/usr/lib/cmplrs/cc/as1 -v -G 0 -p0 -EL -g0 -O2 ctmc -o out.o -t ctmst
```

For a `.s` file:

```
cpp … -DLANGUAGE_ASSEMBLY -D_LANGUAGE_ASSEMBLY … > ctmp
as0 -v -G 0 -EL -g0 -O1 ctmp -o ctma -t ctmst
as1 -v -G 0 -p0 -EL -g0 -O1 ctma -o out.o -t ctmst
```

The empty `-D -D__` pairs are machine-name defines that the driver builds from the host
environment (`machine`, `cputype`). They were empty here. None of the probes uses them.

### Running them on Linux

**The binaries.** They are MIPS big-endian ZMAGIC ECOFF executables for NEWS-OS:

- statically linked and stripped;
- 4.3BSD system calls numbered `1000 + n`, with `$a3` set on error and `$v1` as the second
  result.

The compiler passes use about 20 calls: `exit`, `read`, `write`, `open`, `close`, `unlink`,
`brk`, `lseek`, `getpid`, `access`, `kill`, `ioctl`, `fstat`, `getpagesize`,
`getdtablesize`, `sigvec`, `sigblock`, `sigsetmask`, `gettimeofday`, `getrusage` and
`writev`. The driver adds `fork`, `wait`, `creat`, `execve`, `getpgrp`, `setitimer`,
`dup2`, `sigpause` and 152.

**The research runner.** `newsrun.py`, in the evidence folder, runs the binaries unmodified
under unicorn 2.1.4 in a Python virtualenv:

- a MIPS32 24Kf model, big-endian, with the FPU enabled;
- `fork`, `execve` and `wait` are real host processes, so the real driver runs its own
  passes;
- a no-op per-instruction code hook works around a unicorn crash on long straight-line
  blocks, as in `as1`'s start-up. Instruction counting through unicorn hooks crashed the
  same way, so no instruction counts were measured;
- a full `cc` run takes about 6 seconds.

It isn't a production tool. It's Python, it isn't audited for determinism, and the ECOFF
header carries a timestamp.

**Where they came from.** The NEWS-OS pages and packages were found by searching. The CD
contents were listed with 7-Zip, and the packages are `compress`'d tar files.

## 8. The early converter on this input

These were found while feeding 2.11 output to copies of the harness's ECOFF reader and
`psyq-lnk` (`newsos-cc/scripts/h/`). The harness itself is unchanged.

| Finding | Status |
| --- | --- |
| The input has big-endian headers with the MIPSEL magic stored big-endian | The reader accepts only little-endian; `ecoffle.mts` rewrote the headers |
| `as1` stores the `.mdebug` line count in `s_nlnno`, with `s_lnnoptr` 0 | The reader rejects a nonzero `s_nlnno`; the research copy clears it |
| An external with `sc Nil` and `st StaticProc` (a forward-declared static) is a hidden ID | The reader raised an error; the research copy treats every `sc Nil` external as hidden |
| ECOFF `.bss` → LNK section `f002` | GUN, NEWGUN and TAP. `psyq-lnk`'s early layout writes `f005` |
| A relocation against a defined global → `base(section) + value`, field kept | 3/3 sites in GUN. `psyq-lnk` writes `sym(id)` |
| A lone REFLO's high half = the previous REFLO's word low half | 11/11 sites (`early/rules.mts`). To confirm on a full rebuild |
| Second section header; no SWITCH for empty sections | Already in `psyq-lnk`'s early layout; POWERON is identical |

These are rules for the `early` layout and the reader. Each needs a member that it makes
whole-file identical, as `older-build-assembler.md` step 5 requires.

## 9. Corrections to earlier records

- **`older-build-assembler.md`, "What is known".**
  - It names "the MIPS vendor assembler, which cc1's `-mmips-as` option targets". The
    producer is the MIPS compiler suite itself; GUN and TAP aren't GCC output.
  - Its `.sbss` approach (`-G8`, 8-byte `.lcomm` pieces with `$L` names) imitated the
    converter's `.bss` → `f002` mapping. It isn't needed.
  - Its steps 1–2 (obtain the assembler, install it like the period `as`) become: install
    cc 2.11, plus a way to run NEWS-OS binaries.
- **[assembler-identification-methodology.md](assembler-identification-methodology.md) §3,
  "Packaging variants".** The four members are a different toolchain as well as a different
  encoder version. They don't use ECOFF `.sbss`.
- **The harness's origin classification** ("a member that exports ID 1 or 2 is
  assembly-origin") is a property of GCC + GNU as TUs. POWERON is C and exports ID 1.
- **POWERON's earlier match** under the period GNU as and the early layout is real, but it
  isn't Sony's build.

## 10. What this does not settle

- **No whole-file rebuild of GUN, TAP or NEWGUN.** That needs:
  - complete sources: C for GUN and TAP, assembly in program order for NEWGUN;
  - the converter rules in section 8.
- **NEWGUN's `as1` level.** Only `-O1`, the driver default for `.s`, was tested.
- **The remaining GUN and TAP code.** About 5 KiB of it hasn't been compiled.
- **Cross-checks against Sony's own source.** There is no Sony-written source for these
  members to replay.
- **2.0 versus 2.11.** `func_598` decides it in favour of 2.11, together with `MCGUI.O`'s
  stamp. No other 2.x release was found to test.
- **Running the tools in production.** It needs either an emulator or a port. The research
  runner is neither audited nor in TypeScript.

## 11. Reproduce

`build/toolchain-provenance/fix-research/newsos-cc/verify.sh` runs every comparison above. It
needs `python3`, which creates the unicorn virtualenv, and the harness's `tsx`.

The folder also holds:

- `toolchain/`: `CC.211` and `CC.200` and their extracted trees;
- `scripts/`: `newsrun.py`, `ecoffdump.mts`, `ecoffle.mts`, `compare.mts`, `rebuild.mts`,
  `lnk.mts`, `listing.mts`, and copies of the harness stage and readers under `h/`;
- `probes/`: the sources in appendix A;
- `README.md`.

## Appendix A. Probe sources

`g1.c`, for GUN and TAP `0x000–0x0c8`:

```c
struct SIO { unsigned char data; char pad[3]; unsigned short stat; unsigned short pad2; unsigned short mode; unsigned short ctrl; unsigned short pad3; unsigned short baud; };
static int D_58;
static int D_30;
static volatile struct SIO *sio = (volatile struct SIO *)0x1f801040;
static void delay(volatile int n);

int f0(int x)
{
	int old = D_58;
	D_58 = x;
	return old;
}

void f18(void)
{
	sio->ctrl = 64;
	sio->baud = 136;
	sio->mode = 13;
	sio->ctrl = 0;
	delay(10);
	sio->ctrl = 2;
	delay(10);
	sio->ctrl = 0x2002;
	delay(10);
	sio->ctrl = 0;
	D_30 = 0;
}

static void delay(volatile int n)
{
	while (n--)
		;
}
```

`g2.c`, for GUN `0x6ac–0x7a4`:

```c
struct SIO { unsigned char data; char pad[3]; unsigned short stat; unsigned short pad2; unsigned short mode; unsigned short ctrl; unsigned short pad3; unsigned short baud; };
extern void EnterCriticalSection();
extern void ExitCriticalSection();
extern void _ExitGun();
static int D_28;
static int D_58;
static char D_e9;
static char D_ea;
static volatile struct SIO *sio = (volatile struct SIO *)0x1f801040;
static volatile int *intr = (volatile int *)0x1f801070;
static void delay(volatile int n);
extern void func_c8(int n);
extern void func_598(int n);
void StopGun(void);

int func_6ac(void)
{
	sio->ctrl = 0;
	delay(10);
	if (D_28) {
		func_c8(0);
		func_c8(1);
		if (D_ea)
			func_598(D_e9);
	}
	if (D_58)
		*intr = -2;
	return 0;
}

void RemoveGUN(void)
{
	EnterCriticalSection();
	StopGun();
	intr[1] &= ~0x400;
	intr[0] &= ~0x400;
	_ExitGun();
	ExitCriticalSection();
}

static void delay(volatile int n)
{
	while (n--)
		;
}
```

`g4.c`, for GUN `0x598–0x6ac`:

```c
struct POS { short x; short y; };
extern int _check_gun_flag();
extern void _clear_gun_flag();
static unsigned short *gun_v;
static unsigned short *gun_h;
static unsigned short base_d0;
static char *cnt[2];
static struct POS *pos[2];
static char D_e8;
static char D_e9;
static volatile int *intr = (volatile int *)0x1f801070;
static volatile int *reg44 = (volatile int *)0x1f801100;

void func_598(int n)
{
	int r, i;

	r = _check_gun_flag();
	*cnt[n] = r;
	if (r) {
		for (i = 0; i < *cnt[n]; i++) {
			pos[n][i].x = gun_v[i] - base_d0;
			pos[n][i].y = gun_h[i] & 0xffff;
		}
		_clear_gun_flag();
	}
	D_e9 = D_e8;
	base_d0 = *reg44;
	intr[0] = ~0x400;
	intr[1] |= 0x400;
}
```

`lone.c`: one `lui` shared by two elements of one static gives a lone REFLO. Two separate
statics get two `lui`s.

```c
static int lim[2];
static int a0, a1;
void set_arr(int x, int y)
{
	lim[0] = x + 2;
	lim[1] = y + 2;
}
void set_two(int x, int y)
{
	a0 = x;
	a1 = y;
}
```

`sched.s`, for NEWGUN `0x204–0x22c`. Twenty-four `nop`s in a `noreorder` block sit between
`.set noreorder` and `.set reorder`; they put the branch target where `.L5` is.

```
	.text
	.globl	f
	.ent	f
f:
L5:
	.set	noreorder
	.set	reorder
	lw	$2,cnt
	addi	$2,$2,1
	sw	$2,cnt
	lw	$26,max
	slt	$1,$2,$26
	bne	$1,$0,L5
	j	$31
	.end	f
	.lcomm	cnt,4
	.lcomm	max,4
```
