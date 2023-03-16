# Oh Hello There

I am changing the name of the engine and editor in the future.

It's designed to be lightweight. You can run games on a potato. This doesn't mean games will look awful, it just allows complete customization of the memory layout.

It has two main parts:
1. Editor
2. Engine


**Strevo Is A Testing Game. Have Fun Playing It! :)**

## Engine
A library to help in game development. It has everything already with it. Just link the library, nothing else.

Current Version: v0.5.5 (Media Update)

Current Features:
* 3D Rendering
* Game Controller/Keyboard Input
* Simple Collision
* Textures (Supports .bmp)
* Camera Management
* Actors

*Still In Development*
* 2D GUI
* Debuggin Errors
* Documentation

*Coming Soon*:
* Post Processing
* Lighting
* Audio
* Skeletal Animation

## Editor
A visual game editor that uses the Engine64 Library

Current Version: v0.0.1


## Dependent Libraries

### Qt
Just simply Qt libraries and Qt interface classes
It is part of *Edit64*

These Libraries (Called Media Backends) Are Optional Depending On CMake Configurations
Here Are Some Media Backends

### OpenGL
A part of *Engine64* that is for graphics rendering.
There will be more graphics libraries like Direct3D

### SDL2
Windowing, input, and audio for *Engine64*

### GLM
OpenGL mathematics library for 3D projection and vertex transformations.

### FreeType
TrueType font rendering
