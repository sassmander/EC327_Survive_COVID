#include "Student.h"
#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>
#include <cmath>
#include <iomanip>

using namespace std;

Student::Student() //default constructor
:GameObject('S')
{
  speed = 5;
  is_at_doctor = false;
  is_in_class = false;
  is_ill = false;
  antibodies = 20;
  credits = 0;
  dollars = 0;
  assignments_to_buy = 0;
  vaccines_to_buy = 0;
  name = "Default";
  current_office = NULL;
  current_class = NULL;
  cout<<"Student default constructed"<<endl;
  state = STOPPED;
}

Student::Student(char in_code)
:GameObject(in_code)
{
  speed = 5;
  is_at_doctor = false;
  is_in_class = false;
  is_ill = false;
  antibodies = 20;
  credits = 0;
  dollars = 0;
  assignments_to_buy = 0;
  vaccines_to_buy = 0;
  name = "Default";
  current_office = NULL;
  current_class = NULL;
  cout<<"Student constructed"<<endl;
  state = STOPPED;
}

Student::Student(string in_name, int in_id, unsigned int in_speed, Point2D in_loc)
:GameObject(in_loc, in_id, 'S')
{
  speed = in_speed;
  name = in_name;

  //part of default states
  is_at_doctor = false;
  is_in_class = false;
  is_ill = false;
  antibodies = 20;
  credits = 0;
  dollars = 0;
  assignments_to_buy = 0;
  vaccines_to_buy = 0;
  current_office = NULL;
  current_class = NULL;
  state = STOPPED;
  cout<<"Student " <<name<<" constructed"<<endl;
}

void Student::StartMoving(Point2D dest)
{
  this->destination = dest;
  SetupDestination(dest); //add more to this
  if (this->GetLocation() == dest)
    {
      cout<<GameObject::display_code<<GameObject::id_num<<": I'm already there. See?"<<endl;
    }
  else if (state == INFECTED)
    {
      cout<<GameObject::display_code<<GameObject::id_num<<": I am infected. I may move but you cannot see me."<<endl;
    }
  else if ((state == ILLNESS)||(is_ill == true))
    {
      cout<<GameObject::display_code<<GameObject::id_num<<": I am currently ill. I should go recover at the Doctor's Office instead of moving elsewhere."<<endl;
    }
  else
    {
      cout<<GameObject::display_code<<GameObject::id_num<<": On my way."<<endl;
      state = MOVING;
    }
    return;
}

void Student::StartMovingToClass(ClassRoom* classr)
{
  //Cout for checking errors
  //cout<<"Location of Student: "<<GetLocation()<<endl;
  //cout<<"Destination of Student: "<<destination<<endl;
  //cout<<"Location of ClassRoom: "<<classr->GetLocation()<<endl;
  if (state == INFECTED)
    {
      cout<<GameObject::display_code<<GameObject::id_num<<": I am infected so I can't move to class..."<<endl;
    }
  else if ((state == ILLNESS)||(is_ill == true))
    {
      cout<<GameObject::display_code<<GameObject::id_num<<": I am currently ill. I should go recover at the Doctor's Office instead of going to class."<<endl;
    }
  else if (this->GetLocation() == classr->GetLocation())
    {
      cout<<GameObject::display_code<<GameObject::id_num<<": I am already at the ClassRoom!"<<endl;
    }
  else
    {
      cout<<GameObject::display_code<<GameObject::id_num<<": On my way to class C"<<classr->GetId()<<endl;
      this->current_class = classr;
      this->destination = classr->GetLocation();
      SetupDestination(classr->GetLocation());
      state = MOVING_TO_CLASS;
    }
    return;
}

void Student::StartMovingToDoctor(DoctorsOffice* office)
{
  //cout<<"Location of Student: "<<GetLocation()<<endl;
  //cout<<"Destination of Student: "<<destination<<endl;
  //cout<<"Location of Office: "<<office->GetLocation()<<endl;
  if (state == INFECTED)
    {
      cout<<GameObject::display_code<<GameObject::id_num<<": I am infected so I should have gone to the doctor's..."<<endl;
    }
  else if ((state == ILLNESS)||(is_ill == true))
    {
      cout<<GameObject::display_code<<GameObject::id_num<<": I am currently ill. I will go recover at the Doctor's Office."<<endl;
      this->current_office = office;
      this->destination = office->GetLocation();
      SetupDestination(current_office->GetLocation());
      state = MOVING_TO_DOCTOR;
    }
  else if (this->GetLocation() == office->GetLocation())
    {
      cout<<GameObject::display_code<<GameObject::id_num<<": I am already at the Doctor's!"<<endl;
    }
  else
    {
      cout<<GameObject::display_code<<GameObject::id_num<<": On my way to doctor's D"<<office->GetId()<<endl;
      this->current_office = office;
      this->destination = office->GetLocation();
      SetupDestination(current_office->GetLocation());
      state = MOVING_TO_DOCTOR;
    }
    return;
}

