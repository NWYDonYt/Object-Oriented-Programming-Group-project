#include "MatchOfficial.h"
#include "Exceptions.h"
#include "FileManager.h"
#include <iostream>
using namespace std;

MatchOfficial::MatchOfficial()
    : Person(0, "Match Official", 30, "Unspecified"),
      officiatingRole("Referee"), rank("National"), available(true) {}

MatchOfficial::MatchOfficial(int personId, const std::string& personName, int personAge, const std::string& personGender,
                             const std::string& role, const std::string& officialRank, bool isAvailable)
    : Person(personId, personName, personAge, personGender) {
    setOfficiatingRole(role);
    setRank(officialRank);
    available = isAvailable;
}

MatchOfficial::MatchOfficial(const MatchOfficial& other)
    : Person(other.id, other.name, other.age, other.gender),
      officiatingRole(other.officiatingRole), rank(other.rank), available(other.available) {}

std::string MatchOfficial::getOfficiatingRole() const {
    return officiatingRole;
}

std::string MatchOfficial::getRank() const {
    return rank;
}

bool MatchOfficial::isAvailable() const {
    return available;
}

void MatchOfficial::setOfficiatingRole(const std::string& newRole) {
    if (newRole.empty()) {
        throw InvalidDataException("Officiating role cannot be empty.");
    }
    officiatingRole = newRole;
}

void MatchOfficial::setRank(const std::string& newRank) {
    if (newRank.empty()) {
        throw InvalidDataException("Official rank cannot be empty.");
    }
    rank = newRank;
}

void MatchOfficial::setAvailable(bool isAvailable) {
    available = isAvailable;
}

void MatchOfficial::displayInformation() const {
    std::cout << "[Official] ID: " << id
              << " | Name: " << name
              << " | Age: " << age
              << " | Gender: " << gender
              << " | Role: " << officiatingRole
              << " | Rank: " << rank
              << " | Available: " << (available ? "Yes" : "No") << std::endl;
}

std::string MatchOfficial::toRecord() const {
    std::vector<std::string> fields;
    fields.push_back(FileManager::toText(id));
    fields.push_back(name);
    fields.push_back(FileManager::toText(age));
    fields.push_back(gender);
    fields.push_back(officiatingRole);
    fields.push_back(rank);
    fields.push_back(available ? "1" : "0");
    return FileManager::joinFields(fields);
}

void MatchOfficial::fromRecord(const std::string& record) {
    std::vector<std::string> fields = FileManager::splitFields(record);
    if (fields.size() < 7) {
        throw FileException("MatchOfficial record requires 7 fields: " + record);
    }
    setId(FileManager::toInt(fields[0]));
    setName(fields[1]);
    setAge(FileManager::toInt(fields[2]));
    setGender(fields[3]);
    setOfficiatingRole(fields[4]);
    setRank(fields[5]);
    setAvailable(fields[6] == "1" || fields[6] == "true");
}
