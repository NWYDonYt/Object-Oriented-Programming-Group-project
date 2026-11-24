// Football League Header File
#ifndef FOOTBALLLEAGUE_H
#define FOOTBALLLEAGUE_H

#include <iostream>
#include <string>
#include <vector>

#include "FootballTeam.h"
#include "Stadium.h"
#include "MatchOfficial.h"
#include "Fixture.h"
#include "Spectator.h"
#include "Ticket.h"
#include "StadiumShop.h"
#include "LeagueCommissioner.h"

using namespace std;

class FootballLeague {
private:
    string leagueName;
    int season;

public:
    // Constructor
    FootballLeague(string name, int year) {
        leagueName = name;
        season = year;
    }

    // Getter functions
    string getLeagueName() const {
        return leagueName;
    }

    int getSeason() const {
        return season;
    }

    // Read data from a file
    vector<string> readData(string filename) const;

    // Display league information
    void displayInformation() const;
};

#endif
  