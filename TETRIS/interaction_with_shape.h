#ifndef INTER_WITH_SHAPE_H
#define INTER_WITH_SHAPE_H

#include <stdlib.h>

#include "input_proc.h"

void ChangeStartPoint(Shape *shape, int dx, int dy);
Shape MakeShape(char name);
char GetNameNewShape();
bool CheckColission(Shape *shape);
void ShapeRotation(Shape *shape);
void DrawShape(Shape *shape, bool draw_mode);

#endif  // INTER_WITH_SHAPE_H
