#include <common.h>

Size* NewSize(float width, float height)
{
    Size* s = (Size*)calloc(1, sizeof(Size));
    s->Width = width;
    s->Height = height;
    return s;
}

Point* NewPoint(float x, float y)
{
    Point* point = (Point*)calloc(1, sizeof(Point));
    point->x = x;
    point->y = y;
    return point;
}

int GetRandomInRange(int lower, int upper)
{
    time_t seconds = time(NULL);
    return (rand() * seconds %(upper - lower + 1)) + lower;
}

Point* RandomPoint(Size* s)
{
    int posX = GetRandomInRange(0, WIDTH_WINDOW - s->Width - 1);
    int posY = -GetRandomInRange(s->Height, s->Height - 300);
    // printf("random x: %d y: %d \n", posX, posY);

    return NewPoint(posX, posY);
}

void DestroySize(Size* s){
    free(s);
}

void DestroyPoint(Point* p){
    free(p);
}