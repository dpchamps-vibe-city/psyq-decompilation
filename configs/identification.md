# Identification — partial library configuration

## Status and authority

Subsequent user-authorized converter builds and a full original-entry census are
recorded in `configs/converter-exploration.md`. That census found missing
LIBGTE variants and LIBSN entries beyond the five failures recorded below.
The user has now selected Redux/COMMON for subsequent conversion; this is
registered in `toolchain.json.tools.psyq2elf` and
`configs/conversion-policy.json`. Six originals are explicitly deferred in
`notes/deferred-sdk-objects.md` and `configs/deferred-sdk-objects.json`.
Current target selection and bytes remain unchanged. The next compiler/assembler
evidence pass is recorded in `configs/toolchain-identification.md`.

This repository selects `relocatable-library` / `elf-ar`, as requested by the
user at bootstrap. The supplied converted ELF objects can be inventoried by
the supported adapter. **No historical compiler, complete SDK distribution,
original-LNK identity, or reconstructed member has been verified.**

The stated goal is now the complete PSY-Q 4.7 original inventory (2,230 entries),
with six unsupported conversions deferred rather than excluded. The active
archive-only legacy target selection still needs a reviewed migration to that
broader inventory. The user identified `../psyq2elf/` and
`../btn-decompilation/tools/vendor/psyq47/` as their initial converter/source trees,
and considers this a 4.7 distribution with carried-over SYS headers. A later
read-only comparison matched all 94 loose source files to the supplied ZIP,
whose included February 2000 release notes explicitly identify runtime 4.7.
See `configs/conversion-research.md` and `configs/identification-origin.json`
for the read-only origin comparison. No target inputs were changed or committed.

## Input identities and measured observations

The complete path/size/SHA-256 inventory is retained in
`configs/identification-assets.json` (2,231 supplied files, 30,288,584 bytes).
Its working copy is `build/identification/assets.json`.

- `library-input/converted/lib/`: 23 ar archives, 2,146 individual `.o` files,
  and `converted.txt` (23,139,383 bytes).
- `library-input/converted/include/`: 61 `.h` files.
- No original PSY-Q LIB/LNK files are supplied. `extracted/` and `lib/` are empty.
  The configured originals directory, `library-input/psyq/LIB/`, is absent.
- The archive selection yields 2,142 members and 2,573 identifiable function
  labels, in 2,116 members. The other 26 members remain in verification scope;
  none has a nonempty executable section without an identifiable function.
- All 2,573 function bounds are inferred from size-zero symbols, not proven
  original function-size annotations.
- All selected archive-member ELF headers are ELF32, little-endian, MIPS,
  ET_REL; flags are `0x1000` (o32/MIPS-I), OSABI is 3 (GNU).
  These are properties of the **converted objects**, not proof of original
  compiler/OS identity. No RAM addresses or splat sections were invented.
- Allocated section counts: `.text` 2,116; `.bss` 74; `.data` 178;
  `.rdata` 146; `.sbss` 3. GP-related placement does not establish a unique `-G`
  threshold. The adapter accepts the selected members' relocation formats.

### Header release evidence

55 headers contain `Run-time Library Release 4.7`; five contain `4.6`:
`sys/ioctl.h`, `sys/types.h`, `sys/fcntl.h`, `sys/file.h`, `sys/errno.h`.
One header has no such marker. Predominantly 4.7-labelled headers support
retaining **470 as a candidate**. Subsequent comparison found all 61 headers
byte-identical to the user-designated original INCLUDE tree: its five SYS
headers already say 4.6. This supports the user's carryover explanation; those
markers alone are not evidence that conversion mixed header releases.
A later read-only comparison matched these originals to the supplied
`Psy-Q_47.zip`, whose release notes explicitly identify 4.7. This establishes
content/package consistency for this supplied set, not a unique historical
compiler/assembler version or independent authentication of its publisher.
No linked-image signature scan was attempted: the deep scanner requires image
geometry and is not a library identification adapter.

