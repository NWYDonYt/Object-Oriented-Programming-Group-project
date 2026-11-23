#include "MatchOfficial.h"
#include "Validation.h"
#include <iostream>

using namespace std;

MatchOfficial::MatchOfficial(string role, string officialRank, bool isAvailable) {
    setOfficiatingRole(role);
    setRank(officialRank);
    available = isAvailable;
}

string MatchOfficial::getOfficiatingRole() const {
    return officiatingRole;
}

string MatchOfficial::getRank() const {
    return rank;
}

bool MatchOfficial::isAvailable() const {
    return available;
}

void MatchOfficial::setOfficiatingRole(string newRole) {
    requireText(newRole, "Officiating role");
    officiatingRole = newRole;
}

void MatchOfficial::setRank(string newRank) {
    requireText(newRank, "Rank");
    rank = newRank;
}

void MatchOfficial::setAvailable(bool isAvailable) {
    available = isAvailable;
}

void MatchOfficial::displayInformation() const {
    cout << "\nMATCH OFFICIAL\n";
    cout << "Role: " << officiatingRole << endl;
    cout << "Rank: " << rank << endl;
    cout << "Available: " << (available ? "Yes" : "No") << endl;
}
