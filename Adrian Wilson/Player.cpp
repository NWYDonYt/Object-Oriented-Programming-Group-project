// Person.cpp

#include "Person.h"

Person::Person(int personId, string personName, int personAge, string personGender) {
    id = personId;
    name = personName;
    age = personAge;
    gender = personGender;
}

Person::~Person() {}

int Person::getId() const {
    return id;
}

string Person::getName() const {
    return name;
}

int Person::getAge() const {
    return age;
}

string Person::getGender() const {
    return gender;
}

void Person::setName(string newName) {
    name = newName;
}

void Person::setAge(int newAge) {
    age = newAge;
}

void Person::setGender(string newGender) {
    gender = newGender;
}

