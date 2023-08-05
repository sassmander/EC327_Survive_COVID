#ifndef STUDENT
#define STUDENT
#include <iostream>
#include <string>
#include "Point2D.h"
#include "Vector2D.h"
#include "ClassRoom.h"
#include "DoctorsOffice.h"
#include "Virus.h"

using namespace std;

enum StudentStates
{
  STOPPED = 0,
  MOVING = 1,
  INFECTED = 2,
  AT_DOCTORS = 3,
  IN_CLASS = 4,
  MOVING_TO_DOCTOR = 5,
  MOVING_TO_CLASS = 6,
  STUDYING_IN_CLASS = 7,
  RECOVERING_ANTIBODIES = 8,
  ILLNESS = 9,
  RECOVERING_ILLNESS = 10
};
class Virus;

class Student: virtual public GameObject
{
public:
  Student(); //default constructor
  Student(char);
  Student(string, int, unsigned int, Point2D);
  void StartMoving(Point2D);
  void StartMovingToClass(ClassRoom *);
  void StartMovingToDoctor(DoctorsOffice*);
  void StartLearning(unsigned int);
  void StartRecoveringAntibodies(unsigned int);
  void Stop();
  bool IsInfected();
  bool ShouldBeVisible();
  void ShowStatus();
  bool Update();
  string GetName();
  virtual ~Student(); //Virtual destructor
  bool is_ill;
  Vector2D delta;
  Virus* current_virus;
  //My additions
  void StepUpdate();
  unsigned int GetAntibodies() const;

protected:
  bool UpdateLocation();
  void SetupDestination(Point2D);

private:
  double speed;
  bool is_at_doctor;
  bool is_in_class;
  unsigned int antibodies;
  unsigned int credits;
  double dollars;
  unsigned int assignments_to_buy;
  unsigned int vaccines_to_buy;
  string name;
  DoctorsOffice* current_office;
  ClassRoom* current_class;
  Point2D destination;
  //PA4 addition

};

static double GetRandomAmountOfDollars();
#endif
