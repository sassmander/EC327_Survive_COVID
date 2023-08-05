#ifndef CLASSROOM
#define CLASSROOM
#include <iostream>
#include "Point2D.h"
#include "Building.h"
#include "GameObject.h"

using namespace std;

enum ClassRoomStates
{
  NOT_PASSED = 0,
  PASSED = 1
};

class ClassRoom: public Building
{
private:
  unsigned int num_assignments_remaining;
  unsigned int max_number_of_assignments;
  unsigned int antibody_cost_per_assignment;
  double dollar_cost_per_assignment;
  unsigned int credits_per_assignment;

public:
  ClassRoom();
  ~ClassRoom();
  ClassRoom(int, unsigned int, double, unsigned int, unsigned int, Point2D);
  double GetDollarCost(unsigned int) const;
  unsigned int GetAntibodyCost(unsigned int) const;
  unsigned int GetNumAssignmentsRemaining() const;
  bool IsAbleToLearn(unsigned int, double, unsigned int);
  unsigned int TrainStudents(unsigned int);
  bool Update();
  bool passed();
  void ShowStatus();

};
#endif
