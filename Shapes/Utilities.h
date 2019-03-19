#pragma once
#include "Vertex.h"
#include "macros.h"

bool doubleEqual(double a, double b);

double distance(const Vertex& v1, const Vertex& v2);
bool sameX(const Vertex& v1, const Vertex& v2);
bool sameY(const Vertex& v1, const Vertex& v2);
bool operator<(const Vertex& lhs, const Vertex& rhs);

/*
This function will create a point based on x and y
Arguments: x, y
*/
Vertex setPoint(double x, double y);
