#ifndef ENTRY_H
#define ENTRY_H

#include "Core/Media/WindowMedia.h"
#include "Core/Media/GraphicsMedia.h"
#include "Core/Media/InputMedia.h"

struct Level;

static Level& CurrentLevel();

void Start(Level& lvl, Unique<MWindow> window, Unique<MRenderer> renderer, Unique<MInput> input);
void LoadLevel(Level& lvl, MRenderer* renderer);
void Close(MWindow& window);
void Test();

#endif
