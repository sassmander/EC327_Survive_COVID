#include <iostream>
#include <string>
#include <vector>
#include <bits/stdc++.h>
#include <limits>
#include <ios>

#include "Vector2D.h"
#include "GameObject.h"
#include "Building.h"
#include "ClassRoom.h"
#include "Student.h"
#include "Model.h"
#include "View.h"
#include "GameCommand.h"
#include "Point2D.h"
//#include "Input_Handling.h"
#include "Virus.h"

using namespace std;

//Remaining issues:
//No asterisks for multiple objects

int main()
{
  //Title screen
  cout<<"_____  _____  __    __  __  _____"<<endl;
  cout<<"-----  -----  --    --  --  ----- \\"<<endl;
  cout<<"||     |   |   \\    /   ||   ||    \\"<<endl;
  cout<<"||     |   |    \\  /    ||   ||    /"<<endl;
  cout<<"_____  _____     __     __  _____ /"<<endl;
  cout<<"-----  -----     --     --  -----"<<endl;
  cout<<endl;
  cout<<"_____  __    __  ______  ___    _____   _____  _____   __ __"<<endl;
  cout<<"-----  --    --  ------  --- \\  -----\\  -----  -----   -- --"<<endl;
  cout<<"|   |   |    |     ||     |  /  ||    | |     |     |  |  /"<<endl;
  cout<<"|   |   |    |     ||     |  \\  ||---/  |---- |-----|  | /"<<endl;
  cout<<"_____    ____      ||     |  /  ||    \\ |     |     |  | \\"<<endl;
  cout<<"-----    ----      --    ----   ||    | |---- |     |  |  \\"<<endl;
  cout<<endl<<endl;


  //Initialize Model and View
  Model model;
  View view;
  model.Display(&view);
  model.ShowStatus();

  do {
  //Get user command
  char choice;
  int s_id, para;
  unsigned int vora;
  double xpoint, ypoint;
  string command;
  cout<<endl;
  cout<<"Enter command character then Enter: ";
  cin>>choice;
  cin.ignore(numeric_limits<streamsize>::max(), '\n');

    //int1, int2, Point2D, view
    switch (choice) {
      case 'm': {
        cout<<"Enter student id and command parameters then Enter: ";
        cin>>s_id>>xpoint>>ypoint;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        Point2D p1(xpoint, ypoint);
        DoMoveCommand(&model, s_id, p1);
      }
        break;
      case 'd': {
        cout<<"Enter student id and command parameter then Enter: ";
        cin>>s_id>>para;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        DoMoveToDoctorCommand(&model, s_id, para);
      }
        break;
      case 'c': {
        cout<<"Enter student id and command parameter then Enter: ";
        cin>>s_id>>para;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        DoMoveToClassCommand(&model, s_id, para);
      }
        break;
      case 's': {
        cout<<"Enter student id then Enter: ";
        cin>>s_id;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        DoStopCommand(&model, s_id);
      }
        break;
      case 'v': {
        cout<<"Enter student id and command parameter then Enter: ";
        cin>>s_id>>vora;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        DoRecoverInOfficeCommand(&model, s_id, vora);
      }
        break;
      case 'a': {
        cout<<"Enter student id and command parameter then Enter: ";
        cin>>s_id>>vora;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        DoLearningCommand(&model, s_id, vora);
      }
        break;
      case 'n': {
        char typenew;
        int idnew;
        double xnew, ynew;
        cout<<"Enter type for new object"<<endl<<"d for Office, c for ClassRoom, s for Student, v for Virus: ";
        cin>>typenew;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout<<"Enter new object's ID, followed by the X Y coordinates of starting location (0-20): ";
        cin>>idnew>>xnew>>ynew;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        Point2D p2(xnew, ynew);
        NewCommand(&model, &view, typenew, idnew, p2);
      }
        break;
      case 'g':
        DoGoCommand(&model, &view);
        break;
      case 'r':
        DoRunCommand(&model, &view);
        break;
      case 'q': {
        model.~Model();
        exit(0);
        }
        break;
      default: cout<<"Invalid command!"<<endl;
    }

    model.Display(&view);
    model.ShowStatus();

    //Clear vector for new commands
    //tokens.clear();

  } while (true);

  //Saved code
  /*while (getline(check, intermediate, ' '))
  {
    remove(intermediate.begin(), intermediate.end(), ' ');
    tokens.push_back(intermediate);
  }*/

  //For checking stream input
  /*for (unsigned int i = 0; i < tokens.size(); i++)
  {
    cout<<tokens[i]<<" ";
  }
  cout<<choice<<endl;

  //For checking student id input
  if (static_cast <int> (tokens[0]) == 1) {
    cout<<"Homer is chosen"<<endl<<endl;
  }
  else if (static_cast <int> (tokens[0]) == 2) {
    cout<<"Marge is chosen"<<endl<<endl;
  }*/

  //Just in case
  model.~Model();
  return 0;
}
