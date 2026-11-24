#include "LeagueCommissioner.h"
#include "FootballTeam.h"
#include "Stadium.h"
#include "Exceptions.h"
#include "FileManager.h"
#include <iostream>

LeagueCommissioner::LeagueCommissioner()
    : Person(1, "Hon. Keith Wellington", 58, "Male"),
      officeLocation("KPFL Headquarters, Kingston"), badgeNumber("COMM-01"), yearsInService(8) {}

LeagueCommissioner::LeagueCommissioner(int personId, const std::string& personName, int personAge, const std::string& personGender,
                                       const std::string& office, const std::string& badge, int years)
    : Person(personId, personName, personAge, personGender) {
    setOfficeLocation(office);
    setBadgeNumber(badge);
    setYearsInService(years);
}

std::string LeagueCommissioner::getOfficeLocation() const {
    return officeLocation;
}

std::string LeagueCommissioner::getBadgeNumber() const {
    return badgeNumber;
}

int LeagueCommissioner::getYearsInService() const {
    return yearsInService;
}

void LeagueCommissioner::setOfficeLocation(const std::string& office) {
    if (office.empty()) {
        throw InvalidDataException("Commissioner office location cannot be empty.");
    }
    officeLocation = office;
}

void LeagueCommissioner::setBadgeNumber(const std::string& badge) {
    if (badge.empty()) {
        throw InvalidDataException("Badge number cannot be empty.");
    }
    badgeNumber = badge;
}

void LeagueCommissioner::setYearsInService(int years) {
    if (years < 0) {
        throw NegativeValueException("Years in service cannot be negative.");
    }
    yearsInService = years;
}

bool LeagueCommissioner::approveTeamRegistration(FootballTeam& team) {
    team.setLeagueStatus("Registered");
    std::cout << "[Commissioner Notice] Team '" << team.getName()
              << "' registration approved by Commissioner " << name << ".\n";
    return true;
}

bool LeagueCommissioner::inspectStadium(Stadium& stadium) const {
    std::cout << "[Commissioner Inspection] Commissioner " << name
              << " inspected stadium '" << stadium.getName()
              << "' (Condition: " << stadium.getFieldCondition()
              << ", Capacity: " << stadium.getCapacity() << "). Inspection PASSED.\n";
    return true;
}

void LeagueCommissioner::displayInformation() const {
    std::cout << "[Commissioner] ID: " << id
              << " | Name: " << name
              << " | Age: " << age
              << " | Gender: " << gender
              << " | Office: " << officeLocation
              << " | Badge: " << badgeNumber
              << " | Service: " << yearsInService << " yrs" << std::endl;
}

std::string LeagueCommissioner::toRecord() const {
    std::vector<std::string> fields;
    fields.push_back(FileManager::toText(id));
    fields.push_back(name);
    fields.push_back(FileManager::toText(age));
    fields.push_back(gender);
    fields.push_back(officeLocation);
    fields.push_back(badgeNumber);
    fields.push_back(FileManager::toText(yearsInService));
    return FileManager::joinFields(fields);
}

void LeagueCommissioner::fromRecord(const std::string& record) {
    std::vector<std::string> fields = FileManager::splitFields(record);
    if (fields.size() < 7) {
        throw FileException("LeagueCommissioner record requires 7 fields: " + record);
    }
    setId(FileManager::toInt(fields[0]));
    setName(fields[1]);
    setAge(FileManager::toInt(fields[2]));
    setGender(fields[3]);
    setOfficeLocation(fields[4]);
    setBadgeNumber(fields[5]);
    setYearsInService(FileManager::toInt(fields[6]));
}