void Student::StartLearning(unsigned int num_assignments)
{
  if (current_class->GetLocation() != this->GetLocation())
  {
    cout<<GameObject::display_code<<GameObject::id_num<<": I can only learn in a ClassRoom!"<<endl;
  }
  else {
    if (state == INFECTED)
    {
      cout<<GameObject::display_code<<GameObject::id_num<<": I am infected so no more school for me..."<<endl;
    }
    else if ((state == ILLNESS)||(is_ill == true))
    {
      cout<<GameObject::display_code<<GameObject::id_num<<": I am currently ill. I should go recover at the Doctor's Office instead of going to class."<<endl;
    }
    else if (current_class->GetLocation() != this->GetLocation())
    {
      cout<<GameObject::display_code<<GameObject::id_num<<": I can only learn in a ClassRoom!"<<endl;
    }
    else if (current_class->GetDollarCost(num_assignments) >= dollars)
    {
      cout<<GameObject::display_code<<GameObject::id_num<<": Not enough money for school..."<<endl;
    }
    else if (current_class->GetNumAssignmentsRemaining() == 0)
    {
      cout<<GameObject::display_code<<GameObject::id_num<<": Cannot learn! This ClassRoom has no more assignments"<<endl;
    }
    else
    {
      state = STUDYING_IN_CLASS;
      cout<<GameObject::display_code<<GameObject::GetId()<<": Started to learn at the ClassRoom C"<<GameObject::id_num<<" with ";
      cout<<current_class->GetNumAssignmentsRemaining()<<" assignments remaining"<<endl;
      assignments_to_buy = num_assignments;
    }
  }
  return;
}

void Student::StartRecoveringAntibodies(unsigned int num_vaccines)
{
  if (current_office->GetLocation() != this->GetLocation()) {
    cout<<GameObject::display_code<<GameObject::id_num<<": I can only recover antibodies at a Doctor's Office!"<<endl;
  }
  else {
    if (dollars < current_office->GetDollarCost(num_vaccines))
    {
      cout<<GameObject::display_code<<GameObject::id_num<<": Not enough money to recover antibodies."<<endl;
    }
    else if (0 == current_office->GetNumVaccineRemaining())
    {
      cout<<GameObject::display_code<<GameObject::id_num<<": Cannot recover! No vaccine remaining in this Doctor's Office!"<<endl;
    }
    else if ((state == ILLNESS)||(is_ill == true))
    {
      cout<<GameObject::display_code<<GameObject::id_num<<": I am currently ill. But I should feel better next turn."<<endl;
      state = RECOVERING_ILLNESS;
    }
    else if (current_office->CanAffordVaccine(num_vaccines,dollars)==1)
    {
      state = RECOVERING_ANTIBODIES;
      cout<<GameObject::display_code<<GameObject::id_num<<": Started recovering and "<<current_office->GetNumVaccineRemaining();
      cout<<" remaining vaccines at Doctor's Office D"<<current_office->GetId()<<endl;
      vaccines_to_buy = num_vaccines;
    }
    else
    {
      cout<<": I'm not recovering due to unknown issues, let's try again."<<endl;
    }
  }
  return;
}

void Student::Stop()
{
  state = STOPPED;
  cout<<GameObject::display_code<<GameObject::id_num<<": Stopping..."<<endl;
  destination = this->location;
  return;
}

bool Student::IsInfected()
{
  if (antibodies == 0)
    {
      return true;
    }
  else
    return false;
}

bool Student::ShouldBeVisible()
{
  if (state != INFECTED)
  {
    return true;
  }
  else
    return false;
}

