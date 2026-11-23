#ifndef STADIUM_H
#define STADIUM_H

#pragma once
#include <string>
#include "Storable.h"
using namespace std;

class Stadium {
    private:
        int stadiumId;
        string name;
        string location;
        int occupancy;
        string fieldCondition;
        double ticketPrice;
        int ticketsSold;

    public:
        Stadium()
        {
            stadiumId = 0;
            name = "";
            location = "";
            occupancy = 0;
            fieldCondition = "";
            ticketPrice = 0.0;
            ticketsSold = 0;
        };
        Stadium(string name, int ouccupancy, string location, string fieldCondition, double ticketPrice)
        {
            this->name = name;
            this->occupancy = ouccupancy;
            this->location = location;
            this->fieldCondition = fieldCondition;
            this->ticketPrice = ticketPrice;
        };
        Stadium(const Stadium& S){
            this->stadiumId = S.stadiumId;
            this->name = S.name;
            this->location = S.location;
            this->occupancy = S.occupancy;
            this->fieldCondition = S.fieldCondition;
            this->ticketPrice = S.ticketPrice;
            this->ticketsSold = S.ticketsSold;
        };
        void sellTickets(int ticketsSold){
            this->ticketsSold += ticketsSold;
        };
};

#endif // STADIUM_H