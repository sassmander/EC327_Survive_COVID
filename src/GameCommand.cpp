#include "GameCommand.h"
#include <iostream>

using namespace std;

void DoMoveCommand(Model* model, int student_id, Point2D p1) //Should check if the inputs are within grid
{
  Student* s_ptr = NULL;
  for (int i=0; i < 2; i++)
  {
    s_ptr = model->Model::GetStudentPtr(student_id);
  }
  if (s_ptr == NULL)
  {
    cout<<"Error: Please enter a valid command!"<<endl;
  }
  else
  {
    cout<<"Moving "<<s_ptr->Student::GetName()<<" to "<<p1<<endl;
    s_ptr->Student::StartMoving(p1);
  }
  return;
}

void DoMoveToDoctorCommand(Model* model, int student_id, int office_id)
{
  Student* s_ptr = NULL;
  DoctorsOffice* o_ptr = NULL;
  for (int i=0; i < 2; i++)
  {
    s_ptr = model->Model::GetStudentPtr(student_id);
    o_ptr = model->Model::GetDoctorsOfficePtr(office_id);
  }
  if ((s_ptr == NULL)||(o_ptr == NULL))
  {
    cout<<"Error: Please enter a valid command!"<<endl;
  }
  else
  {
    cout<<"Moving "<<s_ptr->Student::GetName()<<" to doctor's office "<<o_ptr->GameObject::GetId()<<endl;
    s_ptr->Student::StartMovingToDoctor(o_ptr);
  }
  return;
}

void DoMoveToClassCommand(Model* model, int student_id, int class_id)
{
  Student* s_ptr = NULL;
  ClassRoom* c_ptr = NULL;
  for (int i=0; i < 2; i++)
  {
    s_ptr = model->Model::GetStudentPtr(student_id);
    c_ptr = model->Model::GetClassRoomPtr(class_id);
  }
  if ((s_ptr == NULL)||(c_ptr == NULL))
  {
    cout<<"Error: Please enter a valid command!"<<endl;
  }
  else
  {
    cout<<"Moving "<<s_ptr->Student::GetName()<<" to class "<<c_ptr->GameObject::GetId()<<endl;
    s_ptr->Student::StartMovingToClass(c_ptr);

  }
  return;
}

void DoStopCommand(Model* model, int student_id)
{
  Student* s_ptr = NULL;
  for (int i=0; i < 2; i++)
  {
    s_ptr = model->Model::GetStudentPtr(student_id);
  }
  if (s_ptr == NULL)
  {
    cout<<"Error: Please enter a valid command!"<<endl;
  }
  else
  {
    cout<<"Stopping "<<s_ptr->Student::GetName()<<endl;
    s_ptr->Student::Stop();
  }
  return;
}

void DoLearningCommand(Model* model, int student_id, unsigned int assignments)
{
  Student* s_ptr = NULL;
  for (int i=0; i < 2; i++)
  {
    s_ptr = model->Model::GetStudentPtr(student_id);
  }
  if ((s_ptr == NULL) || (assignments < 0))
  {
    cout<<"Error: Please enter a valid command!"<<endl;
  }
  else
  {
    cout<<"Teaching "<<s_ptr->Student::GetName()<<endl;
    s_ptr->Student::StartLearning(assignments);

  }
  return;
}

void DoRecoverInOfficeCommand(Model* model, int student_id, unsigned int vaccine_needs)
{
  Student* s_ptr = NULL;
  for (int i=0; i < 2; i++)
  {
    s_ptr = model->Model::GetStudentPtr(student_id);
  }
  if ((s_ptr == NULL) || (vaccine_needs < 0))
  {
    cout<<"Error: Please enter a valid command!"<<endl;
  }
  else
  {
    cout<<"Recovering "<<s_ptr->Student::GetName()<<"'s antibodies"<<endl;
    s_ptr->Student::StartRecoveringAntibodies(vaccine_needs);
  }
  return;
}

void DoGoCommand(Model* model, View* view) //issues use View
{
  cout<<"Advancing one tick"<<endl;
  model->Model::Update();

  return;
}

void DoRunCommand(Model* model, View* view) //issues use View
{
  cout<<"Advancing to next event!"<<endl;
  bool flag = false;
  int count = 0;
  while ((flag == false)&&(count<5)) {
  flag = model->Model::Update();
  count++;
  }
  return;
}

void NewCommand(Model* model, View* view, char type, int id, Point2D in_loc)
{
  if ((type == 'd')&&(id > 2)) {
    DoctorsOffice* D3 = new DoctorsOffice(id, 1, 10, in_loc);
    model->object_ptrs.push_back(D3);
    model->active_ptrs.push_back(D3);
    model->office_ptrs.push_back(D3);
    cout<<"New DoctorsOffice with ID "<<id<<" created at "<<in_loc<<endl;
  }  //ClassRoom (id_num, antibody_cost, dollar_cost, credit_per, max_assign, location)
  else if ((type == 'c')&&(id > 2)) {
    ClassRoom* C3 = new ClassRoom(id, 1, 1, 10, 5, in_loc);
    model->object_ptrs.push_back(C3);
    model->active_ptrs.push_back(C3);
    model->class_ptrs.push_back(C3);
    cout<<"New ClassRoom with ID "<<id<<" created at "<<in_loc<<endl;
  }   //Student (name, id_num, speed, location)
  else if ((type == 's')&&(id > 2)) {
    Student* S3 = new Student("Hero", id, 5, in_loc);
    model->object_ptrs.push_back(S3);
    model->active_ptrs.push_back(S3);
    model->student_ptrs.push_back(S3);
    cout<<"New Student "<<S3->GetName()<<" with ID "<<id<<" created at "<<in_loc<<endl;
  }   //Virus::Virus(int id, double virulence, double resistance, double energy, char variant, Point2D in_loc)
  else if ((type == 'v')&&(id > 2)) {
    Virus* V3 = new Virus(id, 5, 2, 10, 'w', in_loc);
    model->object_ptrs.push_back(V3);
    model->active_ptrs.push_back(V3);
    model->virus_ptrs.push_back(V3);
    model->num_virus = model->num_virus + 1;
    cout<<"New wild-type Virus with ID "<<id<<" created"<<endl;
  }
  else {
    cout<<"Please enter a valid command! New type not created."<<endl;
  }

  return;
}
