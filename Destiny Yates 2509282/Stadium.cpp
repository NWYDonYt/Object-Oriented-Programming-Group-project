#include "Stadium.h"
#include "Exceptions.h"
#include "FileManager.h"
#include <iostream>
#include <iomanip>
#include <algorithm>
using namespace std;

Stadium::Stadium()
    : stadiumId(0), name("KPFL Ground"), location("Kingston"), capacity(5000),
      fieldCondition("Good"), ticketPrice(1000.0), ticketsSold(0) {}

Stadium::Stadium(int id, const std::string& stadiumName, const std::string& stadiumLocation,
                 int maxCapacity, const std::string& condition, double price)
    : ticketsSold(0) {
    setStadiumId(id);
    setName(stadiumName);
    setLocation(stadiumLocation);
    setCapacity(maxCapacity);
    setFieldCondition(condition);
    setTicketPrice(price);
}

Stadium::Stadium(const Stadium& other)
    : stadiumId(other.stadiumId), name(other.name), location(other.location),
      capacity(other.capacity), fieldCondition(other.fieldCondition),
      ticketPrice(other.ticketPrice), ticketsSold(other.ticketsSold),
      assignedTeamIds(other.assignedTeamIds),
      practiceApprovedTeamIds(other.practiceApprovedTeamIds) {}

int Stadium::getStadiumId() const {
    return stadiumId;
}

std::string Stadium::getName() const {
    return name;
}

std::string Stadium::getLocation() const {
    return location;
}

int Stadium::getCapacity() const {
    return capacity;
}

std::string Stadium::getFieldCondition() const {
    return fieldCondition;
}

double Stadium::getTicketPrice() const {
    return ticketPrice;
}

int Stadium::getTicketsSold() const {
    return ticketsSold;
}

int Stadium::getSeatsRemaining() const {
    return capacity - ticketsSold;
}

const std::vector<int>& Stadium::getAssignedTeamIds() const {
    return assignedTeamIds;
}

const std::vector<int>& Stadium::getPracticeApprovedTeamIds() const {
    return practiceApprovedTeamIds;
}

void Stadium::setStadiumId(int id) {
    if (id < 0) {
        throw InvalidDataException("Stadium ID cannot be negative.");
    }
    stadiumId = id;
}

void Stadium::setName(const std::string& stadiumName) {
    if (stadiumName.empty()) {
        throw InvalidDataException("Stadium name cannot be empty.");
    }
    name = stadiumName;
}

void Stadium::setLocation(const std::string& stadiumLocation) {
    if (stadiumLocation.empty()) {
        throw InvalidDataException("Stadium location cannot be empty.");
    }
    location = stadiumLocation;
}

void Stadium::setCapacity(int maxCapacity) {
    if (maxCapacity <= 0) {
        throw InvalidDataException("Stadium capacity must be greater than zero. Provided: " + FileManager::toText(maxCapacity));
    }
    capacity = maxCapacity;
}

void Stadium::setFieldCondition(const std::string& condition) {
    if (condition.empty()) {
        throw InvalidDataException("Field condition cannot be empty.");
    }
    fieldCondition = condition;
}

void Stadium::setTicketPrice(double price) {
    if (price < 0.0) {
        throw NegativeValueException("Ticket price cannot be negative. Provided: " + FileManager::toText(price));
    }
    ticketPrice = price;
}

void Stadium::setTicketsSold(int sold) {
    if (sold < 0) {
        throw NegativeValueException("Tickets sold cannot be negative.");
    }
    if (sold > capacity) {
        throw CapacityExceededException("Tickets sold (" + FileManager::toText(sold) +
                                         ") exceeds stadium capacity (" + FileManager::toText(capacity) + ").");
    }
    ticketsSold = sold;
}

void Stadium::sellTickets(int quantity) {
    if (quantity <= 0) {
        throw NegativeValueException("Ticket purchase quantity must be positive. Provided: " + FileManager::toText(quantity));
    }
    if (ticketsSold + quantity > capacity) {
        throw CapacityExceededException("Cannot sell " + FileManager::toText(quantity) + " tickets. Only " +
                                         FileManager::toText(getSeatsRemaining()) + " seats available in " + name + " (Capacity: " +
                                         FileManager::toText(capacity) + ").");
    }
    ticketsSold += quantity;
}

void Stadium::resetTicketsSold() {
    ticketsSold = 0;
}

bool Stadium::requestPracticePermission(int teamId) {
    if (std::find(practiceApprovedTeamIds.begin(), practiceApprovedTeamIds.end(), teamId) != practiceApprovedTeamIds.end()) {
        return true; // Already approved
    }
    practiceApprovedTeamIds.push_back(teamId);
    return true;
}

bool Stadium::hasPracticePermission(int teamId) const {
    return std::find(practiceApprovedTeamIds.begin(), practiceApprovedTeamIds.end(), teamId) != practiceApprovedTeamIds.end();
}

void Stadium::assignTeam(int teamId) {
    if (std::find(assignedTeamIds.begin(), assignedTeamIds.end(), teamId) == assignedTeamIds.end()) {
        assignedTeamIds.push_back(teamId);
    }
}

void Stadium::clearAssignedTeams() {
    assignedTeamIds.clear();
}

void Stadium::displayInformation() const {
    std::cout << "[Stadium #" << stadiumId << "] " << std::left << std::setw(22) << name
              << " | Loc: " << std::setw(15) << location
              << " | Cap: " << std::setw(6) << capacity
              << " | Cond: " << std::setw(10) << fieldCondition
              << " | Base Price: $" << std::fixed << std::setprecision(2) << ticketPrice
              << " | Sold: " << ticketsSold << "/" << capacity
              << " (Left: " << getSeatsRemaining() << ")" << std::endl;
}

std::string Stadium::toRecord() const {
    std::vector<std::string> fields;
    fields.push_back(FileManager::toText(stadiumId));
    fields.push_back(name);
    fields.push_back(location);
    fields.push_back(FileManager::toText(capacity));
    fields.push_back(fieldCondition);
    fields.push_back(FileManager::toText(ticketPrice));
    fields.push_back(FileManager::toText(ticketsSold));
    return FileManager::joinFields(fields);
}

void Stadium::fromRecord(const std::string& record) {
    std::vector<std::string> fields = FileManager::splitFields(record);
    if (fields.size() < 7) {
        throw FileException("Stadium record requires 7 fields: " + record);
    }
    setStadiumId(FileManager::toInt(fields[0]));
    setName(fields[1]);
    setLocation(fields[2]);
    setCapacity(FileManager::toInt(fields[3]));
    setFieldCondition(fields[4]);
    setTicketPrice(FileManager::toDouble(fields[5]));
    setTicketsSold(FileManager::toInt(fields[6]));
}
