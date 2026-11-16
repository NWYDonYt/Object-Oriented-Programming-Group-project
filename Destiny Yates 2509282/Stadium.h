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
        string Location;
        int capacity;
        string fieldcondition;
        double ticketprice;
        int ticketsSold;

    public:
        Stadium();
        Stadium(string name, int capacity);
        Stadium(const Stadium& S);
        void sellTickets(int ticketsSold);
};

#endif // STADIUM_H