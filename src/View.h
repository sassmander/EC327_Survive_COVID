#ifndef VIEW
#define VIEW
#include <iostream>
#include "Point2D.h"
#include "GameObject.h"
#include <string>

using namespace std;

const int view_maxsize = 20;

class View
{
public:
  View();
  void Clear();
  void Plot(GameObject*);
  void Draw();

private:
  int size;
  double scale;
  Point2D origin;
  char grid[view_maxsize][view_maxsize][2];
  bool GetSubscripts(int*, int*, Point2D);

};
#endif

//Questions on:
//Issues with model not building arrays correctly - check!
//Seg fault with Run/Go functions - issues with function

//DrawSelf in GameObject!! and Display issues on console
//Also how to know there's multiple objects in 1 location

//Destructor in Model
