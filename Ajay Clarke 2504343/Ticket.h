#ifndef TICKET_H
#define TICKET_H

#include <string>
#include "Storable.h"

class Ticket : public Storable {
private:
    int ticketId;
    int fixtureId;
    std::string category; // "VIP", "Grandstand", "Bleachers"
    double price;
    bool isSold;
    int spectatorId;

public:
    static constexpr double TICKET_GCT_RATE = 0.15; // 15% GCT

    Ticket();
    Ticket(int id, int fixId, const std::string& cat, double ticketPrice, bool sold = false, int specId = 0);
    Ticket(const Ticket& other);

    // Accessors
    int getTicketId() const;
    int getFixtureId() const;
    std::string getCategory() const;
    double getPrice() const;
    bool getIsSold() const;
    int getSpectatorId() const;

    double calculateTax() const;
    double calculateTotalPrice() const;

    // Mutators with validation
    void setTicketId(int id);
    void setFixtureId(int fixId);
    void setCategory(const std::string& cat);
    void setPrice(double ticketPrice);
    void markAsSold(int specId);
    void resetSold();

    // Display
    void displayTicketDetails() const;

    // Storable interface methods
    virtual std::string toRecord() const override;
    virtual void fromRecord(const std::string& record) override;
};

#endif // TICKET_H
