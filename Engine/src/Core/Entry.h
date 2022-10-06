#ifndef ENTRY_H
#define ENTRY_H

#include "Core/Media/WindowMedia.h"
#include "Core/Media/GraphicsMedia.h"
#include "Core/Media/InputMedia.h"

struct Level;

static Level& CurrentLevel();

void Start(Unique<MWindow> window, Unique<MRenderer> renderer, Unique<MInput> input, Level& lvl);
void LoadLevel(MRenderer& renderer, Level& lvl);
void Close(MWindow& window);
void Test();

#endif
