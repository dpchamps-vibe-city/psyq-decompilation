# Original translation-unit groupings

Groups follow original object membership, not shared function names or library-wide similarity. Original C source filenames are unknown.

## LIBAPI.LIB — C57.OBJ (ordinal 0)

- Reconstructed source: `src/libraries/libapi/0-c57.c`
- Target member: `lib_6f830259724bafe6_0`
- Members:
  - `InitHeap` — BIOS heap-initialization binding; the allocator implementation is in ROM, not this object.
- Membership evidence: `library-input/redux/original-members.json`, entry `libapi/0-c57`, identifies `LIBAPI.LIB` / `C57.OBJ`, ordinal 0. The selected converted object, `library-input/redux/libapi/0-c57.o`, contains only `InitHeap`; see `build/libraries/disassembly/lib_6f830259724bafe6_0/member.s`.
- Verification: `build/finalization/InitHeap.json` records exact function and whole-member MATCH, passing scope/source-policy gates, and published context. Converted target SHA-256: `75de3c620e849a420e64f9a62a0806f94bfb7d6956753d8bb430ee526406949a`.