void Student::ShowStatus()
{
  cout<<Student::name<<" status: ";
  GameObject::ShowStatus();
  if (state == STOPPED)
  {
    cout<<" stopped"<<endl;
    cout<<"\t"<<"Antibodies: "<<antibodies<<endl;
    cout<<"\t"<<"Dollars: "<<dollars<<endl;
    cout<<"\t"<<"Credits: "<<credits<<endl;
    return;
  }
  else if (state == MOVING)
  {
    cout<<" moving at a speed of "<<speed<<" to destination "<<destination<<" at each step of "<<delta<<endl;
    cout<<"\t"<<"Antibodies: "<<antibodies<<endl;
    cout<<"\t"<<"Dollars: "<<dollars<<endl;
    cout<<"\t"<<"Credits: "<<credits<<endl;
    return;
  }
  else if (state == MOVING_TO_CLASS)
  {
    cout<<" heading to ClassRoom C"<<current_class->GetId()<<" at a speed of "<<speed<<" at each step of "<<delta<<endl;
    cout<<"\t"<<"Antibodies: "<<antibodies<<endl;
    cout<<"\t"<<"Dollars: "<<dollars<<endl;
    cout<<"\t"<<"Credits: "<<credits<<endl;
    return;
  }
  else if (state == MOVING_TO_DOCTOR)
  {
    cout<<" heading to Doctor's D"<<current_office->GetId()<<" at a speed of "<<speed<<" at each step of "<<delta<<endl;
    cout<<"\t"<<"Antibodies: "<<antibodies<<endl;
    cout<<"\t"<<"Dollars: "<<dollars<<endl;
    cout<<"\t"<<"Credits: "<<credits<<endl;
    return;
  }
  else if (state == IN_CLASS)
  {
    cout<<" inside ClassRoom C"<<current_class->GetId()<<endl;
    cout<<"\t"<<"Antibodies: "<<antibodies<<endl;
    cout<<"\t"<<"Dollars: "<<dollars<<endl;
    cout<<"\t"<<"Credits: "<<credits<<endl;
    return;
  }
  else if (state == AT_DOCTORS)
  {
    cout<<" inside Doctor's Office D"<<current_office->GetId()<<endl;
    cout<<"\t"<<"Antibodies: "<<antibodies<<endl;
    cout<<"\t"<<"Dollars: "<<dollars<<endl;
    cout<<"\t"<<"Credits: "<<credits<<endl;
    return;
  }
  else if (state == STUDYING_IN_CLASS)
  {
    cout<<" studying in ClassRoom C"<<current_class->GetId()<<endl;
    cout<<"\t"<<"Antibodies: "<<antibodies<<endl;
    cout<<"\t"<<"Dollars: "<<dollars<<endl;
    cout<<"\t"<<"Credits: "<<credits<<endl;
    return;
  }
  else if (state == RECOVERING_ANTIBODIES)
  {
    cout<<" recovering antibodies in Doctor's Office D"<<current_office->GetId()<<endl;
    cout<<"\t"<<"Antibodies: "<<antibodies<<endl;
    cout<<"\t"<<"Dollars: "<<dollars<<endl;
    cout<<"\t"<<"Credits: "<<credits<<endl;
    return;
  }
  else if (state == ILLNESS)
  {
    cout<<" currently ill with "<<current_virus->GetVariantName()<<"virus"<<endl;
    cout<<"\t"<<"Antibodies: "<<antibodies<<endl;
    cout<<"\t"<<"Illness is deprecating antibodies by "<<current_virus->GetResistance()<<" every step!"<<endl;
    cout<<"\t"<<"Dollars: "<<dollars<<endl;
    cout<<"\t"<<"Credits: "<<credits<<endl;
    return;
  }
  else if (state == RECOVERING_ILLNESS)
  {
    cout<<" recovering from illness in Doctor's Office D"<<current_office->GetId()<<endl;
    cout<<"\t"<<"Antibodies: "<<antibodies<<endl;
    cout<<"\t"<<"Dollars: "<<dollars<<endl;
    cout<<"\t"<<"Credits: "<<credits<<endl;
    return;
  }
    return;
}

