#include "DoctorsOffice.h"
#include <iostream>

using namespace std;

DoctorsOffice::DoctorsOffice() : GameObject('D'), Building()
{
  //GameObject::display_code = 'D';
  vaccine_capacity = 100;
  num_vaccine_remaining = vaccine_capacity;
  dollar_cost_per_vaccine = 5;
  state = VACCINE_AVAILABLE;
  cout<<"DoctorsOffice default constructed"<<endl;
}

DoctorsOffice::DoctorsOffice(int in_id, double vaccine_cost, unsigned int vaccine_cap, Point2D in_loc)
: GameObject(in_loc, in_id, 'D'), Building()
{
  //GameObject::id_num = in_id;
  //GameObject::location = in_loc;
  dollar_cost_per_vaccine = vaccine_cost;
  vaccine_capacity = vaccine_cap;
  num_vaccine_remaining = vaccine_capacity;
  //GameObject::display_code = 'D';
  state = VACCINE_AVAILABLE;
  cout<<"DoctorsOffice constructed"<<endl;
}

bool DoctorsOffice::HasVaccine()
{
  if (state = VACCINE_AVAILABLE)
    return true;
  else
    return false;
}

unsigned int DoctorsOffice::GetNumVaccineRemaining() const
{
  return num_vaccine_remaining;
}

bool DoctorsOffice::CanAffordVaccine(unsigned int vaccine, double budget) const
{
  if (vaccine*dollar_cost_per_vaccine <= budget)
    return true;
  else
    return false;
}

double DoctorsOffice::GetDollarCost(unsigned int vaccine) const
{
  return (vaccine*dollar_cost_per_vaccine);
}

unsigned int DoctorsOffice::DistributeVaccine(unsigned int vaccine_needed)
{
  if (num_vaccine_remaining >= vaccine_needed)
  {
    num_vaccine_remaining = num_vaccine_remaining - vaccine_needed;
    return vaccine_needed;
  }
  else
  {
    unsigned int tempvalue = num_vaccine_remaining;
    num_vaccine_remaining = 0;
    return tempvalue;
  }
}

bool DoctorsOffice::Update()
{
  if (num_vaccine_remaining == 0 && state == VACCINE_AVAILABLE)
  {
    state = NO_VACCINE_AVAILABLE;
    GameObject::display_code = 'd';
    cout<<"DoctorsOffice "<<Building::GameObject::GetId()<<" has ran out of vaccine"<<endl;
    return true;
  }
  else if (state == NO_VACCINE_AVAILABLE)
    return false;
  else
    return false;
}

void DoctorsOffice::ShowStatus()
{
  cout<<"DoctorsOffice Status: ";
  Building::ShowStatus();
  cout<<"\t"<<"Dollars per vaccine: "<<dollar_cost_per_vaccine<<endl;
  cout<<"\t"<<"Has "<<num_vaccine_remaining<<" vaccine(s) remaining."<<endl;
}

DoctorsOffice::~DoctorsOffice()
{
  cout<<"Office destructed"<<endl;
}
