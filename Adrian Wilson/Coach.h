

//Spectator Header File
#ifndef SPECTATOR_H
#define SPECTATOR_H
#pragma once
#include <string>
#include "Person.h"
// Step 1: the Spectator's own data only. Inheritance from Person comes next.
class Spectator {
private:
    int ticketsBought;

public:
    Spectator();
    Spectator(int tickets);

    int getTicketsBought() const;
    void addTicket();

    void displayInformation() const;
};

#endif
