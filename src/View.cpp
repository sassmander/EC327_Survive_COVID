#include "View.h"
#include <iostream>

using namespace std;

View::View()
{
  size = 11;
  scale = 2;
  Point2D point1(0,0);
  origin = point1;
}

void View::Clear()
{
  for (int i = 0; i < view_maxsize; i++) {
    for (int j = 0; j < view_maxsize; j++) {
      grid[i][j][0] = ' ';
    }
  }
  for (int i = 0; i < view_maxsize; i++) {
    for (int j = 0; j < view_maxsize; j++) {
      grid[i][j][1] = '.';
    }
  }
}

void View::Plot(GameObject* ptr) //2 issues
{
  int output_x, output_y;
  char* charptr = new char[2];
  bool flag = GetSubscripts(&output_x, &output_y, ptr->GetLocation());
  if ((flag == 1)&&(ptr->ShouldBeVisible()==1))
  {
    ptr->DrawSelf(charptr);
    grid[output_x][output_y][0] = *charptr;
    grid[output_x][output_y][1] = *(charptr+1);
  }
  //??? Need to indicate multiple objects!
} //Use for loop to pass through all object ptrs

bool View::GetSubscripts(int *out_x, int *out_y, Point2D loc)
{
  *out_x = (loc.x-origin.x)/scale;
  *out_y = (loc.y-origin.y)/scale;
  if ((*out_x <= view_maxsize)&&(*out_y <= view_maxsize)) {
    return true;
  }
  else {
    cout<<"An object is outside the display"<<endl;
    return false;
  }
}

//Taken from professor
void View::Draw()
{
  for (int j = size-1; j >= -1; j--) {
    for (int i = -1; i <= size-1; i++) {
      //grid axis
      if (i == -1 && j%2 == 0) {
        cout<<j*2;
        if (j/5 == 0) {
          cout<<" ";
        }
      }
      else if (i == -1 && j%2 != 0) {
        cout<<"  ";
      }
      else if (j == -1 && i%2 == 0) {
        cout<<i*2;
        if (i/5 == 0) {
          cout<<" ";
        }
        cout<<"  ";
      }
      //draw objects
      if (i >= 0 && j >= 0) {
        cout<<grid[i][j][0]<<grid[i][j][1];
      }
    }
    cout<<endl;
  }
}
