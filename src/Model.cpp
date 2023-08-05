#include "Model.h"
#include <iostream>

using namespace std;

Model::Model()
{
  time = 0;
  //Create pointers and new objects
  Point2D point1(5,1);
  Point2D point2(10,1);
  Point2D point3(1,20);
  Point2D point4(10,20);
  Point2D point5(0,0);
  Point2D point6(5,5);
  Point2D point7(10,12);
  Point2D point8(15,5);

  //num_objects = 6;
  //num_students = 2;
  //num_offices = 2;
  //num_classes = 2;

  //Student (name, id_num, speed, location)
  Student* S1 = new Student("Homer", 1, 2, point1);
  Student* S2 = new Student("Marge", 2, 1, point2);
  //object_ptrs[0] = S1;
  //object_ptrs[1] = S2;
  //student_ptrs[0]= S1;
  //student_ptrs[1]= S2;
  object_ptrs.push_back(S1);
  active_ptrs.push_back(S1);
  student_ptrs.push_back(S1);
  object_ptrs.push_back(S2);
  active_ptrs.push_back(S2);
  student_ptrs.push_back(S2);


  //DoctorsOffice (id_num, vaccine_cost, vaccine_capacity, location)
  DoctorsOffice* D1 = new DoctorsOffice(1, 1, 100, point3);
  DoctorsOffice* D2 = new DoctorsOffice(2, 2, 200, point4);
  //object_ptrs[2] = D1;
  //object_ptrs[3] = D2;
  //office_ptrs[0] = D1;
  //office_ptrs[1] = D2;
  object_ptrs.push_back(D1);
  active_ptrs.push_back(D1);
  office_ptrs.push_back(D1);
  object_ptrs.push_back(D2);
  active_ptrs.push_back(D2);
  office_ptrs.push_back(D2);

  //ClassRoom (id_num, antibody_cost, dollar_cost, credit_per, max_assign, location)
  ClassRoom* C1 = new ClassRoom(1, 1, 2, 3, 10, point5);
  ClassRoom* C2 = new ClassRoom(2, 5, 7.5, 4, 20, point6);
  //object_ptrs[4] = C1;
  //object_ptrs[5] = C2;
  //class_ptrs[0] = C1;
  //class_ptrs[1] = C2;
  object_ptrs.push_back(C1);
  active_ptrs.push_back(C1);
  class_ptrs.push_back(C1);
  object_ptrs.push_back(C2);
  active_ptrs.push_back(C2);
  class_ptrs.push_back(C2);

  //Virus::Virus(int id, double virulence, double resistance, double energy, char variant, Point2D in_loc)
  Virus* V1 = new Virus(1, 10, 4, 40, 'd', point7);
  Virus* V2 = new Virus(2, 5, 2, 30, 'a', point8);
  //Virus* V3 = new Virus(3, 5, 2, 10, 'w', point9);

  object_ptrs.push_back(V1);
  active_ptrs.push_back(V1);
  virus_ptrs.push_back(V1);
  object_ptrs.push_back(V2);
  active_ptrs.push_back(V2);
  virus_ptrs.push_back(V2);
  num_virus = 2;
  //object_ptrs.push_back(V3);
  //active_ptrs.push_back(V3);
  //virus_ptrs.push_back(V3);

  cout<<"Model default constructed"<<endl;
}

Model::~Model()
{
  //for (unsigned int i = 0; i < object_ptrs.size(); i++)
  for(vector <GameObject*>::iterator pObj = object_ptrs.begin(); pObj != object_ptrs.end(); ++pObj)
  {
    delete *pObj;
  }
  object_ptrs.clear();

  cout<<"Model destructed"<<endl;
}

Student* Model::GetStudentPtr(int id)
{
  Student* return_ptr = NULL;
  for(vector <Student*>::iterator fObj = student_ptrs.begin(); fObj != student_ptrs.end(); ++fObj)
  {
    if ((*fObj)->GetId() == id)
    {
      return_ptr = *fObj;
      return return_ptr;
    }
  }

  if (return_ptr == NULL)
    {
      cout<<"Unable to find Student Pointer"<<endl;
    }
  return return_ptr;
}

DoctorsOffice* Model::GetDoctorsOfficePtr(int id)
{
  DoctorsOffice* return_ptr = NULL;
  for(vector <DoctorsOffice*>::iterator pObj = office_ptrs.begin(); pObj != office_ptrs.end(); ++pObj)
  {
    if ((*pObj)->GetId() == id)
    {
      return_ptr = *pObj;
      return return_ptr;
    }
  }

  if (return_ptr == NULL)
    {
      cout<<"Unable to find Office Pointer"<<endl;
    }
  return return_ptr;
}

ClassRoom* Model::GetClassRoomPtr(int id)
{
  ClassRoom* return_ptr = NULL;
  for(vector <ClassRoom*>::iterator cObj = class_ptrs.begin(); cObj != class_ptrs.end(); ++cObj)
  {
    if ((*cObj)->GetId() == id)
    {
      return_ptr = *cObj;
      return return_ptr;
    }
  }

  if (return_ptr == NULL)
    {
      cout<<"Unable to find Class Pointer"<<endl;
    }
  return return_ptr;
}

