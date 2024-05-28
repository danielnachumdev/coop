# COOP (C with OOP)

## What is this?

This is a challenge that I posed to myself.

## Whats the goal?

The goal is to implement in C behaviour that is similar to the OOP structure that is implemented in python.

## How?

**Some preliminaries**

* As this is C, there is no such thing as an 'instance' because there are no classes. When I'm saying instance I mean
  specific initialization of some struct.

All of my implementation boils down to clever use of one struct:

```C
typedef struct Object {
    const struct Object *type;
    unsigned long num_attributes;
    struct Object **attributes;
    void *data;
} Object;
```

I create an instance that is the most basic type: `Type`.
Also some additional types are `String`,`Integer`,`Field`,`Function`
I also have some builtin functions such as `getattr`,`setattr`, `hasattr`

Also, because we are talking about classes it is expected that they will be garbage collected, for this reason I have
implemented som form of garbage collection which all of the allocations are being executed using it
with `acquire`, `release`, `clear`

Note that because of all of the required initialization, In addition to the real entry point which is `main`, from there I'm calling the "real" entry point `_main`.