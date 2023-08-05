#ifndef BUILDING
#define BUILDING
#include <iostream>
#include "Point2D.h"
#include "GameObject.h"

using namespace std;

class Building: virtual public GameObject
{
private:
  unsigned int student_count;

public:
  Building();
  Building(char, int, Point2D);
  void AddOneStudent();
  void RemoveOneStudent();
  void ShowStatus();
  bool ShouldBeVisible();

};
#endif
