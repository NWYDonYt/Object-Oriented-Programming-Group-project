#ifndef STADIUM_H
#define STADIUM_H

class Stadium {
    private:
        int stadiumId;
        string name;
        string location;
        int capacity;
        string fieldCondition;
        double ticketPrice;
        int ticketsSold;

    public:
        Stadium();
        Stadium(string name, int capacity);
        Stadium(const Stadium& S);
        void sellTickets(int ticketsSold);
};

#endif // STADIUM_H