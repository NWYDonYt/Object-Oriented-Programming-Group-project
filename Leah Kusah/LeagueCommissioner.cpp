//League Commissioner Source File
#include "FootballLeague.h"
#include "LeagueCommissioner.h"
#include <iostream>

using namespace std;

LeagueCommissioner::LeagueCommissioner(std::string name, FootballLeague* footballLeague)
{
    commissionerName = name;
    league = footballLeague;
}

void LeagueCommissioner::displayInformation() const
{
    cout << "\nLEAGUE COMMISSIONER\n";
    cout << "Name: " << commissionerName << endl;
    cout << "League: " << league->getLeagueName() << endl;
}

void LeagueCommissioner::manageLeague() const
{
    cout << commissionerName << " is managing "
         << league->getLeagueName() << endl;
}