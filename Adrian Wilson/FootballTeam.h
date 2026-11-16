//Football League Header File
#ifndef FOOTBALLLEAGUE_H
#define FOOTBALLLEAGUE_H

#pragma once
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

class FootballLeague {
private:
    std::string leagueName;
    int season;

public:
    FootballLeague(std::string name, int year);
    std::string getLeagueName();
    int getSeason();
    std::vector<std::string> readData(std::string filename);
    void displayInformation();
};

#endif
  