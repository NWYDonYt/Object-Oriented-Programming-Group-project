#ifndef STADIUM_H
#define STADIUM_H

<<<<<<< HEAD
using namespace std;
#include <string>
#include "Storable.h"
#pragma once
=======
#pragma once
#include <string>
#include "Storable.h"
using namespace std;
>>>>>>> f3472d4f1e3ffc30080712529e7bf90f5528766c

class Stadium {
    private:
        int stadiumId;
        string name;
        string location;
        int capacity;
        string fieldCondition; //Excellent, Good, Poor
        double ticketPrice;
        int ticketsSold;
        int occupancy;

    public:
        Stadium();
        Stadium(string name, int capacity);
        Stadium(const Stadium& S);
        void sellTickets(int ticketsSold);

        //Mutators
        void setStadiumId(int stadiumId);
        void setName(string name);
        void setLocation(string location);
        void setCapacity(int capacity);
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