Virus* Model::GetVirusPtr(int id)
{
  Virus* return_ptr = NULL;
  for(vector <Virus*>::iterator pObj = virus_ptrs.begin(); pObj != virus_ptrs.end(); ++pObj)
  {
    if ((*pObj)->GetId() == id)
    {
      return_ptr = *pObj;
      return return_ptr;
    }
  }

  if (return_ptr == NULL)
    {
      cout<<"Unable to find Virus Pointer"<<endl;
    }
  return return_ptr;
}

bool Model::Update()
{
  //Individually updates for different objects and increases a count for any status updates

  //Final flag var is returns as true if any of the update functions return true (aka there is a status change)
  bool final_flag = false;
  cout<<endl<<"Current time: "<<GetTime()<<endl;
  time = time+1;
  int count = 0;
  for (unsigned int i = 0; i < active_ptrs.size(); i++)
  {
    unsigned int tempstate = active_ptrs[i]->GetState();
    if ((tempstate == INFECTED)||(tempstate == DEAD))
    {
      active_ptrs.erase(active_ptrs.begin()+i);
      cout<<"1 Dead or Infected removed"<<endl;
    }

  }
  for(vector <GameObject*>::iterator aObj = active_ptrs.begin(); aObj != active_ptrs.end(); ++aObj)
  {
    bool flag = (*aObj)->Update();
    if (flag == 1)
    {
      count++;
    }
  }
  for(vector <Virus*>::iterator eObj = virus_ptrs.begin(); eObj != virus_ptrs.end(); ++eObj)
  {
    for(vector <Student*>::iterator sObj = student_ptrs.begin(); sObj != student_ptrs.end(); ++sObj)
    {
      (*eObj)->Infect((*sObj));
    }
  }

  //Sets final flag if any counts are bigger than 0
  if (count>0)
  {
    final_flag = true;
  }

  //Get total count of assignments remaining
  unsigned int TotalAssignments = 0;
  unsigned int VirusDead = 0;
  for(vector <ClassRoom*>::iterator pObj = class_ptrs.begin(); pObj != class_ptrs.end(); ++pObj)
  {
    TotalAssignments = TotalAssignments + (*pObj)->GetNumAssignmentsRemaining();
  }
  for(vector <Virus*>::iterator vObj = virus_ptrs.begin(); vObj != virus_ptrs.end(); ++vObj)
  {
    if ((*vObj)->GetState() == DEAD)
    {
      VirusDead = VirusDead + 1;
    }
  }
  if (TotalAssignments == 0)
  {
    cout<<"GAME OVER: You win! All assignments done!"<<endl;
    //~Model
    for(vector <GameObject*>::iterator wObj = object_ptrs.begin(); wObj != object_ptrs.end(); ++wObj)
    {
      delete *wObj;
    }
    object_ptrs.clear();

    cout<<"Model destructed"<<endl;
    exit(0);
  }
  else if ((TotalAssignments == 0)&&(VirusDead == num_virus))
  {
    cout<<"TRUE ENDING: The Pandemic is over!!"<<endl;
    for(vector <GameObject*>::iterator bObj = object_ptrs.begin(); bObj != object_ptrs.end(); ++bObj)
    {
      delete *bObj;
    }
    object_ptrs.clear();

    cout<<"Model destructed"<<endl;
    exit(0);
  }
  //If all students are infected
  unsigned int InfectedStudents = 0;
  for(vector <Student*>::iterator qObj = student_ptrs.begin(); qObj != student_ptrs.end(); ++qObj)
  {
    if ((*qObj)->IsInfected() == 1)
    {
      InfectedStudents++;
    }
  }
  if (InfectedStudents == student_ptrs.size())
  {
    cout<<"GAME OVER: You lose! All of your students are infected!"<<endl;
    //~Model
    for(vector <GameObject*>::iterator rObj = object_ptrs.begin(); rObj != object_ptrs.end(); ++rObj)
    {
      delete *rObj;
    }
    object_ptrs.clear();

    cout<<"Model destructed"<<endl;
    exit(0);
  }
  return final_flag;
}

void Model::Display(View* view)
{
  //To clear and replot objects after a command
  (*view).Clear();
  for(vector <GameObject*>::iterator pObj = active_ptrs.begin(); pObj != active_ptrs.end(); ++pObj)
  {
    (*view).Plot(*pObj);
  }

  //Redraw objects
  (*view).Draw();

  //Model::ShowStatus();
  return;
}

void Model::ShowStatus()
{
  /*for (int i = 0; i < num_objects; i++) {
    object_ptrs[i]->GameObject::ShowStatus();
  }*/
  for(vector <Student*>::iterator pObj = student_ptrs.begin(); pObj != student_ptrs.end(); ++pObj)
  {
    (*pObj)->Student::ShowStatus();
  }
  for(vector <ClassRoom*>::iterator pObj = class_ptrs.begin(); pObj != class_ptrs.end(); ++pObj)
  {
    (*pObj)->ClassRoom::ShowStatus();
  }
  for(vector <DoctorsOffice*>::iterator pObj = office_ptrs.begin(); pObj != office_ptrs.end(); ++pObj)
  {
    (*pObj)->DoctorsOffice::ShowStatus();
  }
  for(vector <Virus*>::iterator pObj = virus_ptrs.begin(); pObj != virus_ptrs.end(); ++pObj)
  {
    (*pObj)->Virus::ShowStatus();
  }
  return;
}

int Model::GetTime()
{
  return time;
}
