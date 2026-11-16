//League Commissioner Header File
#ifndef LEAGUECOMMISSIONER_H
#define LEAGUECOMMISSIONER_H
#pragma once
#include "Person.h"
#include "FootballLeague.h"
class LeagueCommissioner {
private:
    std::string commissionerName;
    FootballLeague* league;

public:
    LeagueCommissioner(std::string name, FootballLeague* footballLeague);

    void displayInformation() const;
    void manageLeague() const;
};

#endif