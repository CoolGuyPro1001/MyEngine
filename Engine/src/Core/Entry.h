#ifndef ENTRY_H
#define ENTRY_H

struct Level;
void Start(int window_width, int window_height, const char* window_name);
void Run(Level& lvl);
void Close();
void Test();

#endif
