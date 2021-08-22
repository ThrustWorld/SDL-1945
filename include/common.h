#ifndef COMMON_H
#define COMMON_H

#define WIDTH_WINDOW 640
#define HEIGHT_WINDOW 480
#define POINT_ZERO NewPoint(0,0)
#define SIZE_ZERO NewSize(0,0)
#define RECT_ZERO NewRect(POINT_ZERO, SIZE_ZERO)

#include "SDL.h"
#include <SDL_mixer.h>
#include <SDL_ttf.h>
#include <SDL_image.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include "list.h"

enum boolean_enum { false, true };
typedef unsigned char boolean;

typedef unsigned int uint;

typedef struct {
    float Width;
    float Height;
} Size;

typedef struct {
    float x;
    float y;
} Point;


Size* NewSize(float width, float height);
Point* NewPoint(float x, float y);

int GetRandomInRange(int lower, int upper);
Point* RandomPoint(Size* s);

void DestroySize(Size* s);
void DestroyPoint(Point* p);


#endif // COMMON_H