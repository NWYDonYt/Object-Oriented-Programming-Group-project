#ifndef STADIUM_H
#define STADIUM_H

using namespace std;
#include <string>
#include "Storable.h"
#pragma once

class Stadium {
    private:
        int stadiumId;
        string name;
        string location;
    
        string fieldCondition;
        double ticketPrice;
        int ticketsSold;
        int occupancy;

    public:
        Stadium();
        Stadium(string name, int occupancy );
        Stadium(const Stadium& S);
        void sellTickets(int ticketsSold);

        //Mutators
        void setStadiumId(int stadiumId);
        void setName(string name);
        void setLocation(string location);
        void setFieldCondition(string fieldCondition);
        void setTicketPrice(double ticketPrice);
        void setTicketsSold(int ticketsSold);
        void setOccupancy(int occupancy);

        //Accessors
        int getStadiumId();
        string getName();
        string getLocation();
        int getCapacity();
        string getFieldCondition();
        double getTicketPrice();
        int getTicketsSold();
        int getOccupancy();


        //ticket sales cannot exceed capacity of stadium
        void TicketsSold(int quantity);

        
};

#endif // STADIUM_H