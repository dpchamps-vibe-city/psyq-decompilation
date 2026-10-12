# PSX project setup (library)

Implementation is supplied by the Pi-installed PSX package, not copied into this repository. No target identification or verification is claimed.

1. Put authoritative ELF32 little-endian MIPS ET_REL archives in library-input/ (*.a). project.json initially selects library-input/**/*.a only; select standalone .o files explicitly instead if appropriate. Every configured glob must match.

2. Supply SDK originals, headers and notices under library-input/psyq/ (LIB/ and INCLUDE/). The configured 470 release is a candidate, not measured identity. Existing explicitly configured SDK paths are preserved; no proprietary SDK is downloaded.

3. lib/ is project-owned and trackable: it may contain authoritative library reconstruction targets or SDK extraction/conversion results. Compiled candidates and disposable traces belong in build/, never over authoritative inputs.

4. Original PSY-Q LIB/LNK inputs require a supplied converter (toolchain.json.tools.psyq2elf). Select supported ELF/ar or converted member targets explicitly in project.json; converted-object identity is not original-LNK identity.

5. The installed package supplies its own JavaScript dependencies. Configure external cross-binutils, Python, splat/spimdisasm and any custom compiler executable; missing supported pinned tooling is prepared in build/dependencies/, not in tools/.

6. Bootstrap prepares pinned public support sources automatically. Network/Git are needed only for absent support assets; original inputs and lib/ contents are never deleted. build/ contains disposable outputs, except append-only experiment history, which cleanup preserves.

7. Run /reload in Pi, then /skill:psx-identify-project after supplying inputs. Configure target paths/layout, SDK and compiler choices from evidence before splitting or matching. No EXE addresses, section boundaries, SDK identity or byte verification were inferred by bootstrap.

8. For an EXE, identification must create configs/splat/exe.yaml using the measured header. For a library, review project.json input/header roles before psx_split_project. Verification regenerates the project profile only after successful byte identity.

Bootstrap never clears inputs or overwrites existing project configuration.

## Project commands

These npm scripts forward to the local harness configured in `.pi/settings.json`,
using this repository's `project.json` and `toolchain.json`. They reuse the harness's
installed dependencies; no separate `npm install` is needed here.

```sh
npm run                         # list available commands
npm run build                   # build every configured whole TU
npm run verify                  # build and verify every configured member
npm run check                   # same verification as verify
npm run progress                # fresh, verified reconstruction progress
npm --silent run progress -- --json  # JSON-only progress output
npm run progress -- --remaining  # remaining members
npm run split                   # regenerate configured splits; preserve existing bodies
npm run disassemble             # library disassembly/split route
npm run inventory               # configured member inventory
npm run graph                   # regenerate the call graph
npm run prepare -- MEMBER::SYMBOL
npm run diff -- MEMBER::SYMBOL
npm run compiler-source -- verify --json
```

`check-all` and `split-all` are also available. Full verification still uses the
ordered whole-TU production pipeline; assembly-backed backlog does not count as
decompiled C. For a deliberately scoped owning-member check, use
`npm run library -- check --member MEMBER_ID`. To see the library CLI options, use
`npm run library -- --help`.
