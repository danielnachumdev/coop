# COOP (C with OOP)

> **Object-Oriented Programming in C, inspired by Python**

---

## Introduction
COOP is an ambitious project that brings Python-like object-oriented programming (OOP) features to the C language. It provides a flexible, extensible, and dynamic object system, enabling you to write C code with classes, inheritance, attributes, and even some built-in functions reminiscent of Python.

## Key Features
- **Dynamic Object System:** Central `Object` struct with runtime type information and dynamic attributes.
- **Pythonic Built-ins:** Functions like `getattr`, `setattr`, `hasattr`, `isinstance`, `len`, `print`, and more.
- **Rich Type System:** Built-in types such as `Type`, `String`, `Integer`, `Boolean`, `List`, `Array`, `Set`, `Union`, `Function`, and more.
- **Attribute & Method Support:** Add, get, and check attributes and methods at runtime.
- **Inheritance & Super:** Simulate inheritance and call parent methods with `super`.
- **Garbage Collection:** Custom memory allocator with `acquire`, `release`, and `clear` for safe memory management.
- **Logging & Debugging:** Integrated logger with multiple severity levels for easier debugging.
- **Extensive Macros:** Macros to simplify OOP patterns and function definitions in C.
- **Type-Safe Function Calls:** All functions are implemented with specially designed macros that help the IDE maintain the type information of arguments when calling functions—this is a core part of the project's magic, enabling type safety and better developer experience in C.
- **Comprehensive Testing:** Modular test suite for all major components.

## How It Works
COOP revolves around a single, powerful struct:

```c
typedef struct Object {
    const struct Object *type;
    unsigned long num_attributes;
    struct Attribute **attributes;
    void *data;
} Object;

typedef struct Attribute {
    const char *key;
    Object *value;
} Attribute;
```

Every value is an `Object`, including types themselves. Attributes and methods are stored in a dynamic array, and types are themselves objects, enabling metaprogramming and dynamic behavior.

### Example: Attribute Access
- `getattr(obj, "attr")` — Get an attribute (with inheritance lookup)
- `setattr(obj, "attr", value)` — Set or add an attribute
- `hasattr(obj, "attr")` — Check if an attribute exists

## Implemented Types & Functions
- **Types:** Array, Boolean, Function, Integer, List, Node, Number, Set, String, Type, Union
- **Functions:** `getattr`, `setattr`, `hasattr`, `isinstance`, `len`, `print`, `super`, `input`, `dir`, `hash`, `contains`, `callable`, and more
- **Macros:** For defining methods, global functions, and type-safe casting

See [Documentation.md](./Documentation.md) for a full list of types and their methods.

## Memory Management & Logging
- **Custom Allocator:** All allocations use a custom allocator supporting both linked list and hash set strategies. Track memory usage and prevent leaks with `acquire`, `release`, and `clear`.
- **Logger:** Built-in logger with severity levels (DEBUG, INFO, WARN, ERROR) for structured logging and debugging.

## Usage Example
Here's a taste of OOP in C with COOP (from `examples/animals.c`):

```c
Object *Animal = explicitgetfunc(Type, __init__)("Animal", ...);
explicitsetfunc(Animal, __init__);
explicitsetfunc(Animal, speak);
Object *Dog = explicitgetfunc(Animal, __init__)("Dog");
explicitsetfunc(Dog, __init__);
Object *rocky = explicitgetfunc(Dog, __init__)("Rocky");
explicitgetfunc(Dog, speak)(rocky);
```

You can define types, methods, and even simulate inheritance and method overriding!

## Building & Running
### With CMake (Recommended)
```sh
cmake -B build
cmake --build build
./build/coop
```

### With Python Helper (WSL required)
```sh
python main.py           # Build and run
python main.py valgrind  # Run with Valgrind for memory checks
```

## Testing
All major components are covered by modular tests:
- Backend data structures (linked list, stack, hashset, node)
- Built-in types and functions (attributes, globals, types)

To build and run tests:
```sh
cmake --build build --target tests
./build/tests
```

## Documentation
- [Documentation.md](./Documentation.md): Full list of types, methods, and built-in functions
- [diagrams/](./diagrams/): Visual diagrams of the architecture and flow

## Contributing & License
Contributions are welcome! Please open issues or pull requests for suggestions, bug reports, or new features.

---

COOP is released under the MIT License.