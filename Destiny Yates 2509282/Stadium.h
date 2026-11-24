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
        // Default constructor
        Stadium(){
            stadiumId = 0;
            name = "";
            location = "";
            fieldCondition = "";
            ticketPrice = 0.0;
            ticketsSold = 0;
            occupancy = 0;
        };

        // Parameterized constructor
        Stadium(string name, int occupancy)
        {
            this->name = name;
            this->occupancy = occupancy;
        };
        //Copy constructor
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
        void sellTickets(int ticketsSold){
            if (ticketsSold + ticketsSold > occupancy) {
                throw std::runtime_error("Cannot sell more tickets than the stadium's capacity.");
            }
            this->ticketsSold += ticketsSold;
        };

        //Mutators
        void setStadiumId(int stadiumId){
            this->stadiumId = stadiumId;
        };
        void setName(string name){
            this->name = name;
        };
        void setLocation(string location){
            this->location = location;
        };
        void setFieldCondition(string fieldCondition){
            this->fieldCondition = fieldCondition;
        };
        void setTicketPrice(double ticketPrice){
            this->ticketPrice = ticketPrice;
        };
        void setTicketsSold(int ticketsSold){
            this->ticketsSold = ticketsSold;
        };
        void setOccupancy(int occupancy){
            this->occupancy = occupancy;
        };

        //Accessors
        int getStadiumId(){
            return stadiumId;
        };
        string getName(){
            return name;
        };
        string getLocation(){
            return location;
        };
        int getCapacity(){
            return occupancy;
        };
        string getFieldCondition(){
            return fieldCondition;
        };
        double getTicketPrice(){
            return ticketPrice;
        };
        int getTicketsSold(){
            return ticketsSold;
        };
        int getOccupancy(){
            return occupancy;
        };

        //ticket sales cannot exceed capacity of stadium
        void TicketsSold(int quantity){
            if (ticketsSold + quantity > occupancy) {
                throw std::runtime_error("Cannot sell more tickets than the stadium's capacity.");
            }
            ticketsSold += quantity;
        };

        
};

#endif // STADIUM_H