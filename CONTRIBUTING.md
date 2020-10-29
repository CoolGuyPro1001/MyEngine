# Setup

You Will Need The Following
* An IDE for C++
* GNU Compiler (For Windows Users Download MSYS2) : https://www.msys2.org/
* Cmake 3.17.0 : https://cmake.org/download/
* Qt 5.15
* GLM : https://github.com/g-truc/glm
* SDL2 (Click on MinGW) : https://www.libsdl.org/download-2.0.php

CMake Setup Generator
* open cmakegui.exe
* For the source code path navigate to wherever your Edit64 folder is
* For the build path do the same thing and add "/build"
* Click on Configure
* Select MinGW as Generator
* Select Specify Native Compilers
* For C Compiler use gcc.exe and for C++ Compiler use g++.exe
* They should be in msys64/mingw64/bin

CMake Add Library Paths
* Click on GLM path
* Navigate to (your GLM folder)/cmake/glm
* Click on Select Folder
* For SDL2 go to (your msys64 folder)/mingw64/lib/cmake/SDL2
* For QT go to (your QT folder)/(version number)/mingw64-1229/lib/cmake/QT
* Click on Configure to save changes

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

