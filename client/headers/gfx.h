#ifndef GFX_H
#define GFX_H

#include <vector>

#include "../headers/object.h"

void initGfx();
void draw(std::vector<Object *> *objects, int *score);
char *enterMsg(int id);
void enterMsg(char *msg);
void clear();

#endif
