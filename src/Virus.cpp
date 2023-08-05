#include "Virus.h"
#include <iostream>

using namespace std;

Virus::Virus()
:GameObject('V')
{
  state = IN_ENVIRONMENT;
  virulence = 5;
  resistance = 2;
  variant = 'w';
  energy = 20;
  is_in_student = false;
  current_student = NULL;
  virusrange = 1;
  cout<<"Wild-type Virus default constructed"<<endl;
}

Virus::Virus(int id, unsigned int viru, unsigned int resist, unsigned int ener, char var, Point2D in_loc)
:GameObject(in_loc, id, 'V')
{
  state = IN_ENVIRONMENT;
  virulence = viru;
  resistance = resist;
  variant = var;
  energy = ener;
  is_in_student = false;
  current_student = NULL;
  if (variant == 'w') {
    virusrange = 1;
    cout<<"Wild-type Virus constructed"<<endl;
  }
  else if (variant == 'a') {
    virusrange = 2;
    cout<<"Variant type Alpha Virus constructed"<<endl;
  }
  else if (variant == 'd') {
    virusrange = 4;
    cout<<"Variant type Delta Virus constructed"<<endl;
  }
  else {
    variant = 'w';
    virusrange = 2;
    cout<<"Variant request not detected, wild-type Virus constructed"<<endl;
  }
}

Virus::~Virus()
{
  cout<<"Virus destructed"<<endl;
}

bool Virus::Infect(Student* sptr)
{
  if ((state != DEAD)&&(virusrange <= GetDistanceBetween(this->GetLocation(), sptr->GetLocation()))&&(sptr->GetAntibodies() <= GetVirulence())) {
    current_student = sptr;
    is_in_student = true;
    movement = current_student->delta;
    current_student->is_ill = true;
    current_student->current_virus = this;
    cout<<"Student "<<current_student->GetName()<<" was infected by virus variant "<<GetVariantName()<<endl;
    return true;
  }
  else {
    return false;
  }
}

char Virus::GetVariant() const
{
  return variant;
}


string Virus::GetVariantName()
{
  string out;
  if (variant == 'w') {
    out = "wild-type";
  }
  else if (variant == 'a') {
    out = "alpha";
  }
  else if (variant == 'd') {
    out = "delta";
  }

  return out;
}

unsigned int Virus::GetVirulence() const
{
  return virulence;
}

unsigned int Virus::GetResistance() const
{
  return resistance;
}

unsigned int Virus::GetEnergy() const
{
  return energy;
}

bool Virus::GetInStudent() const
{
  return is_in_student;
}

bool Virus::Update()
{
  if (state == IN_ENVIRONMENT)
  {
    VStepUpdate();
    return false;
  }
  else if (state == IN_STUDENT)
  {
    if (IsAlive() == 0) {
      state = DEAD;
    }
    else {
      is_in_student = true;
      VStepUpdate();
    }
    return false;
  }
  else if (state == DEAD)
  {
    return false; //just to compile
  }
}

void Virus::ShowStatus()
{
  cout<<"Virus variant "<<GetVariantName()<<" status: ";
  if (state == IN_ENVIRONMENT)
  {
    cout<<"Currently floating somewhere"<<endl;
    cout<<"\t"<<"Virulence (initial antibodies needed to fight off infection): "<<GetVirulence()<<endl;
    cout<<"\t"<<"Resistance (antibodies used up every turn once infected): "<<GetResistance()<<endl;
    cout<<"\t"<<"Energy left (life meter, deprecates by 1 if not infecting): "<<GetEnergy()<<endl;
  }
  else if (state == IN_STUDENT)
  {
    cout<<"Currently infecting S"<<current_student->GetId()<<endl;
    cout<<"\t"<<"Virulence (initial antibodies needed to fight off infection): "<<GetVirulence()<<endl;
    cout<<"\t"<<"Resistance (antibodies used up every turn once infected): "<<GetResistance()<<endl;
    cout<<"\t"<<"Energy left (life meter, deprecates by 1 if not infecting): "<<GetEnergy()<<endl;
  }
  else if (state == DEAD)
  {
    cout<<"\t"<<"Currently deactivated"<<endl;
  }
}

bool Virus::IsAlive()
{
  if (energy > 0)
  {
    return true;
  }
  else if (energy == 0)
  {
    return false;
  }
}

bool Virus::ShouldBeVisible()
{
  return false;
}

void Virus::VStepUpdate()
{
  if (is_in_student == false) {
    if (this->energy >= 1) {
      this->energy = this->energy - 1;
    }
    else {
      this->energy = 0;
    }
  }
  else if (is_in_student == true) {
    this->energy = this->energy;
  }
}
