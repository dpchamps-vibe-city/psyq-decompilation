# SN/Psy-Q compiler research: community findings

Research date: 2026-10-17. Scope: public SN/Psy-Q compiler research, especially the distinction between the distributed compiler and the producer of prebuilt library objects. This is a literature/source inspection, not a locally reproduced compiler experiment. No compiler was installed, run, patched or selected, and no project configuration changed. No historical producer is identified for `LIBAPI/REALLOC3` by this research.

## 1. A source-derived SN compiler reconstruction exists

Repository: <https://github.com/nocato/homebrew-psyq>

Inspected revision: `bdee891005a0aec6bf6fe40e504cf068ebf38caf` (2023-04-03).

The README describes a Linux reconstruction of Psy-Q 4.4's GCC 2.8.1 `CC1PSX.EXE`, built from upstream GCC plus changes imported from the SDK compiler sources. It reports that replacing the original compiler in `mgs_reversing` produces the same game binary. This is author-reported compatibility, not proof that this compiler built all Psy-Q 4.4 library members.

There is inspectable supporting material beyond the README:

- Import commit `a80e2da663e2488cc7e19d7723cdfce529a5f378`: <https://github.com/nocato/homebrew-psyq/commit/a80e2da663e2488cc7e19d7723cdfce529a5f378>. It changes `gcc/config/mips/mips.h` and adds `psx.h` and `xm-psx.h` under `gcc-2.8.1_psyq-4.4/`.
- Git history distinguishes importing upstream release files, importing Psy-Q target files, subsequent target/build fixes, and CRLF output support.
- The checked-in workflow runs a compatibility test: <https://github.com/nocato/homebrew-psyq/blob/bdee891005a0aec6bf6fe40e504cf068ebf38caf/.github/workflows/build.yaml>.
- The test replaces `CC1PSX.EXE` in pinned SDK revision `dac47a48d0ed6d255b26a5dc104ce319a6bbe963` and builds pinned MGS revision `a94e1f6026ea303ce5f76b6eb9e922dcbe226265`: <https://github.com/nocato/homebrew-psyq/blob/bdee891005a0aec6bf6fe40e504cf068ebf38caf/build-scripts/test-old-school.sh>.

Neither that test nor its SDK/game inputs was downloaded or executed here. The original SDK source archive was not independently authenticated against the imported target files.

A newer wrapper, <https://github.com/jaysonvirissimo/psyq-wasm>, pins this same source revision. Its `PROVENANCE.md` makes the dependency explicit: <https://github.com/jaysonvirissimo/psyq-wasm/blob/main/PROVENANCE.md>. Its differential oracle is a native build of the same reconstructed sources, so its tests are not independent confirmation against an original SN executable.

## 2. Reports directly concerning original library objects

### Tenchu

Source: <https://github.com/Fuuzetsu/tenchu-decomp/blob/47c1ee292a779704865963636fe5672b1f9455fb/docs/toolchain.md>.

The authors report extracting complete original SDK members and comparing them with the game, rather than attributing compilers solely from archive names:

- `GS_106/110/111/113/121/122` reproduce under GCC 2.7.2-compatible generation.
- `GS_119.OBJ` has identical content in SDKs 4.3–4.6 and reproduces under both GCC 2.8.0 and 2.8.1. It therefore does not uniquely identify either compiler.
- `GS_105` and `GS_125` are explicitly described as compiler-invariant on their measured source programs.
- `GS_107.OBJ` is reported identical in the 4.5 and 4.6 archives, but its ordinary structure-copy sources and RA-only epilogues require a reconstructed backend in that project. Released SN 2.8.1 is among the compared references.

The GS_107 section explicitly says its backend patch is a reconstruction from observed output, **not a claim that the patch is the exact historical Sony source**. That distinction is important. Reported symptoms include block-copy splitting and the ordering of `lw ra`, stack adjustment and return; these are relevant research leads for return-tail mismatches, not a diagnosis of our helper.

An identical member across releases establishes identical content, not whether it was retained or rebuilt identically. A matched reconstructed source establishes compatibility, not a unique historical compiler version. None of these experiments was reproduced locally.

### Digimon Digital Card Battle

Inspected revision: `6c9caf124450cafa1b5f402d03d82b90bb02d16e`.

