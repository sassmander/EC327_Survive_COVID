#include <iostream>
#include <cmath>
#include "Point2D.h"
#include "Vector2D.h"

using namespace std;

Point2D::Point2D()
{
  x = 0.0;
  y = 0.0;
}

Point2D::Point2D(double inputx, double inputy)
{
  x = inputx;
  y = inputy;
}

double GetDistanceBetween(Point2D p1, Point2D p2)
{
  double root;
  root = sqrt(pow(p1.x-p2.x, 2.0)+pow(p1.y-p2.y, 2.0));
  return root;
}

bool operator == (Point2D p1, Point2D p2)
{
  if (p1.x == p2.x && p1.y == p2.y)
    return true;
  else
    return false;
}

bool operator != (Point2D p1, Point2D p2)
{
  if ((p1.x != p2.x)|(p1.y != p2.y))
    return true;
  else
    return false;
}

Vector2D operator - (Point2D p1, Point2D p2)
{
  Vector2D v1;
  v1.x = p1.x-p2.x;
  v1.y = p1.y - p2.y;

  return Vector2D(v1);
}

Point2D operator + (Point2D p1, Vector2D v1)
{
  Point2D p2;
  p2.x = p1.x + v1.x;
  p2.y = p1.y + v1.y;

  return Point2D(p2);
}

ostream& operator << (ostream& out, Point2D p1)
{
  //double a = 0;
  out<<"("<<p1.x<<", "<<p1.y<<")";

  return out;
}
