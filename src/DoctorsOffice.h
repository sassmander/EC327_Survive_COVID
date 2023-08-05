#ifndef DOCTORSOFFICE
#define DOCTORSOFFICE
#include <iostream>
#include "Point2D.h"
#include "Building.h"
#include "GameObject.h"

using namespace std;

enum DoctorsOfficeStates
{
  VACCINE_AVAILABLE = 0,
  NO_VACCINE_AVAILABLE = 1
};

class DoctorsOffice: public Building
{
private:
  unsigned int vaccine_capacity;
  unsigned int num_vaccine_remaining;
  double dollar_cost_per_vaccine;

public:
  DoctorsOffice();
  ~DoctorsOffice();
  DoctorsOffice(int, double, unsigned int, Point2D);
  bool HasVaccine();
  unsigned int GetNumVaccineRemaining() const;
  bool CanAffordVaccine(unsigned int, double) const;
  double GetDollarCost(unsigned int) const;
  unsigned int DistributeVaccine(unsigned int);
  bool Update();
  void ShowStatus();

};
#endif
