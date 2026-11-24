#ifndef FOOTBALLLEAGUE_H
#define FOOTBALLLEAGUE_H

#include <string>
#include <vector>
#include "FootballTeam.h"
#include "Stadium.h"
#include "MatchOfficial.h"
#include "Fixture.h"
#include "MatchResult.h"
#include "Spectator.h"
#include "Ticket.h"
#include "StadiumShop.h"
#include "LeagueCommissioner.h"
#include "FileManager.h"

class FootballLeague {
private:
    std::string leagueName;
    int season;

    std::vector<FootballTeam> teams;
    std::vector<Stadium> stadiums;
    std::vector<Fixture> fixtures;
    std::vector<MatchOfficial> officials;
    std::vector<Spectator> spectators;
    std::vector<Ticket> tickets;

    StadiumShop shop;
    LeagueCommissioner* commissioner;
    FileManager fileManager;

public:
    FootballLeague(const std::string& name = "Kingston Premier Football League",
                   int year = 2026,
                   const std::string& dataDirectory = "Data");
    ~FootballLeague();

    // Prevent accidental copying
    FootballLeague(const FootballLeague&) = delete;
    FootballLeague& operator=(const FootballLeague&) = delete;

    // League basic properties
    std::string getLeagueName() const;
    int getSeason() const;
    void setLeagueName(const std::string& name);
    void setSeason(int year);
    void displayLeagueBanner() const;

    // Commissioner
    LeagueCommissioner* getCommissioner();
    const LeagueCommissioner* getCommissioner() const;

    // Team Operations
    void registerTeam(const FootballTeam& team);
    bool updateTeam(const FootballTeam& team);
    FootballTeam* findTeamById(int teamId);
    const FootballTeam* findTeamById(int teamId) const;
    FootballTeam* findTeamByName(const std::string& name);
    const FootballTeam* findTeamByName(const std::string& name) const;
    void displayAllTeams() const;
    void approveTeamRegistration(int teamId);
    void setTeamStatus(int teamId, const std::string& newStatus);
    const std::vector<FootballTeam>& getTeams() const;

    // Team Personnel Operations
    void addPlayerToTeam(int teamId, const Player& player);
    void updatePlayerInTeam(int teamId, const Player& player);
    void removePlayerFromTeam(int teamId, int playerId);
    Player* findPlayerAcrossLeague(int playerId, int& outTeamId);

    void addCoachToTeam(int teamId, const Coach& coach);
    void updateCoachInTeam(int teamId, const Coach& coach);
    void removeCoachFromTeam(int teamId, int coachId);
    Coach* findCoachAcrossLeague(int coachId, int& outTeamId);

    // Stadium Operations
    void registerStadium(const Stadium& stadium);
    Stadium* findStadiumById(int stadiumId);
    const Stadium* findStadiumById(int stadiumId) const;
    void updateStadiumCondition(int stadiumId, const std::string& condition);
    void displayAllStadiums() const;
    bool requestPracticePermission(int teamId, int stadiumId);
    const std::vector<Stadium>& getStadiums() const;

    // Match Official Operations
    void registerOfficial(const MatchOfficial& official);
    MatchOfficial* findOfficialById(int officialId);
    const MatchOfficial* findOfficialById(int officialId) const;
    void displayAllOfficials() const;
    const std::vector<MatchOfficial>& getOfficials() const;

    // Fixture Operations
    // Enforces:
    // Rule 1: An unregistered or suspended team cannot be assigned to a fixture
    // Rule 2: A team cannot participate in two fixtures scheduled for the same day and time
    // Rule: Stadium cannot host two fixtures on the same day and time
    int createFixture(int homeTeamId, int awayTeamId, int stadiumId,
                      const std::string& date, const std::string& time);
    Fixture* findFixtureById(int fixtureId);
    const Fixture* findFixtureById(int fixtureId) const;
    void displayAllFixtures() const;
    const std::vector<Fixture>& getFixtures() const;

    // Official Assignment
    // Enforces Rule 3: A match official cannot be assigned to conflicting fixtures
    void assignOfficialToFixture(int fixtureId, int officialId);

    // Match Results & Standings
    // Enforces Rule 5: Match scores cannot be negative
    // Enforces Rule 8: A fixture cannot be completed until a valid result has been recorded
    void recordMatchResult(int fixtureId, int homeScore, int awayScore);
    void displayStandings() const;
    void recomputeStandingsFromResults();

    // Ticketing Operations
    // Enforces Rule 4: Ticket sales cannot exceed stadium seating capacity
    // Enforces Rule 7: Transaction cannot be completed when payment is insufficient
    std::string sellTicket(int fixtureId, const std::string& category, int quantity,
                           int spectatorId, double paymentAmount,
                           double& outSubtotal, double& outTax, double& outTotal, double& outChange);
    int getSeatsRemainingForFixture(int fixtureId) const;
    void displayTickets() const;
    const std::vector<Ticket>& getTickets() const;

    // Spectator Operations
    void registerSpectator(const Spectator& spectator);
    Spectator* findSpectatorById(int spectatorId);
    const Spectator* findSpectatorById(int spectatorId) const;
    void displayAllSpectators() const;
    const std::vector<Spectator>& getSpectators() const;

    // Stadium Shop Operations
    StadiumShop& getShop();
    const StadiumShop& getShop() const;
    void addProductToShop(Product* product);
    void restockShopProduct(int productId, int quantity);
    void displayShopInventory() const;
    std::string processShopSale(int productId, int quantity, double paymentAmount,
                                double& outSubtotal, double& outTax, double& outTotal, double& outChange);

    // Persistence Operations
    void saveAllData();
    void loadAllData();

    // Management Reports (Requirement 11)
    void generateStandingsAndTopScorersReport() const;
    void generateTicketSalesAndAttendanceReport() const;
    void generateShopInventoryAndFinancialReport() const;
    void generateClubSquadsAndPersonnelReport() const;
    void generateMatchScheduleAndOfficialsReport() const;
};

#endif // FOOTBALLLEAGUE_H
