// Person Header File
#ifndef PERSON_H
#define PERSON_H

#include <iostream>
#include <string>

using namespace std;

class Person {
private:
    int id;
    string name;
    int age;
    string gender;

public:
    Person(int personId, string personName, int personAge, string personGender) {
        id = personId;
        name = personName;
        age = personAge;
        gender = personGender;
    }

    virtual ~Person() {}

    int getId() const {
        return id;
    }

    string getName() const {
        return name;
    }

    int getAge() const {
        return age;
    }

    string getGender() const {
        return gender;
    }

    void setName(string newName) {
        name = newName;
    }

    void setAge(int newAge) {
        age = newAge;
    }

    void setGender(string newGender) {
        gender = newGender;
    }

    virtual void displayInformation() const = 0;
};

#endif

