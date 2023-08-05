#ifndef GAMECOMMAND
#define GAMECOMMAND
#include <iostream>
#include "Model.h"
#include "Point2D.h"
#include "Vector2D.h"
#include "GameObject.h"
#include "Building.h"
#include "ClassRoom.h"
#include "DoctorsOffice.h"
#include "Virus.h"
#include "View.h"

using namespace std;

void DoMoveCommand(Model*, int, Point2D);
void DoMoveToDoctorCommand(Model*, int, int);
void DoMoveToClassCommand(Model*, int, int);
void DoStopCommand(Model*, int);
void DoLearningCommand(Model*, int, unsigned int);
void DoRecoverInOfficeCommand(Model*, int, unsigned int);
void DoGoCommand(Model*, View*);
void DoRunCommand(Model*, View*);

//PA4 additions
void NewCommand(Model*, View*, char, int, Point2D);

#endif