bool Student::Update()
{
  if (state == STOPPED)
  {
    return false;
  }
  else if (state == MOVING)
  {
    if (IsInfected()==1)
    {
      cout<<name<<" is out of antibodies and can't move"<<endl;
      state = INFECTED;
      return true;
    }
    else if (is_ill == true)
    {
      state = ILLNESS;
      cout<<name<<" is currently ill and should move to the doctor's"<<endl;
      is_at_doctor = false;
      is_in_class = false;
      return false;
    }
    else {
      bool loc = this->UpdateLocation();
      if (loc == 1)
      {
        state = STOPPED;
        return true;
      }
      else {
        state = MOVING;
        //Increase dollars & decrease Antibodies
        this->StepUpdate();
        is_at_doctor = false;
        is_in_class = false;
        return false;
      }
    }
  }
  else if (state == MOVING_TO_CLASS)
  {
    if (IsInfected()==1)
    {
      cout<<name<<" is out of antibodies and can't move"<<endl;
      state = INFECTED;
      return true;
    }
    else if (is_ill == true)
    {
      state = ILLNESS;
      cout<<name<<" is currently ill and should move to the doctor's"<<endl;
      is_at_doctor = false;
      is_in_class = false;
      return false;
    }
    else {
      bool loc = this->UpdateLocation();
      if (loc == 1)
      {
        state = IN_CLASS;
        is_in_class = true;
        current_class->AddOneStudent();
        return true;
      }
      else {
        state = MOVING_TO_CLASS;
        //Increase dollars & decrease Antibodies
        this->StepUpdate();
        is_at_doctor = false;
        is_in_class = false;
        return false;
      }
    }
  }
  else if (state == MOVING_TO_DOCTOR)
  {
    if (IsInfected()==1)
    {
      cout<<name<<" is out of antibodies and can't move"<<endl;
      state = INFECTED;
      return true;
    }
    /*else if (is_ill == true)
    {
      state = ILLNESS;
      cout<<name<<" is currently ill and so I'm glad to move to the doctor"<<endl;
      is_at_doctor = false;
      is_in_class = false;
      return false;
    }*/
    else {
      bool loc = this->UpdateLocation();
      if (loc == 1)
      {
        state = AT_DOCTORS;
        is_at_doctor = true;
        current_office->AddOneStudent();
        if (is_ill == true) {
          state = RECOVERING_ILLNESS;
        }
        return true;
      }
      else {
        state = MOVING_TO_DOCTOR;
        //Increase dollars & decrease Antibodies
        this->StepUpdate();
        is_at_doctor = false;
        is_in_class = false;
        return false;
      }
    }
  }
  else if (state == IN_CLASS)
  {
    is_in_class = true;
    return false;
  }
  else if (state == AT_DOCTORS)
  {
    is_at_doctor = true;
    return false;
  }
  else if (state == STUDYING_IN_CLASS)
  {
    is_in_class = true;
    unsigned int tempcredits = current_class->TrainStudents(assignments_to_buy);
    credits = credits + tempcredits;
    antibodies = antibodies - current_class->GetAntibodyCost(assignments_to_buy);
    dollars = dollars - current_class->GetDollarCost(assignments_to_buy);
    cout<<"* * "<<name<<" completed "<<assignments_to_buy<<" assignment(s)! * *"<<endl;
    cout<<"* * "<<name<<" gained "<<tempcredits<<" credit(s)! * *"<<endl;
    current_class->RemoveOneStudent();
    state = IN_CLASS;
    return true;
  }
  else if (state == RECOVERING_ANTIBODIES)
  {
    is_at_doctor = true;
    vaccines_to_buy = current_office->DistributeVaccine(vaccines_to_buy); //THis is probs wrong
    antibodies = antibodies + (5*vaccines_to_buy);
    dollars = dollars - current_office->GetDollarCost(vaccines_to_buy);
    cout<<"* * "<<name<<" bought "<<vaccines_to_buy<<" vaccine(s)! * *"<<endl;
    cout<<"* * "<<name<<" recovered "<<(vaccines_to_buy*5)<<" antibodies! * *"<<endl;
    current_office->RemoveOneStudent();
    state = AT_DOCTORS;
    return true;
  }
  else if (state == RECOVERING_ILLNESS)
  {
    Vector2D v1(0,0);
    current_virus->movement = v1;
    current_virus->energy = 0;
    is_ill = false;
    cout<<name<<" recovered from illness from virus variant "<<current_virus->GetVariantName()<<endl;
  }
}

bool Student::UpdateLocation()
{
  Vector2D diff = this->destination-this->location;
  //cout<<"difference: "<<diff<<endl;
  //cout<<"delta: "<<delta<<endl;
  if (this->GetLocation() == destination)
  {
    cout<<GameObject::display_code<<GameObject::id_num<<": I'm there!"<<endl;
    return true;
  }
  else if ((fabs(this->delta.x)>=fabs(diff.x))&&(fabs(this->delta.y)>=fabs(diff.y)))
  {
    this->location = this->destination;
    cout<<GameObject::display_code<<GameObject::id_num<<": Arrived!"<<endl;
    this->StepUpdate();
    return true;
  }
  else
  {
    cout<<GameObject::display_code<<GameObject::id_num<<": Step step..."<<endl;
    this->location = this->location+this->delta;
    return false;
  }
}

void Student::SetupDestination(Point2D dest)
{
  this->delta = (dest - this->location)*(this->speed / GetDistanceBetween(dest, this->GetLocation()));
  return;
}

void Student::StepUpdate() //Updates antibodies and dollars every step
{
  //To check for if this function is called
  //cout<<"StepUpdate called"<<endl;
  if (state != ILLNESS) {
    this->antibodies = this->antibodies - 1;
  }
  else if (state == ILLNESS) {
    this->antibodies = this->antibodies - 1 - current_virus->GetResistance();
  }
  double value = GetRandomAmountOfDollars();
  this->dollars = this->dollars + value;
  return;
}

Student::~Student()
{
  cout<<"Student destructed"<<endl;
}

string Student::GetName()
{
  return name;
}

unsigned int Student::GetAntibodies() const
{
  return antibodies;
}

static double GetRandomAmountOfDollars() //Doesn't work as intended
{
  srand(time(0));
  double value = static_cast <double> (rand()/ static_cast <double> (RAND_MAX));
  value = value*2.0;
  //cout<<"Dollars: "<<value<<endl;
  return value;
}
