#include "ClassRoom.h"
#include <iostream>

using namespace std;

ClassRoom::ClassRoom(): GameObject('C'), Building() //default constructor
{
  state = NOT_PASSED; //Not passed
  max_number_of_assignments = 10;
  num_assignments_remaining = max_number_of_assignments;
  antibody_cost_per_assignment = 1;
  dollar_cost_per_assignment = 1.0;
  credits_per_assignment = 2;
  cout<<"ClassRoom default constructed"<<endl;
}

ClassRoom::ClassRoom(int in_id, unsigned int antibody_cost, double dollar_cost, unsigned int crd_per_assign, unsigned int max_assign, Point2D in_loc)
:GameObject(in_loc, in_id, 'C'), Building()
{
  max_number_of_assignments = max_assign;
  antibody_cost_per_assignment = antibody_cost;
  credits_per_assignment = crd_per_assign;
  dollar_cost_per_assignment = dollar_cost;

  //default values
  state = NOT_PASSED; //Not passed
  num_assignments_remaining = max_number_of_assignments;
  cout<<"ClassRoom constructed"<<endl;
}

double ClassRoom::GetDollarCost(unsigned int unit_qty) const
{
  return (unit_qty*dollar_cost_per_assignment);
}

unsigned int ClassRoom::GetAntibodyCost(unsigned int unit_qty) const
{
  return (unit_qty*antibody_cost_per_assignment);
}

unsigned int ClassRoom::GetNumAssignmentsRemaining() const
{
  return num_assignments_remaining;
}

bool ClassRoom::IsAbleToLearn(unsigned int unit_qty, double budget, unsigned int antibodies)
{
  //true if a ClassRoom can request to take unit_qty assignments
  if ((unit_qty*dollar_cost_per_assignment <= budget) && (antibodies >= (antibody_cost_per_assignment*unit_qty)))
  {
    return true;
  }
  else
    return false;
}

unsigned int ClassRoom::TrainStudents(unsigned int assignment_units)
{
  //subtracts assignments from num_assignments_remaining
  //need to account for unit requested being bigger than num_assignments_remaining
  unsigned int temp_unit = num_assignments_remaining;
  num_assignments_remaining = num_assignments_remaining-assignment_units;
  if (temp_unit >= assignment_units)
  {
    return (assignment_units*credits_per_assignment);
  }
  else
  {
    num_assignments_remaining = 0;
    return(temp_unit*credits_per_assignment);
  }
}

bool ClassRoom::Update()
{
  if (num_assignments_remaining == 0 && state == NOT_PASSED)
  {
    state = PASSED;
    GameObject::display_code = 'c';
    cout<<"ClassRoom "<<Building::GameObject::display_code<<Building::GameObject::GetId();
    cout<<" has been passed"<<endl;
    return true;
  }
  else if (state = PASSED)
    return false;
  else
    return false;
}

bool ClassRoom::passed()
{
  if (num_assignments_remaining == 0)
    return true;
  else
    return false;
}

void ClassRoom::ShowStatus()
{
  cout<<"ClassRoomStatus: ";
  Building::ShowStatus();
  cout<<"\t"<<"Max number of assignments: "<<max_number_of_assignments<<endl;
  cout<<"\t"<<"Antibody cost per assignment: "<<antibody_cost_per_assignment<<endl;
  cout<<"\t"<<"Dollar per assignment: "<<dollar_cost_per_assignment<<endl;
  cout<<"\t"<<"credits per assignment: "<<credits_per_assignment<<endl;
  cout<<"\t"<<num_assignments_remaining<<" assignment(s) are remaining for the ClassRoom"<<endl;
}

ClassRoom::~ClassRoom()
{
  cout<<"ClassRoom destructed"<<endl;
}
