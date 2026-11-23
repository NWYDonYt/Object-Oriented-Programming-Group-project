#ifndef FIXTURE_H
#define FIXTURE_H

#pragma once
#include <string>
#include <vector>
#include "Storable.h"
#include "FootballTeam.h"
#include "Stadium.h"
#include "MatchOfficial.h"
#include "MatchResult.h"

class Fixture {
    private:
        std::string date;
        std::string time;
        std::string status;
    public:
        //Default constructor
        Fixture(){ 
            date = "";
            time = "";
            status = "";
        };
        //Parameterized constructor
        Fixture(std::string date, std::string time, std::string status)
        {
            this->date = date;
            this->time = time;
            this->status = status;
        };
        // Copy constructor
        Fixture(const Fixture& F)
        {
            this->date = F.date;
            this->time = F.time;
            this->status = F.status;
        };
        
        //Mutators
        void setDate(std::string date);
        void setTime(std::string time);
        void setStatus(std::string status);

        //Accessors
        std::string getDate();
        std::string getTime();
        std::string getStatus();
};

#endif // FIXTURE_H;