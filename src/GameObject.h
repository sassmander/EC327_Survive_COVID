#ifndef GAMEOBJECT
#define GAMEOBJECT
#include <iostream>
#include "Point2D.h"

using namespace std;

class GameObject
{
 protected:
  int id_num;
  char display_code;
  unsigned int state;
  Point2D location;

 public:
  GameObject(char in_code);
  GameObject(Point2D in_loc, int in_id, char in_code);
  Point2D GetLocation() const;
  int GetId() const;
  unsigned int GetState() const;
  virtual void ShowStatus() const;
  virtual bool Update();
  virtual bool ShouldBeVisible();
  virtual ~GameObject(); //Virtual destructor
  void DrawSelf(char*);

};
#endif
