#ifndef MODEL
#define MODEL
#include <iostream>
#include <bits/stdc++.h>
#include <algorithm>

#include "Point2D.h"
#include "Vector2D.h"
#include "Building.h"
#include "GameObject.h"
#include "DoctorsOffice.h"
#include "ClassRoom.h"
#include "Student.h"
#include "Virus.h"
#include "View.h"

using namespace std;

class Model
{
private:
  int time;
  //int num_students;
  //int num_offices;
  //int num_classes;

public:
  Model();
  ~Model();
  Student* GetStudentPtr(int);
  DoctorsOffice* GetDoctorsOfficePtr(int);
  ClassRoom* GetClassRoomPtr(int);
  Virus* GetVirusPtr(int);
  bool Update();
  void Display(View*);
  void ShowStatus();
  int GetTime();
  vector <GameObject*> object_ptrs;
  vector <GameObject*> active_ptrs;
  vector <DoctorsOffice*> office_ptrs;
  vector <ClassRoom*> class_ptrs;
  vector <Student*> student_ptrs;
  vector <Virus*> virus_ptrs;
  int num_virus;


  //DoctorsOffice* office_ptrs[2];
  //ClassRoom* class_ptrs[2];
  //Student* student_ptrs[2];
  //GameObject* object_ptrs[6];

  //int GetNumObjects();
  //int GetNumClasses();
  //int GetNumOffices();
  //int GetNumStudents();
};

#endif
