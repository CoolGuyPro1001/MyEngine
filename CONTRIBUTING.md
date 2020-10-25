# Setup

You will need the following
* An IDE for C++
* GNU Compiler (For Windows Users Download MinGW) : https://osdn.net/projects/mingw/releases/
* Additionally you can get MSYS2 which comes with MinGW : https://www.msys2.org/
* Cmake 3.17.0 : https://cmake.org/download/
* Qt 5.15
* The GLEW library (for OpenGL) : http://glew.sourceforge.net/
* GLM : https://github.com/g-truc/glm
* SDL2 (Click on MinGW) : https://www.libsdl.org/download-2.0.php

# Coding Style

#### Variables
```cpp
int some_variable = 420;
```

#### Constants (const, constexpr, #define)
```cpp
const int CONSTANT_VARIABLE = 69;
```

#### Classes and Structs
```cpp
MyClass
```


## If Statements

Single lines should go in new line

**Yay**
```cpp
if(condition)
    code
```

**Boo**
```cpp
if(condition) code
```

The only except to to this rule is ternary operators


There must all have brackets or all have no brackets

**Yay**
```cpp
if(condition)
{
   code
}
else
{
   code
}
```

**Boo**
```cpp
if(condition)
{
   code
}
else
    code
```


## Loops

**++/-- on right**

For nested loops, follow the patern for iterator variable
* First loop: i
* 2nd: i1
* 3rd: i2

**Unless the nested loop has to do with coordinates, etc.**
**Just use the patern for nested loops where iterator has not meaning**

**Don't use goto**

For infinite loops use
```cpp
while(true)
```


## Other Styles
Identation is **four** spaces

New and delete are acceptable
Smart pointers are preferred

Brackets on new line, not on same line


Create classes **ONLY** when needed.
Use namespaces as containers for functions

