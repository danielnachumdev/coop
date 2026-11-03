# COOP (C with OOP)

**Object-oriented programming in C, inspired by Python.**

COOP gives C a dynamic object system: classes, inheritance, attributes, and Pythonic builtins (`getattr`, `setattr`, `isinstance`, `len`, `print`, …) without leaving C11.

## Why COOP?

Plain C has structs and function pointers, but not a uniform runtime model for types, methods, and inheritance. COOP wraps every value in an `Object`, stores attributes dynamically, and treats types as objects—so you can prototype OOP patterns (and some metaprogramming) while staying in C.

- Dynamic `Object` / `Attribute` model with runtime type info
- Built-in types: `Type`, `String`, `Integer`, `Boolean`, `List`, `Array`, `Set`, `Union`, `Function`, …
- Inheritance helpers (`super`) and attribute lookup up the type chain
- Custom allocator (`acquire` / `release` / `clear`) plus a severity-based logger
- Macros (`DEF`, `explicitgetfunc`, …) that keep call-site type information for IDEs

## Quick start

Requires **CMake ≥ 3.22** and a C11 compiler.

```sh
cmake -B build
cmake --build build
./build/coop          # demo binary (main.c)
./build/tests         # modular unit suite
```

Library sources live under [`coop/`](./coop/). Include the umbrella header:

```c
#include "coop/__init__.h"
```

`coop_setup` / `coop_teardown` run via constructor/destructor attributes when you link the library objects.

### Inheritance taste (`examples/animals.c`)

```c
Animal = explicitgetfunc(Type, __init__)("Animal", 0l, (Object[]) {}, 0l, (Attribute[]) {});
explicitsetfunc(Animal, __init__);
explicitsetfunc(Animal, speak);
Dog = explicitgetfunc(Animal, __init__)("Dog");
explicitsetfunc(Dog, __init__);
Object *rocky = explicitgetfunc(Dog, __init__)("Rocky");
explicitgetfunc(Dog, speak)(rocky);
```

Full type/method inventory (regenerated dump): [`Documentation.md`](./Documentation.md). Architecture sketches: [`diagrams/`](./diagrams/).

## Contributing

Developer/agent workflow (layout, CMake targets, tests, PR labels): see [`AGENTS.md`](./AGENTS.md).

## License

No SPDX license file is checked into this repository yet. Do not assume a license grant until one is added.
