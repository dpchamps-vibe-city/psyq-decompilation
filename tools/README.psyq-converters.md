# PSY-Q converter exploration

## Installed public source

`tools/pcsx-redux/` is a sparse Git checkout of
https://github.com/grumpycoders/pcsx-redux at
`78e777e160d840c37b17872d864a8d896681d191`, with only parser/support sources and
three build dependencies initialized at the upstream gitlink pins.
No emulator, SDK, or system installation is performed.

Build and run from the project root:

```sh
tools/build-psyq-obj-parser.sh
tools/psyq-obj-parser INPUT.OBJ -c -o build/OUTPUT.o
```

Inputs precede switches. `-c` preserves ELF COMMON; upstream defaults to
converting COMMON into BSS. No flags are implicitly added by this raw wrapper.

`toolchain.json.tools.psyq2elf` selects the separate `tools/psyq2elf-redux`
adapter, which accepts `INPUT.OBJ OUTPUT.o` and explicitly supplies `-c -o`
to upstream. Its selected policy and hashes are in
`configs/conversion-policy.json`.
`-h` prints help but upstream returns 255 for it.
The executable resides in `build/converters/pcsx-redux/<commit>/`.

The build script compiles the unmodified upstream parser and the small file/fmt
support subset using host g++ and zlib. It deliberately does not invoke the
emulator's Makefile or fetch unrelated submodules. Required local tools:
Git, g++ with C++23 support, and zlib development headers/library.
Public dependency pins and executable/source hashes are retained in
`configs/converter-exploration.json`.

## Reproduce the exploration

`tools/explore-psyq-converters.mjs` uses the installed harness's existing
LIB v1/v2 readers and symbolic ELF object comparator. Supply the harness root
and an explicitly selected original SDK LIB directory:

```sh
node --import /PATH/TO/HARNESS/node_modules/tsx/dist/loader.mjs \
  tools/explore-psyq-converters.mjs /PATH/TO/HARNESS /PATH/TO/SDK/LIB --all
```

Omit `--all` for the eleven-member focused set. The current comparison also
expects a Jype binary built under `build/converters/jype-cba9b60/psyq2elf`.
That binary was built directly from the user's existing, unmodified Jype
checkout; its source/build identities are recorded in the exploration receipt.
There is no bundled proprietary input or automatic SDK download.

Original members are identified by archive and **ordinal**, not only filename.
Outputs, logs, extracted LNK inputs, hashes and reports stay below
`build/converters/exploration/{focused,all}/`. Failed retries cannot reuse stale
successful outputs. No conversion modifies `library-input/` or `lib/`.

Named old `.o` copies are diagnostic baselines only. For duplicate member names,
`ambiguousNamedBaseline` marks that their precise original mapping is unknown.
Successful conversion or agreement with an older converted object does not
prove faithful original-LNK semantics. Redux/COMMON is now selected in
`toolchain.json` for subsequent conversion; existing targets were not replaced.
The six deferred originals remain inventoried in
`configs/deferred-sdk-objects.json` and `notes/deferred-sdk-objects.md`.

See `configs/converter-exploration.md` for measured findings and remaining
limitations. The nested Git checkout remains uncommitted; decide Git-submodule
or pinned dependency provisioning before publishing this repository.
