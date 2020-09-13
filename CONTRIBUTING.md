# Dolphin Coding Style & Licensing

blah blah blahdsafdasfasfasdfdasfasfasdfffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffff

Variables
``int some_variable = 420;``

Constants (const, constexpr, #define)
``const int CONSTANT_VARIABLE = 69;``

Classes and Structs
``MyClass``


If Statements

Single lines should go in new line

Good
```
if(condition)
    code
```

Bad
```
if(condition) code
```§

The only except to to this rule is ternary operators


There must all have brackets or all have no brackets

Good
```
if(condition)
{
   code
}
else
{
   cod
}
```

Bad
```
if(condition)
{
   code
}
else
    code
```


Loops

++/-- on right

For nested loops, follow the patern for iterator variable
First loop: i
2nd: i1
3rd: i2
...

Don't use goto



Identation is four spaces

New and delete are acceptable
Smart pointers are preferred

Brackets on new line, not on same line


Create classes ONLY when needed.
Use namespaces as containers for functions

