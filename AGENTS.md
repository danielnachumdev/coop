# COOP – Agent Context

Implementation guide for coding agents changing **coop**. Product pitch and user quickstart: [`README.md`](README.md).

---

## Orientation

| Question | Answer |
| -------- | ------ |
| What is this? | C11 library adding Python-like OOP (dynamic objects, types, builtins) |
| Library code | `coop/` (umbrella: `coop/__init__.h`) |
| Toolchain | CMake ≥ 3.22, C11 (`CMAKE_C_STANDARD 11`) |
| Tests | `tests/` — custom framework in `tests/__framework__.h`; **never delete** |
| Secrets | None expected; do not commit API keys or credentials |

```text
.
├── coop/                  # Library: backend, builtins, log, memory
│   ├── backend/           # CNode, linked list, stack, hash set
│   ├── builtins/          # Object, types, functions, macros.h
│   ├── log/               # Logger
│   └── memory/            # Allocator (linked-list / hash-set strategies)
├── tests/                 # Backend + builtins suites (`__main__.c`)
├── examples/              # e.g. animals.c inheritance demo
├── diagrams/              # Architecture / flow visuals
├── main.c                 # Demo executable target `coop`
├── build_documentation.c  # Regenerates Documentation.md (with helper scripts)
├── CMakeLists.txt
├── README.md              # Marketing / quickstart
└── Documentation.md       # Generated type/method dump (addresses are runtime)
```

There is currently **no** `.github/` on `main`. Semver labels already exist on the repo; thin CI via [`danielnachumdev/actions`](https://github.com/danielnachumdev/actions) `@latest` may land separately—do not invent workflows here unless asked.

---

## Develop

```bash
cmake -B build
cmake --build build                 # targets: coop, tests, build_documentation
./build/coop
./build/tests
```

| Task | Command |
| ---- | ------- |
| Configure | `cmake -B build` |
| Build all | `cmake --build build` |
| Demo | `./build/coop` |
| Tests | `./build/tests` |
| Regen docs binary | `cmake --build build --target build_documentation` then run `./build/build_documentation` (optional Python helper `build_documentation.py`) |

`main.py` is a legacy Windows→WSL `gcc` helper and references files that are not part of the CMake layout—prefer CMake.

Do not commit `build/`, `cmake-build-debug/`, or `*.out` artifacts (see `.gitignore`).

### CMake notes

- `add_executable(coop …)` — `main.c` + all `coop/**/*.c`
- `add_executable(tests …)` — `tests/__main__.c` + test tree + library sources
- `add_executable(build_documentation …)` — dumps builtin type dirs for `Documentation.md`

---

## Code style & domain notes

- Entry umbrella: `#include "coop/__init__.h"`. Call sites use macros from `coop/builtins/macros.h` (`DEF`, `explicitgetfunc` / `explicitsetfunc`, `cast`, …)—preserve macro patterns; they carry IDE type info.
- Every value is an `Object` (`type`, `attributes`, `data`). Types are objects; attribute lookup walks inheritance (`getattr` / `setattr` / `hasattr`).
- Lifecycle: `__attribute__((constructor)) coop_setup` installs the global allocator and `init_builtins`; `coop_teardown` clears the allocator on exit.
- Memory: allocate with the custom allocator APIs (`acquire` / `release` / `clear`) rather than ad-hoc `malloc` for library-owned objects.
- Logging: `coop/log` severity levels (`DEBUG`, `INFO`, `WARN`, `ERROR`).
- `Documentation.md` is generated and embeds **runtime function addresses**—regenerate rather than hand-edit addresses.
- Prefer extending existing type/test modules under `coop/builtins` and `tests/test_*` over one-off demos in `main.c`.

---

## PRs and labels

1. Branch off `main`; open a PR into `main`.
2. Attach **exactly one** semver label when Semver CI is enabled: `noBump` | `bumpPatch` | `bumpMinor` | `bumpMajor`. Docs-only → `noBump`.
3. Prefer required check names **`CI / CI`** and **`Semver / Semver`** once thin workflows exist.
4. Change shared CI/semver behavior in **`danielnachumdev/actions`**, not by re-vendoring here.

### Repo gates

- Labels for semver already configured on GitHub.
- No force-push to `main`.

---

## Sensitive / ignored

Do not commit secrets, local IDE junk beyond tracked `.idea` policy, or build trees. Respect `.gitignore` (`/cmake-build-debug/`, objects, `*.out`, …).