- <https://github.com/ReGame-Labs/dcb_decomp/blob/6c9caf124450cafa1b5f402d03d82b90bb02d16e/README.md>
- <https://github.com/ReGame-Labs/dcb_decomp/blob/6c9caf124450cafa1b5f402d03d82b90bb02d16e/config/us/psyq_objects.txt>
- <https://github.com/ReGame-Labs/dcb_decomp/blob/6c9caf124450cafa1b5f402d03d82b90bb02d16e/tools/sn_cc1.py>
- <https://github.com/ReGame-Labs/dcb_decomp/blob/6c9caf124450cafa1b5f402d03d82b90bb02d16e/tools/patch_cc1.py>

The project assigns different compiler configurations to different Psy-Q 4.7 library units. However, those configurations include extensive binary patches to compiler passes. `sn_cc1.py` alters return-insn eligibility, epilogue blocking/liveness, post-reload CSE, register availability, scratch allocation and block-move scheduling. The other patch script imports selected GCC 2.8 behaviors into a 2.7.2 build and includes an explicitly empirical register-class rule.

These are useful descriptions of observed incompatibilities. They are **not authenticated historical SN compiler releases**, and the scripts' assertions that they recreate the library's compiler are stronger than the provenance demonstrated by the scripts themselves. Their success reports do not automatically satisfy this project's original-owning-member and clean-source gates.

## 3. Different SN builds must not be collapsed into one GCC label

### Tombi

Source: <https://github.com/afsenovilla/Tombi-Decomp/blob/d8a8a5f0fe78eeddc589b69fba86f5b755dc566b/notes/compiler.md>.

The note's leading update reports that an older DOS `2.7.2.SN.1` compiler produced a different prologue schedule and blocked dozens of functions; a Win32 compiler from their '4.3' distribution became the reference. Their native fast checker is reported to reproduce 628 of 636 reference-verified functions, not all of them.

The document retains an older DOS/SN.1 conclusion below the update. Do not merge those contradictory paragraphs into a single assertion about the current reference compiler, or infer the Win32 compiler's exact version solely from the archive label. Its actual binary needs an independently recorded banner and hash.

### Armored Core

Source: <https://github.com/Wyrelade/Armored-Core-Decomp/blob/1be6d78814f2f332f5f2c5e51eaa62ca33cdefbb/README.md>.

The authors report comparing eleven game functions across nine compiler builds, selecting `CC1PSX` GCC 2.7.2 SN32 3.7.0002, compatible on that corpus with the decompals 2.7.2 PSX build. Their return-slot observations are useful fingerprints. Their Psy-Q library functions remain assembly, however: this is evidence about that game's compiler, not the producer of its SDK libraries. A finite source corpus does not uniquely identify a historical compiler or rule out all other source/flag combinations.

## 4. Mixed SDK dumps are a known problem

Lameguy64's 2020–2021 SDK tutorial distinguishes a commonly circulated older dump from a cleaner 1998 Programmer's Tool CD dump, and says the older dump includes newer compiler executables absent from the CD:

<https://www.breck-mckye.com/psnoobsdk-docs/setup.html>.

This independently supports treating filenames, top-level READMEs and SDK version labels as insufficient executable identification. It does not identify a library's producer.

## Findings and next discriminating work

- There is a concrete SN-source-based reconstruction to inspect; we do not need to begin by inventing optimizer changes.
- Community projects report both ordinary released-compiler matches and library objects needing reconstructed variants. Keep those classes separate.
- Exact original SN build identity matters. A native replacement matching many functions is not automatically equivalent on all functions.
- The strongest next compiler experiment is against original SN executables or a source reconstruction calibrated against them, using the whole `87-realloc3` member and a small broader corpus.
- The published Tenchu complete-member comparisons are candidates for independent calibration, not authority to apply their compiler patches here.
- No located source establishes which compiler built our exact allocator member. No production toolchain change follows from this literature review alone.

Search hygiene: several Brave-indexed `juandav/*` pull-request results were unavailable or did not correspond to the current repositories' PR numbering. They were not used as evidence. Decompedia's PSY-Q page could not be fetched because its host did not resolve; its snippets were not promoted to checked findings.
