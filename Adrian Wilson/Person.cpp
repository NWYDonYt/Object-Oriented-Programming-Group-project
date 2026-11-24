// Spectator Header File
#ifndef SPECTATOR_H
#define SPECTATOR_H

#include <iostream>
#include "Person.h"

using namespace std;

class Spectator {
private:
    int ticketsBought;

public:
    Spectator() {
        ticketsBought = 0;
    }

    Spectator(int tickets) {
        ticketsBought = tickets;
    }

    int getTicketsBought() const {
        return ticketsBought;
    }

    void addTicket() {
        ticketsBought++;
    }

    void displayInformation() const {
        cout << "Tickets Bought: " << ticketsBought << endl;
    }
};

#endif