#ifndef GFX_H
#define GFX_H

#include <vector>

#include "../headers/object.h"

void initGfx();
void draw(std::vector<Object *> *objects, int *score);
void clear();

#endif
