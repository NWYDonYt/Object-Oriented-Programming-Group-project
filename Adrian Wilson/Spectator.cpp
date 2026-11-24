// Spectator Header File
#ifndef SPECTATOR_H
#define SPECTATOR_H

#include <iostream>
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

    int getTicketsBought() {
        return ticketsBought;
    }

    void addTicket() {
        ticketsBought++;
    }

    void displayInformation() {
        cout << "Tickets Bought: " << ticketsBought << endl;
    }
};

#endif