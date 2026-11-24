// Coach.cpp

#include "Coach.h"

Coach::Coach(int id, string name, int age, string gender, string team)
    : Person(id, name, age, gender) {
    teamName = team;
}

string Coach::getTeamName() const {
    return teamName;
}

void Coach::setTeamName(string newTeam) {
    teamName = newTeam;
}

void Coach::displayInformation() const {
    cout << "Coach ID: " << getId() << endl;
    cout << "Name: " << getName() << endl;
    cout << "Age: " << getAge() << endl;00
    cout << "Gender: " << getGender() << endl;
    cout << "Team: " << teamName << endl;
}