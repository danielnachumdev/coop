## How `getattr` should work
1. validate that the input is valid
2. iterate over all of the object's attributes
   1. If the type is not `Field` continue.
   2. check if the current attribute is the `__name__` field using subroutine 1, if not continue.
   3. check if the `__name__` field's data is equal to the requested key
4. return `NULL`

### Subroutine 1 - How to know if an attribute is the `__name__` field
1. iterate over the field's attributes
   1. if the type is not `Field` continue
   2. if the data is not of type `String` continue
   3. if the data's data is the string `"__name__"`return `true`
2. return `false`