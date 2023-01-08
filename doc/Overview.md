# Overview
This Engine has three main parts to it, Non-Media and Media, and Common

## Non-Media
Non-Media refers to any classes, functions, and data structures used inside the game itself.

Actors, Components, Levels, Events, and GUI fall into this category.

## Media
Media refers to any classes, functions, and data structures that Non-Media uses to run the game. Each Media class can be enabled or disabled from the project by the CMake Cache.

Media classes have an M prefix.

Media classes have their implementation provided by groups of classes from MediaBackends (OpenGL, DirectX, SDL, etc.). Different MediaBackend classes can be enabled or disabled based on the platform the game is built for.

For example, let's say you want to your game to have rendering. If you are developing on Windows, DirectX classes will be enabled. If you are developing for MacOS or Linux, OpenGL classes will be enabled.

Some Media classes are dependent on each other.
Example: MRenderer and MWindow

## Common
All classes and structures in the Common folder are used anywhere. Simple data structures like Vector3, Color, and Matrix can be found here.

Additionally, logging and error output functions are also found here.

## Media Devices
Classes here represent, well, devices. They each have their own state and will Announce() any events. Their state and list of events are changed every frame by a Media class.

## Miscellanious Headers

### Systems.h
Systems are functions that take in Media Classes, Components, and other data to execute a part of the Engine. They are based on the ECS design.

### Entry.h
Provides the Start() and LoadLevel() functions, and keeps track of the current level

### Time.h
Calculates game delay and FPS. Has functions for timing.

To measure the time between a section of code, use StartImer() and StopTimer(). StopTimer() will log the resulting time in nano seconds.

