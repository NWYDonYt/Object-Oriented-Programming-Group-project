#ifndef LEAGUECOMMISSIONER_H
#define LEAGUECOMMISSIONER_H

#include "Person.h"
#include <string>

class FootballTeam;
class Stadium;

class LeagueCommissioner : public Person {
private:
    std::string officeLocation;
    std::string badgeNumber;
    int yearsInService;

public:
    LeagueCommissioner();
    LeagueCommissioner(int personId, const std::string& personName, int personAge, const std::string& personGender,
                       const std::string& office = "KPFL Headquarters, Kingston",
                       const std::string& badge = "COMM-01", int years = 5);

    // Accessors
    std::string getOfficeLocation() const;
    std::string getBadgeNumber() const;
    int getYearsInService() const;

    // Mutators with validation
    void setOfficeLocation(const std::string& office);
    void setBadgeNumber(const std::string& badge);
    void setYearsInService(int years);

    // League Coordination Responsibilities
    bool approveTeamRegistration(FootballTeam& team);
    bool inspectStadium(Stadium& stadium) const;

    // Polymorphic display
    virtual void displayInformation() const override;

    // Storable interface methods
    virtual std::string toRecord() const override;
    virtual void fromRecord(const std::string& record) override;
};

#endif // LEAGUECOMMISSIONER_H