### Conversion provenance and omissions

Representative supplied objects (`libspu/version.o`, `libcd/c_002.o`,
`libgpu/sys.o`, `mcgui.o`) contain notes naming `psyq-obj-parser`, the
`pcsx-redux project`, and its GitHub URL. No producing-converter
revision/executable hash or authoritative original-to-member mapping is supplied. Original file hashes from
the subsequently user-designated external tree are now recorded in
`configs/identification-origin.json`; originals have not been imported into this
project. All 2,231 supplied converted files match that tree's converted directory.
The Jype checkout's revision is known, but these outputs identify Redux; the
actual Redux executable/revision/options remain unresolved.
`libspu/version.o` contains a compiled-time string `Feb 16 2000 22:00:32`;
this does not establish a distribution revision or compiler identity.

The supplied log records 2,146 completed conversions and **five failures**:

| Logged input | Failure |
|---|---|
| `2mbyte.obj` | Unsupported relocation expression type: 12 |
| `8mbyte.obj` | Unsupported relocation expression type: 12 |
| `libsn/snmain.obj` | Section `.sbss` looks like bss, but has data |
| `noheap.obj` | Unsupported relocation expression type: 12 |
| `none3.obj` | Unsupported relocation expression type: 12 |

Those outputs are absent. Do not claim that the converted set covers every
original SDK member. Recovery of those inputs needs originals and a supported
conversion fix/adapter. Matching converted ELF would not prove original LNK
encoding identity, even after provenance is supplied.

### Explicitly unselected inputs

The current archive-only scope excludes these distinct, nonduplicate top-level
objects: `mcgui.o`, `mcgui_e.o`, `noprint.o`, `poweron.o`, all under
`library-input/converted/lib/`. Their hashes are in the asset inventory and
`build/identification/summary.json`. Ask whether to add them as explicit
`target.standaloneObjects`; do not silently add or omit them from a claim of
complete SDK reconstruction. The per-archive `.o` directories are member copies
and must not be selected alongside their archives.

## Configured choices, not historical facts

- Narrowed the archive glob to `library-input/converted/lib/*.a`: it matches the
  same 23 archives and preserves every selected member ID/hash from the
  bootstrap selection. No new target scope was assumed.
- Immutable reference headers now point to `library-input/converted/include`.
  Editable declarations/types belong in `include/library`. `common.h` remains
  the only selected source/m2c context header; no unrelated SDK umbrella was
  introduced across all library families.
- Include search paths are `include`, `include/library`, and the actual supplied
  reference directory. SDK `convertedDir` and `headers` point to the supplied
  converted tree. `originalDir` remains an unresolved expected-input path.
- GCC 2.95.2, `-O2 -G8`, ASPSX 2.80 emulation, and the other flag arrays remain
  unchanged **bootstrap candidates**, not measured historical choices.
  Another compiler/release or mixed compiler builds remain competing hypotheses.
  No real-target production comparison has validated these candidates.
- `profiles`, `containerProfiles`, and `memberProfiles` remain empty.
  `configs/flag_overrides.mk` contains comments only. No per-TU flag override,
  policy exception, matching campaign, or autonomous commit was enabled.

## Tool availability

`build/identification/tool-availability.json` records the initial preflight,
when the configured runtime GCC `cc1` was missing. It has subsequently been
provisioned through the supported public recipe at
`build/dependencies/compiler/gcc-2.95.2-psx/cc1`. The candidate reports
GNU C 2.95.2 19991024 (release), `mips-sony-psx`; its compiler/build hashes are
recorded in `configs/toolchain-identification.json` and the build-cache receipt.
This availability does not prove it generated the originals.

