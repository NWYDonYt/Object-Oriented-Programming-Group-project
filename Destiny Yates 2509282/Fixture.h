#ifndef FIXTURE_H
#define FIXTURE_H

#include <string>
#include <vector>
#include "Storable.h"
#include "MatchResult.h"

class Fixture : public Storable {
private:
    int fixtureId;
    int homeTeamId;
    int awayTeamId;
    int stadiumId;
    std::string date; // Format: YYYY-MM-DD
    std::string time; // Format: HH:MM
    std::string status; // "Scheduled", "Completed", "Postponed", "Cancelled"
    std::vector<int> assignedOfficialIds;
    MatchResult matchResult;
    int ticketsSold;

public:
    Fixture(){
        
    };
    Fixture(int id, int homeId, int awayId, int stadId,
            const std::string& fixDate, const std::string& fixTime,
            const std::string& fixStatus = "Scheduled");
    Fixture(const Fixture& other);

    // Accessors
    int getFixtureId() const;
    int getHomeTeamId() const;
    int getAwayTeamId() const;
    int getStadiumId() const;
    std::string getDate() const;
    std::string getTime() const;
    std::string getStatus() const;
    const std::vector<int>& getAssignedOfficialIds() const;
    const MatchResult& getMatchResult() const;
    MatchResult& getMatchResult();
    int getTicketsSold() const;

    // Mutators with validation
    void setFixtureId(int id);
    void setHomeTeamId(int homeId);
    void setAwayTeamId(int awayId);
    void setTeams(int homeId, int awayId);
    void setStadiumId(int stadId);
    void setDate(const std::string& fixDate);
    void setTime(const std::string& fixTime);
    void setStatus(const std::string& fixStatus);
    void setTicketsSold(int sold);
    void addTicketsSold(int count);

    // Official Assignment
    void assignOfficial(int officialId);
    bool removeOfficial(int officialId);
    bool hasOfficial(int officialId) const;
    void clearOfficials();

    // Result and Completion Operations
    void recordResult(int homeScore, int awayScore);
    // Rule: A fixture cannot be completed until a valid result has been recorded
    void completeFixture();

    // Display
    void displayInformation() const;

    // Storable interface methods
    virtual std::string toRecord() const override;
    virtual void fromRecord(const std::string& record) override;
};

#endif // FIXTURE_H
