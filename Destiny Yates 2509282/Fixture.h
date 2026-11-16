#ifndef FIXTURE_H
#define FIXTURE_H

<<<<<<< HEAD
#include <string>
=======
#pragma once
#include <string>
#include <vector>
#include "Storable.h"
#include "FootballTeam.h"
#include "Stadium.h"
#include "MatchOfficial.h"
#include "MatchResult.h"
>>>>>>> efdb78d414269764ed6398367a007978d9db22af

class Fixture {
    private:
        std::string date;
        std::string time;
        std::string status;
    public:
        Fixture();
        Fixture(std::string date, std::string time, std::string status);
        Fixture(const Fixture& F);
        void setDate(std::string date);
        void setTime(std::string time);
        void setStatus(std::string status);
        std::string getDate();
        std::string getTime();
        std::string getStatus();
};

#endif // FIXTURE_H