Available: MIPS cross-cpp and cross-binutils, Python, splat, spimdisasm, and the
pinned maspsx/m2c sources. Observed versions: cross-cpp 12.4.0, GNU assembler
2.42, Python 3.12.3. The configured cpp argument smoke check succeeds; it proves
argument acceptance only, not target matching. `maspsx --help` and verified
patched `m2c --help` succeed. `psx_prepare_tooling` verifies/prepares pinned public
sources and patched m2c. The later explicit compiler provisioning is documented
in `configs/toolchain-identification.md`; no proprietary tool binary was fetched.

## Commands and report paths

All commands ran from the target repository root, not the harness checkout.

- `psx_identify_project({json: true})`: supported ELF/ar inventory succeeds;
  historical compiler detection explicitly reports `undetermined`.
- The same installed identification implementation was run through its
  `tools/lib/scriptHost.ts` with explicit `--project "$PWD" --json` to retain
  `build/identification/identify.initial.json` and
  `build/identification/identify.json` (before/after path corrections).
- A local read-only Python scan recorded all input hashes, release markers,
  conversion failures, header ABI counts, selected-member parity, and tool
  availability. Summary: `build/identification/summary.json`.
- `mips-linux-gnu-readelf -h -S -r` on `libcd/c_002.o` and `mcgui.o`:
  `build/identification/libcd-c_002.readelf.txt`,
  `build/identification/mcgui.readelf.txt`.
- `psx_prepare_tooling({})`: pinned sources and patched m2c prepared successfully.
- `psx_generate_project_profile({write: true})`: wrote
  `configs/project-profile.md`, explicitly reporting byte identity NOT VERIFIED.
  Read this identification record alongside that configured-choice profile:
  compiler-dependent analysis remains unavailable until `cc1` is provisioned.
- `psx_project_progress({})`: 0/2,142 members, 0/2,573 function labels, and
  0/1,186,236 code bytes verified. This is inventory/progress, not a byte check.
- Rehashed all 2,231 supplied files after configuration: no input changes.
  The three edited configuration JSON files parse; no live `src/` C TU exists.
- Help/smoke outputs: `build/identification/{maspsx-help.txt,m2c-help.txt,
  cpp-smoke.i,cpp-smoke.stderr}`.

## Blockers and handoff

1. Reconcile the original-LNK/converted-ELF versus production GCC/GAS
   representation contract. A build-only real SDK member probe reproduces its
   six executable words/relocations but fails strict whole-member identity on
   padding, section alignment, ABI flags and additional allocated metadata.
   This persists against fresh Redux/COMMON output. Do not mask these differences
   or guess compiler flags to hide them; see `configs/toolchain-identification.md`.
2. Migrate the active legacy archive selection to a reviewed, ordinal-preserving
   Redux/COMMON set covering the supported originals and standalone objects.
   Restore the LIBGTE/LIBSN coverage gaps; keep six deferred originals in the
   separate full-SDK completion ledger.
3. Original hashes and source/member mapping are recorded in
   `configs/identification-origin.json` and converter exploration reports.
   The selected producing converter/policy is pinned in
   `configs/conversion-policy.json`; this does not retrospectively identify the
   old converter invocation or prove LNK-to-ELF fidelity.
4. Validate additional members with the provisioned GCC 2.95.2 candidate after
   resolving the representation gate, not a synthetic smoke test or score alone.
   The release document points to GCC 2.95; 45 parser-confirmed LIBSN runtime
   source paths name GCC 2.8.0. Neither uniquely identifies every member's compiler.
5. Determine historical assembler semantics and compiler/ABI flags without
   assuming ASPSX 2.80/-O2/-G8 merely because the template selected them.

Splitting/building and whole-member verification are deferred pending the
representation contract and reviewed target-set migration. The supported
candidate compiler is now available. Only one build-local C probe was authored;
no live source stub or reconstructed C TU was integrated. Profile generation and progress reporting describe
this **partial configuration**, not byte-verified output. Acceptance must compare
entire owning members, including code/data/BSS/COMMON, symbols and symbolic
relocations; function-local agreement is insufficient.
