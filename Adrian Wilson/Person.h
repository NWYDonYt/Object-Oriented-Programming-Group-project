//Person Header File
#ifndef PERSON_H
#define PERSON_H

#include <string>

// Abstract base class: you cannot create a Person directly.
// Player, Coach, Spectator, MatchOfficial and LeagueCommissioner will inherit from it.
class Person {
private:
    int id;
    string name;
    int age;
    string gender;

public:
    Person(int personId, string personName, int personAge, string personGender);
   
    virtual ~Person() {}

    int getId() const;
    string getName() const;
    int getAge() const;
    string getGender() const;

    void setName(string newName);
    void setAge(int newAge);
    void setGender(string newGender);

    // Pure virtual: every kind of person must show its own details
    virtual void displayInformation() const = 0;
};

#endif

