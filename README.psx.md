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
