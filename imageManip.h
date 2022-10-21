#ifndef IMAGEMANIP_H
#define IMAGEMANIP_H

#include "ppmIO.h"
#include <stdlib.h>

void swap(Image* image);

void grayscale(Image* image);

void contrast(Image* image, double amt);

void blackout(Image* image);

Image* crop(Image* image, int x1, int y1, int x2, int y2);
#endif
