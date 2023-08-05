#include "Building.h"
#include <iostream>

using namespace std;

Building::Building()
:GameObject('B')
{
  student_count = 0;
  cout<<"Building default constructed"<<endl;

}

Building::Building(char in_code, int in_id, Point2D in_loc)
:GameObject(in_loc, in_id, in_code)
{
  //GameObject::id_num = in_id;
  //GameObject::location = in_loc;
  student_count = 0;
  cout<<"Building constructed"<<endl;

}

void Building::AddOneStudent()
{
  student_count = student_count+1;
  return;
}

void Building::RemoveOneStudent()
{
  student_count = student_count-1;
  return;
}

void Building::ShowStatus()
{
  GameObject::ShowStatus();
  cout<<endl;
  if (student_count == 1)
    cout<<"\t"<<student_count<<" student is in this building"<<endl;
  else if (student_count > 1)
    cout<<"\t"<<student_count<<" students are in this building"<<endl;
  else
    cout<<"\t"<<"There are no students in this building"<<endl;
  return;
}

bool Building::ShouldBeVisible()
{
  return true;
}
