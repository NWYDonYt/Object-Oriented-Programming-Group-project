#include "Ticket.h"
#include "Exceptions.h"
#include "FileManager.h"
#include <iostream>
#include <iomanip>
using namespace std;

Ticket::Ticket()
    : ticketId(0), fixtureId(0), category("Bleachers"), price(500.0), isSold(false), spectatorId(0) {}

Ticket::Ticket(int id, int fixId, const string& cat, double ticketPrice, bool sold, int specId) {
    setTicketId(id);
    setFixtureId(fixId);
    std::string categoryCopy = cat;
    setCategory(categoryCopy);
    setPrice(ticketPrice);
    isSold = sold;
    spectatorId = specId;
}

Ticket::Ticket(const Ticket& other)
    : ticketId(other.ticketId), fixtureId(other.fixtureId), category(other.category),
      price(other.price), isSold(other.isSold), spectatorId(other.spectatorId) {}

int Ticket::getTicketId() const {
    return ticketId;
}
int Ticket::getFixtureId() const {
    return fixtureId;
}
string Ticket::getCategory() const {
    return category;
}
double Ticket::getPrice() const {
    return price;
}
bool Ticket::getIsSold() const {
    return isSold;
}
int Ticket::getSpectatorId() const {
    return spectatorId;
}
double Ticket::calculateTax() const {
    return price * TICKET_GCT_RATE;
}
double Ticket::calculateTotalPrice() const {
    return price + calculateTax();
}
void Ticket::setTicketId(int id) {
    if (id < 0) {
        throw InvalidDataException("Ticket ID cannot be negative.");
    }
    ticketId = id;
}
void Ticket::setFixtureId(int fixId) {
    if (fixId < 0) {
        throw InvalidDataException("Fixture ID cannot be negative.");
    }
    fixtureId = fixId;
}
void Ticket::setCategory(std::string& cat) {
    if (cat.empty()) {
        throw InvalidDataException("Ticket category cannot be empty.");
    }
    category = cat;
}
void Ticket::setPrice(double ticketPrice) {
    if (ticketPrice < 0.0) {
        throw NegativeValueException("Ticket price cannot be negative. Provided: " + FileManager::toText(ticketPrice));
    }
    price = ticketPrice;
}
void Ticket::markAsSold(int specId) {
    if (isSold) {
        throw InvalidDataException("Ticket #" + FileManager::toText(ticketId) + " is already sold.");
    }
    isSold = true;
    spectatorId = specId;
}
void Ticket::resetSold() {
    isSold = false;
    spectatorId = 0;
}
void Ticket::displayTicketDetails() {
    cout << "[Ticket #" << ticketId << "] Fixture: " << fixtureId
              << " | Cat: " << left << setw(11) << category
              << " | Base: $" << fixed << setprecision(2) << price
              << " | Total (incl 15% GCT): $" << calculateTotalPrice()
              << " | Status: " << (isSold ? "SOLD (Spectator #" + FileManager::toText(spectatorId) + ")" : "AVAILABLE")
              << endl;
}

string Ticket::toRecord() const {
    vector<string> fields;
    fields.push_back(FileManager::toText(ticketId));
    fields.push_back(FileManager::toText(fixtureId));
    fields.push_back(category);
    fields.push_back(FileManager::toText(price));
    fields.push_back(isSold ? "1" : "0");
    fields.push_back(FileManager::toText(spectatorId));
    return FileManager::joinFields(fields);
}

void Ticket::fromRecord(const string& record) {
    vector<string> fields = FileManager::splitFields(record);
    if (fields.size() < 6) {
        throw FileException("Ticket record requires 6 fields: " + record);
    }

    setTicketId(FileManager::toInt(fields[0]));
    setFixtureId(FileManager::toInt(fields[1]));
    setCategory(fields[2]);
    setPrice(FileManager::toDouble(fields[3]));

    isSold = (fields[4] == "1" || fields[4] == "true");
    spectatorId = FileManager::toInt(fields[5]);
}
