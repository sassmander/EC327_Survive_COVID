#ifndef VIRUS
#define VIRUS

#include <iostream>
#include <string>
#include "Point2D.h"
#include "Vector2D.h"
#include "Student.h"

using namespace std;

enum VirusStates {
  IN_ENVIRONMENT = 0,
  IN_STUDENT = 1,
  DEAD = 2
};
class Student;

class Virus: virtual public GameObject
{
protected:
  unsigned int virulence;
  unsigned int resistance;
  char variant; //w for WT, a for alpha, d for delta
  bool is_in_student;
  Student* current_student;
  //PA4 additions
  double virusrange;
  void VStepUpdate();


public:
  Virus();
  Virus(int, unsigned int, unsigned int, unsigned int, char, Point2D);
  virtual ~Virus();
  bool Infect(Student*);
  char GetVariant() const;
  string GetVariantName();
  unsigned int GetVirulence() const;
  unsigned int GetResistance() const;
  unsigned int GetEnergy() const;
  bool GetInStudent() const;
  bool Update();
  void ShowStatus();
  bool IsAlive();
  bool ShouldBeVisible();
  //PA4 additions
  Vector2D movement;
  unsigned int energy;


};
#endif
