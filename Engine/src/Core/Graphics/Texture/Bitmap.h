#ifndef BITMAP_H
#define BITMAP_H

struct Color;

bool ReadBitmapFile(std::string image_path, std::vector<Color>& colors, uint& width, uint& height);
static bool BMPToTexture(std::string bmp_path, std::vector<Color>& colors, uint& width                                                        , uint& height);

#endif
