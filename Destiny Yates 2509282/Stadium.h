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
<<<<<<< HEAD
        // Default constructor
        Stadium(){
            stadiumId = 0;
            name = "";
            location = "";
            capacity = 0;
            fieldCondition = "";
            ticketPrice = 0.0;
            ticketsSold = 0;
            occupancy = 0;
        };

        // Parameterized constructor
        Stadium(string name, int capacity)
        {
            this->name = name;
            this->capacity = capacity;
        };
        //Copy constructor
=======
        Stadium();
        Stadium(string name, int occupancy );
>>>>>>> d2780510fcc6e9cb8267706ccc94629a5491725d
        Stadium(const Stadium& S);
        {
            this->stadiumId = S.stadiumId;
            this->name = S.name;
            this->location = S.location;
            this->capacity = S.capacity;
            this->fieldCondition = S.fieldCondition;
            this->ticketPrice = S.ticketPrice;
            this->ticketsSold = S.ticketsSold;
            this->occupancy = S.occupancy;
        };

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