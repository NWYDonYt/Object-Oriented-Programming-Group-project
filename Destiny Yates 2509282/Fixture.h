#ifndef FIXTURE_H
#define FIXTURE_H

#pragma once
#include <string>
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
        void setDate(std::string date){
            this->date = date;
        };
        void setTime(std::string time){
            this->time = time;
        };
        void setStatus(std::string status){
            this->status = status;
        };

        //Accessors
        std::string getDate(){
            return date;
        };
        std::string getTime(){
            return time;
        };
        std::string getStatus(){
            return status;
        };
};

#endif // FIXTURE_H;