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
        string fieldCondition;
        double ticketPrice;
        int ticketsSold;
        int occupancy;

    public:
        Stadium();
        Stadium(string name, int capacity);
        Stadium(const Stadium& S);
        void sellTickets(int ticketsSold);
};

#endif // STADIUM_H