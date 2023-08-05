#include "GameObject.h"
#include "Point2D.h"
#include <iostream>

using namespace std;

GameObject::GameObject(char in_code)
{
  display_code = in_code;
  id_num = 1;
  state = 0;
  Point2D x(0,0);
  location = x;
  cout<<"GameObject constructed"<<endl;
}

GameObject::GameObject(Point2D in_loc, int in_id, char in_code)
{
  display_code = in_code;
  id_num = in_id;
  state = 0;
  location = in_loc;
}

Point2D GameObject::GetLocation() const
{
  return location;
}

int GameObject::GetId() const
{
  return id_num;
}

unsigned int GameObject::GetState() const
{
  return state;
}

//Four virtual functions
void GameObject::ShowStatus() const
{
  cout<<display_code<< id_num;
  cout << " at "<<GetLocation();

  return;
}

bool GameObject::Update()
{
}

bool GameObject::ShouldBeVisible()
{
}

GameObject::~GameObject()
{
  cout<<"GameObject destructed"<<endl;
}

void GameObject::DrawSelf(char* charptr) //issues?
{
  *(charptr) = display_code;
  if (GetId() <= 9) {
    *(charptr+1) = '0'+id_num;
  }
  else if (GetId() > 9) {
    *(charptr+1) = 'V'+id_num;
  }
}
