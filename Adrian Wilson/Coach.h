
// Coach Header File
#ifndef COACH_H
#define COACH_H

#include "Person.h"
#include <iostream>
#include <string>

using namespace std;

class Coach : public Person {
private:
    string teamName;

public:
    Coach(int id, string name, int age, string gender, string team);

    string getTeamName() const;
    void setTeamName(string newTeam);

    void displayInformation() const override;
};

#endif
