# Setup

Note that I am still learning CMake CLI

You Will Need The Following
* An IDE for C++ (Or Not If Like Using Terminal)
* GNU Compiler (For Windows Users Download MSYS2) : https://www.msys2.org/
* Cmake 3.17.0 : https://cmake.org/download/
* Qt 5.15
* GLM : https://github.com/g-truc/glm
* SDL2 (Click on MinGW) : https://www.libsdl.org/download-2.0.php
* FreeType : https://www.freetype.org/download.html

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

Single lines should go in new line, unless you stack together one lined if statements;

**Yay**
```cpp
if(condition)
    code
```

**Optional**
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

Variable names like i, j, x are ok

For nested loops, try to use naming.
If you need placeholder variable names use:
* First loop: i
* 2nd: i1
* 3rd: i2

**For nested loops that handle coordinates, colors, etc. use the approriate names (xyz, rgba)**

**Just use the pattern for nested loops where iterator has not meaning**

**Prefer foreach over for**

**Don't use goto**

For infinite loops use
```cpp
while(true)
```

## Functions
Don't use * for referencing, use &.
Only use * if you actually want a pointer.


## Other Styles
Identation is **four** spaces

New and delete are acceptable
Smart pointers are preferred

Brackets on new line, not on same line

Create classes **ONLY** when needed.

Use namespaces as containers for functions that are similar.
But tone down the namespacing.

The line width is 120. Any variables, conditions, or cout strings surpassing the width must be put on a new line and then indented one more.
```cpp
void SomeFunctionWitLotsOfParameters(bool b, char c, double d, float f, int i, long l, short s, uchar uc, uint ui, 
    ulong ul, ushort us);
```


## Including
Lower amount of #includes in header files.

External Libraries (STD, STL, etc.) are preferred inside pch.h

### Include Structure

[Direct Header File By Name]

[System Specific Libraries (WIN32, OSX, etc.)]

[Engine Header Files (Path Starts From Top)]

[Any External Libraries That Couldn't Be In Precompiled Header]


## CMake
Don't use add_library() for adding sources, use target_sources()

When adding sources, don't do GLOB, just list them explicitly
