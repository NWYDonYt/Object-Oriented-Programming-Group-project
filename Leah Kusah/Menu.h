#ifndef MENU_H
#define MENU_H

#include "FootballLeague.h"

class Menu {
private:
    FootballLeague& league;

    // Submenu displays and handlers
    void handleTeamAndPersonnel();
    void handleStadiumsAndOfficials();
    void handleFixturesAndResults();
    void handleTickets();
    void handleStadiumShop();
    void handleReports();

    // Input helper utilities
    static int readInt(const std::string& prompt);
    static double readDouble(const std::string& prompt);
    static std::string readString(const std::string& prompt);
    static void pause();

public:
    explicit Menu(FootballLeague& footballLeague);
    void run();
};

#endif // MENU_H
