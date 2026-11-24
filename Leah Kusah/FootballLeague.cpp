#include "FootballLeague.h"
#include "Exceptions.h"
#include <iostream>
#include <iomanip>
#include <sstream>
#include <algorithm>

FootballLeague::FootballLeague(const std::string& name, int year, const std::string& dataDirectory)
    : leagueName(name), season(year), fileManager(dataDirectory) {
    commissioner = new LeagueCommissioner(1, "Hon. Keith Wellington", 58, "Male",
                                          "KPFL Headquarters, Kingston", "COMM-01", 8);
}

FootballLeague::~FootballLeague() {
    delete commissioner;
}

std::string FootballLeague::getLeagueName() const {
    return leagueName;
}

int FootballLeague::getSeason() const {
    return season;
}

void FootballLeague::setLeagueName(const std::string& name) {
    if (name.empty()) {
        throw InvalidDataException("League name cannot be empty.");
    }
    leagueName = name;
}

void FootballLeague::setSeason(int year) {
    if (year < 1900 || year > 2100) {
        throw InvalidDataException("Invalid season year.");
    }
    season = year;
}

void FootballLeague::displayLeagueBanner() const {
    std::cout << "\n======================================================================\n";
    std::cout << "        " << leagueName << " (" << season << " SEASON)        \n";
    std::cout << "         Parish of Kingston, Jamaica - Premier Division        \n";
    std::cout << "======================================================================\n";
}

LeagueCommissioner* FootballLeague::getCommissioner() {
    return commissioner;
}

const LeagueCommissioner* FootballLeague::getCommissioner() const {
    return commissioner;
}

// ----------------- TEAM OPERATIONS -----------------

void FootballLeague::registerTeam(const FootballTeam& team) {
    if (findTeamById(team.getTeamId())) {
        throw InvalidDataException("Team with ID " + FileManager::toText(team.getTeamId()) + " is already registered.");
    }
    if (findTeamByName(team.getName())) {
        throw InvalidDataException("Team name '" + team.getName() + "' is already registered.");
    }
    teams.push_back(team);
}

bool FootballLeague::updateTeam(const FootballTeam& updatedTeam) {
    for (size_t i = 0; i < teams.size(); i++) {
        if (teams[i].getTeamId() == updatedTeam.getTeamId()) {
            teams[i].setName(updatedTeam.getName());
            teams[i].setParish(updatedTeam.getParish());
            teams[i].setRegistrationNumber(updatedTeam.getRegistrationNumber());
            teams[i].setLeagueStatus(updatedTeam.getLeagueStatus());
            return true;
        }
    }
    return false;
}

FootballTeam* FootballLeague::findTeamById(int teamId) {
    for (size_t i = 0; i < teams.size(); i++) {
        if (teams[i].getTeamId() == teamId) {
            return &teams[i];
        }
    }
    return nullptr;
}

const FootballTeam* FootballLeague::findTeamById(int teamId) const {
    for (size_t i = 0; i < teams.size(); i++) {
        if (teams[i].getTeamId() == teamId) {
            return &teams[i];
        }
    }
    return nullptr;
}

FootballTeam* FootballLeague::findTeamByName(const std::string& name) {
    for (size_t i = 0; i < teams.size(); i++) {
        if (teams[i].getName() == name) {
            return &teams[i];
        }
    }
    return nullptr;
}

const FootballTeam* FootballLeague::findTeamByName(const std::string& name) const {
    for (size_t i = 0; i < teams.size(); i++) {
        if (teams[i].getName() == name) {
            return &teams[i];
        }
    }
    return nullptr;
}

void FootballLeague::displayAllTeams() const {
    std::cout << "\n======================== KPFL TEAMS DIRECTORY ========================\n";
    if (teams.empty()) {
        std::cout << "No teams currently registered in the league.\n";
    } else {
        for (size_t i = 0; i < teams.size(); i++) {
            teams[i].displayInformation();
        }
    }
    std::cout << "======================================================================\n";
}

void FootballLeague::approveTeamRegistration(int teamId) {
    FootballTeam* t = findTeamById(teamId);
    if (!t) {
        throw TeamNotFoundException("Team ID " + FileManager::toText(teamId) + " not found.");
    }
    commissioner->approveTeamRegistration(*t);
}

void FootballLeague::setTeamStatus(int teamId, const std::string& newStatus) {
    FootballTeam* t = findTeamById(teamId);
    if (!t) {
        throw TeamNotFoundException("Team ID " + FileManager::toText(teamId) + " not found.");
    }
    t->setLeagueStatus(newStatus);
}

const std::vector<FootballTeam>& FootballLeague::getTeams() const {
    return teams;
}

// ----------------- PERSONNEL OPERATIONS -----------------

void FootballLeague::addPlayerToTeam(int teamId, const Player& player) {
    FootballTeam* t = findTeamById(teamId);
    if (!t) {
        throw TeamNotFoundException("Cannot add player: Team ID " + FileManager::toText(teamId) + " not found.");
    }
    // Check if player ID exists anywhere in league
    int dummyTeam;
    if (findPlayerAcrossLeague(player.getId(), dummyTeam)) {
        throw InvalidDataException("Player ID " + FileManager::toText(player.getId()) + " is already registered in team #" + FileManager::toText(dummyTeam));
    }
    t->addPlayer(player);
}

void FootballLeague::updatePlayerInTeam(int teamId, const Player& player) {
    FootballTeam* t = findTeamById(teamId);
    if (!t) {
        throw TeamNotFoundException("Team ID " + FileManager::toText(teamId) + " not found.");
    }
    if (!t->updatePlayer(player)) {
        throw PlayerNotFoundException("Player ID " + FileManager::toText(player.getId()) + " not found in team " + t->getName());
    }
}

void FootballLeague::removePlayerFromTeam(int teamId, int playerId) {
    FootballTeam* t = findTeamById(teamId);
    if (!t) {
        throw TeamNotFoundException("Team ID " + FileManager::toText(teamId) + " not found.");
    }
    if (!t->removePlayer(playerId)) {
        throw PlayerNotFoundException("Player ID " + FileManager::toText(playerId) + " not found in team " + t->getName());
    }
}

Player* FootballLeague::findPlayerAcrossLeague(int playerId, int& outTeamId) {
    for (size_t i = 0; i < teams.size(); i++) {
        Player* p = teams[i].findPlayer(playerId);
        if (p) {
            outTeamId = teams[i].getTeamId();
            return p;
        }
    }
    outTeamId = 0;
    return nullptr;
}

void FootballLeague::addCoachToTeam(int teamId, const Coach& coach) {
    FootballTeam* t = findTeamById(teamId);
    if (!t) {
        throw TeamNotFoundException("Cannot add coach: Team ID " + FileManager::toText(teamId) + " not found.");
    }
    int dummyTeam;
    if (findCoachAcrossLeague(coach.getId(), dummyTeam)) {
        throw InvalidDataException("Coach ID " + FileManager::toText(coach.getId()) + " is already registered in team #" + FileManager::toText(dummyTeam));
    }
    t->addCoach(coach);
}

void FootballLeague::updateCoachInTeam(int teamId, const Coach& coach) {
    FootballTeam* t = findTeamById(teamId);
    if (!t) {
        throw TeamNotFoundException("Team ID " + FileManager::toText(teamId) + " not found.");
    }
    if (!t->updateCoach(coach)) {
        throw CoachNotFoundException("Coach ID " + FileManager::toText(coach.getId()) + " not found in team " + t->getName());
    }
}

void FootballLeague::removeCoachFromTeam(int teamId, int coachId) {
    FootballTeam* t = findTeamById(teamId);
    if (!t) {
        throw TeamNotFoundException("Team ID " + FileManager::toText(teamId) + " not found.");
    }
    if (!t->removeCoach(coachId)) {
        throw CoachNotFoundException("Coach ID " + FileManager::toText(coachId) + " not found in team " + t->getName());
    }
}

Coach* FootballLeague::findCoachAcrossLeague(int coachId, int& outTeamId) {
    for (size_t i = 0; i < teams.size(); i++) {
        Coach* c = teams[i].findCoach(coachId);
        if (c) {
            outTeamId = teams[i].getTeamId();
            return c;
        }
    }
    outTeamId = 0;
    return nullptr;
}

// ----------------- STADIUM OPERATIONS -----------------

void FootballLeague::registerStadium(const Stadium& stadium) {
    if (findStadiumById(stadium.getStadiumId())) {
        throw InvalidDataException("Stadium ID " + FileManager::toText(stadium.getStadiumId()) + " is already registered.");
    }
    stadiums.push_back(stadium);
}

Stadium* FootballLeague::findStadiumById(int stadiumId) {
    for (size_t i = 0; i < stadiums.size(); i++) {
        if (stadiums[i].getStadiumId() == stadiumId) {
            return &stadiums[i];
        }
    }
    return nullptr;
}

const Stadium* FootballLeague::findStadiumById(int stadiumId) const {
    for (size_t i = 0; i < stadiums.size(); i++) {
        if (stadiums[i].getStadiumId() == stadiumId) {
            return &stadiums[i];
        }
    }
    return nullptr;
}

void FootballLeague::updateStadiumCondition(int stadiumId, const std::string& condition) {
    Stadium* s = findStadiumById(stadiumId);
    if (!s) {
        throw StadiumNotFoundException("Stadium ID " + FileManager::toText(stadiumId) + " not found.");
    }
    s->setFieldCondition(condition);
}

void FootballLeague::displayAllStadiums() const {
    std::cout << "\n======================= KPFL STADIUMS DIRECTORY =======================\n";
    if (stadiums.empty()) {
        std::cout << "No stadiums currently registered in the league.\n";
    } else {
        for (size_t i = 0; i < stadiums.size(); i++) {
            stadiums[i].displayInformation();
        }
    }
    std::cout << "=======================================================================\n";
}

bool FootballLeague::requestPracticePermission(int teamId, int stadiumId) {
    FootballTeam* t = findTeamById(teamId);
    if (!t) {
        throw TeamNotFoundException("Team ID " + FileManager::toText(teamId) + " not found.");
    }
    Stadium* s = findStadiumById(stadiumId);
    if (!s) {
        throw StadiumNotFoundException("Stadium ID " + FileManager::toText(stadiumId) + " not found.");
    }
    s->requestPracticePermission(teamId);
    std::cout << "[Practice Permission] Team '" << t->getName()
              << "' granted official practice access at " << s->getName() << ".\n";
    return true;
}

const std::vector<Stadium>& FootballLeague::getStadiums() const {
    return stadiums;
}

// ----------------- MATCH OFFICIAL OPERATIONS -----------------

void FootballLeague::registerOfficial(const MatchOfficial& official) {
    if (findOfficialById(official.getId())) {
        throw InvalidDataException("Official ID " + FileManager::toText(official.getId()) + " is already registered.");
    }
    officials.push_back(official);
}

MatchOfficial* FootballLeague::findOfficialById(int officialId) {
    for (size_t i = 0; i < officials.size(); i++) {
        if (officials[i].getId() == officialId) {
            return &officials[i];
        }
    }
    return nullptr;
}

const MatchOfficial* FootballLeague::findOfficialById(int officialId) const {
    for (size_t i = 0; i < officials.size(); i++) {
        if (officials[i].getId() == officialId) {
            return &officials[i];
        }
    }
    return nullptr;
}

void FootballLeague::displayAllOfficials() const {
    std::cout << "\n==================== KPFL MATCH OFFICIALS ROSTER ====================\n";
    if (officials.empty()) {
        std::cout << "No match officials currently registered.\n";
    } else {
        for (size_t i = 0; i < officials.size(); i++) {
            officials[i].displayInformation();
        }
    }
    std::cout << "=====================================================================\n";
}

const std::vector<MatchOfficial>& FootballLeague::getOfficials() const {
    return officials;
}

// ----------------- FIXTURE OPERATIONS -----------------

int FootballLeague::createFixture(int homeTeamId, int awayTeamId, int stadiumId,
                                  const std::string& date, const std::string& time) {
    FootballTeam* home = findTeamById(homeTeamId);
    if (!home) {
        throw TeamNotFoundException("Home team ID " + FileManager::toText(homeTeamId) + " not found.");
    }
    FootballTeam* away = findTeamById(awayTeamId);
    if (!away) {
        throw TeamNotFoundException("Away team ID " + FileManager::toText(awayTeamId) + " not found.");
    }
    if (homeTeamId == awayTeamId) {
        throw InvalidDataException("Home team and away team cannot be identical.");
    }

    // MANDATORY BUSINESS RULE 1: An unregistered or suspended team cannot be assigned to a fixture
    if (!home->isEligibleForFixture()) {
        throw TeamIneligibleException("Home team '" + home->getName() + "' is " + home->getLeagueStatus() +
                                      ". Unregistered or suspended teams cannot be scheduled for fixtures.");
    }
    if (!away->isEligibleForFixture()) {
        throw TeamIneligibleException("Away team '" + away->getName() + "' is " + away->getLeagueStatus() +
                                      ". Unregistered or suspended teams cannot be scheduled for fixtures.");
    }

    Stadium* s = findStadiumById(stadiumId);
    if (!s) {
        throw StadiumNotFoundException("Stadium ID " + FileManager::toText(stadiumId) + " not found.");
    }

    // MANDATORY BUSINESS RULE 2: A team cannot participate in two fixtures scheduled for the same day and time
    for (size_t i = 0; i < fixtures.size(); i++) {
        if (fixtures[i].getStatus() != "Cancelled" &&
            fixtures[i].getDate() == date && fixtures[i].getTime() == time) {
            if (fixtures[i].getHomeTeamId() == homeTeamId || fixtures[i].getAwayTeamId() == homeTeamId) {
                throw SchedulingConflictException("Team '" + home->getName() + "' is already scheduled for fixture #" +
                                                 FileManager::toText(fixtures[i].getFixtureId()) + " on " + date + " at " + time);
            }
            if (fixtures[i].getHomeTeamId() == awayTeamId || fixtures[i].getAwayTeamId() == awayTeamId) {
                throw SchedulingConflictException("Team '" + away->getName() + "' is already scheduled for fixture #" +
                                                 FileManager::toText(fixtures[i].getFixtureId()) + " on " + date + " at " + time);
            }
            if (fixtures[i].getStadiumId() == stadiumId) {
                throw SchedulingConflictException("Stadium '" + s->getName() + "' is already booked for fixture #" +
                                                 FileManager::toText(fixtures[i].getFixtureId()) + " on " + date + " at " + time);
            }
        }
    }

    int newFixtureId = 1;
    for (size_t i = 0; i < fixtures.size(); i++) {
        if (fixtures[i].getFixtureId() >= newFixtureId) {
            newFixtureId = fixtures[i].getFixtureId() + 1;
        }
    }

    Fixture fix(newFixtureId, homeTeamId, awayTeamId, stadiumId, date, time, "Scheduled");
    fixtures.push_back(fix);
    s->assignTeam(homeTeamId);
    s->assignTeam(awayTeamId);

    return newFixtureId;
}

Fixture* FootballLeague::findFixtureById(int fixtureId) {
    for (size_t i = 0; i < fixtures.size(); i++) {
        if (fixtures[i].getFixtureId() == fixtureId) {
            return &fixtures[i];
        }
    }
    return nullptr;
}

const Fixture* FootballLeague::findFixtureById(int fixtureId) const {
    for (size_t i = 0; i < fixtures.size(); i++) {
        if (fixtures[i].getFixtureId() == fixtureId) {
            return &fixtures[i];
        }
    }
    return nullptr;
}

void FootballLeague::displayAllFixtures() const {
    std::cout << "\n======================== KPFL FIXTURE SCHEDULE ========================\n";
    if (fixtures.empty()) {
        std::cout << "No fixtures currently scheduled.\n";
    } else {
        for (size_t i = 0; i < fixtures.size(); i++) {
            const Fixture& f = fixtures[i];
            const FootballTeam* h = findTeamById(f.getHomeTeamId());
            const FootballTeam* a = findTeamById(f.getAwayTeamId());
            const Stadium* s = findStadiumById(f.getStadiumId());

            std::string hName = h ? h->getName() : ("Team #" + FileManager::toText(f.getHomeTeamId()));
            std::string aName = a ? a->getName() : ("Team #" + FileManager::toText(f.getAwayTeamId()));
            std::string sName = s ? s->getName() : ("Stadium #" + FileManager::toText(f.getStadiumId()));

            std::cout << "[Fixture #" << f.getFixtureId() << "] "
                      << f.getDate() << " @ " << f.getTime() << "\n"
                      << "  Match:   " << hName << " vs " << aName << "\n"
                      << "  Venue:   " << sName << "\n"
                      << "  Status:  " << f.getStatus() << "\n"
                      << "  Tickets: " << f.getTicketsSold() << " sold\n";

            if (f.getMatchResult().getIsRecorded()) {
                std::cout << "  Score:   " << hName << " " << f.getMatchResult().getHomeScore()
                          << " - " << f.getMatchResult().getAwayScore() << " " << aName << "\n";
            }

            if (!f.getAssignedOfficialIds().empty()) {
                std::cout << "  Officials Assigned: ";
                for (size_t j = 0; j < f.getAssignedOfficialIds().size(); j++) {
                    const MatchOfficial* off = findOfficialById(f.getAssignedOfficialIds()[j]);
                    if (off) {
                        std::cout << off->getName() << " (" << off->getOfficiatingRole() << ")";
                    } else {
                        std::cout << "#" << f.getAssignedOfficialIds()[j];
                    }
                    if (j + 1 < f.getAssignedOfficialIds().size()) std::cout << ", ";
                }
                std::cout << "\n";
            }
            std::cout << "----------------------------------------------------------------------\n";
        }
    }
    std::cout << "======================================================================\n";
}

const std::vector<Fixture>& FootballLeague::getFixtures() const {
    return fixtures;
}

// ----------------- OFFICIAL ASSIGNMENT -----------------

void FootballLeague::assignOfficialToFixture(int fixtureId, int officialId) {
    Fixture* f = findFixtureById(fixtureId);
    if (!f) {
        throw FixtureNotFoundException("Fixture ID " + FileManager::toText(fixtureId) + " not found.");
    }
    MatchOfficial* off = findOfficialById(officialId);
    if (!off) {
        throw OfficialNotFoundException("Official ID " + FileManager::toText(officialId) + " not found.");
    }
    if (!off->isAvailable()) {
        throw InvalidDataException("Official " + off->getName() + " is marked as unavailable.");
    }

    // MANDATORY BUSINESS RULE 3: A match official cannot be assigned to conflicting fixtures
    for (size_t i = 0; i < fixtures.size(); i++) {
        if (fixtures[i].getFixtureId() != fixtureId &&
            fixtures[i].getStatus() != "Cancelled" &&
            fixtures[i].getDate() == f->getDate() &&
            fixtures[i].getTime() == f->getTime()) {
            if (fixtures[i].hasOfficial(officialId)) {
                throw SchedulingConflictException("Official '" + off->getName() + "' is already assigned to fixture #" +
                                                 FileManager::toText(fixtures[i].getFixtureId()) + " at the same date and time (" +
                                                 f->getDate() + " " + f->getTime() + ").");
            }
        }
    }

    f->assignOfficial(officialId);
    std::cout << "[Official Assigned] " << off->getName() << " (" << off->getOfficiatingRole()
              << ") successfully assigned to fixture #" << fixtureId << ".\n";
}

// ----------------- RESULTS & STANDINGS -----------------

void FootballLeague::recordMatchResult(int fixtureId, int homeScore, int awayScore) {
    Fixture* f = findFixtureById(fixtureId);
    if (!f) {
        throw FixtureNotFoundException("Fixture ID " + FileManager::toText(fixtureId) + " not found.");
    }
    // MANDATORY BUSINESS RULE 5: Match scores and quantities cannot be negative
    if (homeScore < 0 || awayScore < 0) {
        throw NegativeValueException("Match scores cannot be negative.");
    }

    FootballTeam* home = findTeamById(f->getHomeTeamId());
    FootballTeam* away = findTeamById(f->getAwayTeamId());
    if (!home || !away) {
        throw TeamNotFoundException("Associated team not found for fixture #" + FileManager::toText(fixtureId));
    }

    // Record the scores
    f->recordResult(homeScore, awayScore);

    // MANDATORY BUSINESS RULE 8: A fixture cannot be completed until a valid result has been recorded
    f->completeFixture();

    // Recompute standings across all completed fixtures
    recomputeStandingsFromResults();

    std::cout << "[Result Recorded] Fixture #" << fixtureId << ": "
              << home->getName() << " " << homeScore << " - "
              << awayScore << " " << away->getName()
              << ". League standings updated!\n";
}

void FootballLeague::recomputeStandingsFromResults() {
    // Reset all team stats
    for (size_t i = 0; i < teams.size(); i++) {
        teams[i].resetStats();
    }

    // Apply points system: win = 3, draw = 1, loss = 0
    for (size_t i = 0; i < fixtures.size(); i++) {
        if (fixtures[i].getStatus() == "Completed" && fixtures[i].getMatchResult().getIsRecorded()) {
            int hId = fixtures[i].getHomeTeamId();
            int aId = fixtures[i].getAwayTeamId();
            int hSc = fixtures[i].getMatchResult().getHomeScore();
            int aSc = fixtures[i].getMatchResult().getAwayScore();

            FootballTeam* h = findTeamById(hId);
            FootballTeam* a = findTeamById(aId);

            if (h && a) {
                h->recordMatchResult(hSc, aSc);
                a->recordMatchResult(aSc, hSc);
            }
        }
    }
}

void FootballLeague::displayStandings() const {
    std::vector<FootballTeam> sortedTeams = teams;

    // Sort by: Points DESC, Goal Difference DESC, Goals For DESC, Name ASC
    std::sort(sortedTeams.begin(), sortedTeams.end(), [](const FootballTeam& a, const FootballTeam& b) {
        if (a.getPoints() != b.getPoints()) return a.getPoints() > b.getPoints();
        if (a.getGoalDifference() != b.getGoalDifference()) return a.getGoalDifference() > b.getGoalDifference();
        if (a.getGoalsFor() != b.getGoalsFor()) return a.getGoalsFor() > b.getGoalsFor();
        return a.getName() < b.getName();
    });

    std::cout << "\n========================================================================================\n";
    std::cout << "                         KPFL OFFICIAL LEAGUE STANDINGS                                 \n";
    std::cout << "========================================================================================\n";
    std::cout << std::left << std::setw(4)  << "Pos"
              << std::setw(24) << "Club"
              << std::setw(5)  << "P"
              << std::setw(5)  << "W"
              << std::setw(5)  << "D"
              << std::setw(5)  << "L"
              << std::setw(6)  << "GF"
              << std::setw(6)  << "GA"
              << std::setw(6)  << "GD"
              << std::setw(6)  << "PTS"
              << std::setw(12) << "Status" << "\n";
    std::cout << "----------------------------------------------------------------------------------------\n";

    for (size_t i = 0; i < sortedTeams.size(); i++) {
        const FootballTeam& t = sortedTeams[i];
        std::cout << std::left << std::setw(4)  << (i + 1)
                  << std::setw(24) << t.getName()
                  << std::setw(5)  << t.getMatchesPlayed()
                  << std::setw(5)  << t.getWins()
                  << std::setw(5)  << t.getDraws()
                  << std::setw(5)  << t.getLosses()
                  << std::setw(6)  << t.getGoalsFor()
                  << std::setw(6)  << t.getGoalsAgainst()
                  << std::setw(6)  << t.getGoalDifference()
                  << std::setw(6)  << t.getPoints()
                  << std::setw(12) << t.getLeagueStatus() << "\n";
    }
    std::cout << "========================================================================================\n";
    std::cout << "Rules: Win = 3 Pts | Draw = 1 Pt | Loss = 0 Pts. Top 4 qualify for KPFL Playoffs.\n";
}

// ----------------- TICKETING OPERATIONS -----------------

std::string FootballLeague::sellTicket(int fixtureId, const std::string& category, int quantity,
                                       int spectatorId, double paymentAmount,
                                       double& outSubtotal, double& outTax, double& outTotal, double& outChange) {
    if (quantity <= 0) {
        throw NegativeValueException("Ticket purchase quantity must be positive. Provided: " + FileManager::toText(quantity));
    }
    if (paymentAmount < 0.0) {
        throw NegativeValueException("Payment amount cannot be negative.");
    }

    Fixture* fix = findFixtureById(fixtureId);
    if (!fix) {
        throw FixtureNotFoundException("Fixture ID " + FileManager::toText(fixtureId) + " not found.");
    }
    Stadium* stad = findStadiumById(fix->getStadiumId());
    if (!stad) {
        throw StadiumNotFoundException("Stadium ID " + FileManager::toText(fix->getStadiumId()) + " not found.");
    }
    Spectator* spec = findSpectatorById(spectatorId);
    if (!spec) {
        throw InvalidDataException("Spectator ID " + FileManager::toText(spectatorId) + " not found.");
    }

    // MANDATORY BUSINESS RULE 4: Ticket sales cannot exceed stadium seating capacity
    if (fix->getTicketsSold() + quantity > stad->getCapacity()) {
        throw CapacityExceededException("Cannot sell " + FileManager::toText(quantity) + " tickets. Only " +
                                         FileManager::toText(stad->getCapacity() - fix->getTicketsSold()) +
                                         " seats left in " + stad->getName() + " (Capacity: " +
                                         FileManager::toText(stad->getCapacity()) + ").");
    }

    // Determine category price multiplier
    double baseUnitPrice = stad->getTicketPrice();
    if (category == "VIP") {
        baseUnitPrice *= 1.6;
    } else if (category == "Grandstand") {
        baseUnitPrice *= 1.2;
    } else if (category == "Bleachers") {
        baseUnitPrice *= 0.8;
    }

    outSubtotal = baseUnitPrice * quantity;
    outTax = outSubtotal * Ticket::TICKET_GCT_RATE; // 15% GCT
    outTotal = outSubtotal + outTax;

    // MANDATORY BUSINESS RULE 7: A transaction cannot be completed when payment is insufficient
    if (paymentAmount < outTotal) {
        std::stringstream ss;
        ss << std::fixed << std::setprecision(2);
        ss << "Insufficient payment: $" << paymentAmount << " provided, but total charge is $"
           << outTotal << " (Short by $" << (outTotal - paymentAmount) << ").";
        throw InsufficientPaymentException(ss.str());
    }

    outChange = paymentAmount - outTotal;

    // Update state
    stad->sellTickets(quantity);
    fix->addTicketsSold(quantity);
    spec->addTickets(quantity);
    spec->addSpend(outTotal);

    // Create tickets in ledger
    int nextTicketId = 1;
    for (size_t i = 0; i < tickets.size(); i++) {
        if (tickets[i].getTicketId() >= nextTicketId) {
            nextTicketId = tickets[i].getTicketId() + 1;
        }
    }
    for (int i = 0; i < quantity; i++) {
        Ticket t(nextTicketId + i, fixtureId, category, baseUnitPrice, true, spectatorId);
        tickets.push_back(t);
    }

    // Generate receipt
    const FootballTeam* h = findTeamById(fix->getHomeTeamId());
    const FootballTeam* a = findTeamById(fix->getAwayTeamId());
    std::string hName = h ? h->getName() : "Home";
    std::string aName = a ? a->getName() : "Away";

    std::stringstream receipt;
    receipt << "\n=======================================================\n";
    receipt << "             KPFL MATCH-DAY TICKET RECEIPT             \n";
    receipt << "=======================================================\n";
    receipt << "Fixture:   #" << fixtureId << " - " << hName << " vs " << aName << "\n";
    receipt << "Date/Time: " << fix->getDate() << " @ " << fix->getTime() << "\n";
    receipt << "Venue:     " << stad->getName() << "\n";
    receipt << "Customer:  " << spec->getName() << " (ID #" << spec->getId() << ")\n";
    receipt << "Category:  " << category << " (Quantity: " << quantity << ")\n";
    receipt << "Unit Base: $" << std::fixed << std::setprecision(2) << baseUnitPrice << "\n";
    receipt << "-------------------------------------------------------\n";
    receipt << "Subtotal:  $" << outSubtotal << "\n";
    receipt << "15% GCT:   $" << outTax << "\n";
    receipt << "TOTAL:     $" << outTotal << "\n";
    receipt << "Paid:      $" << paymentAmount << "\n";
    receipt << "Change:    $" << outChange << "\n";
    receipt << "=======================================================\n";

    return receipt.str();
}

int FootballLeague::getSeatsRemainingForFixture(int fixtureId) const {
    const Fixture* fix = findFixtureById(fixtureId);
    if (!fix) {
        throw FixtureNotFoundException("Fixture ID " + FileManager::toText(fixtureId) + " not found.");
    }
    const Stadium* stad = findStadiumById(fix->getStadiumId());
    if (!stad) {
        throw StadiumNotFoundException("Stadium ID " + FileManager::toText(fix->getStadiumId()) + " not found.");
    }
    return stad->getCapacity() - fix->getTicketsSold();
}

void FootballLeague::displayTickets() const {
    std::cout << "\n======================= KPFL ISSUED TICKETS =======================\n";
    if (tickets.empty()) {
        std::cout << "No tickets issued yet.\n";
    } else {
        for (size_t i = 0; i < tickets.size(); i++) {
            tickets[i].displayTicketDetails();
        }
    }
    std::cout << "===================================================================\n";
}

const std::vector<Ticket>& FootballLeague::getTickets() const {
    return tickets;
}

// ----------------- SPECTATOR OPERATIONS -----------------

void FootballLeague::registerSpectator(const Spectator& spectator) {
    if (findSpectatorById(spectator.getId())) {
        throw InvalidDataException("Spectator ID " + FileManager::toText(spectator.getId()) + " is already registered.");
    }
    spectators.push_back(spectator);
}

Spectator* FootballLeague::findSpectatorById(int spectatorId) {
    for (size_t i = 0; i < spectators.size(); i++) {
        if (spectators[i].getId() == spectatorId) {
            return &spectators[i];
        }
    }
    return nullptr;
}

const Spectator* FootballLeague::findSpectatorById(int spectatorId) const {
    for (size_t i = 0; i < spectators.size(); i++) {
        if (spectators[i].getId() == spectatorId) {
            return &spectators[i];
        }
    }
    return nullptr;
}

void FootballLeague::displayAllSpectators() const {
    std::cout << "\n======================= REGISTERED SPECTATORS =======================\n";
    if (spectators.empty()) {
        std::cout << "No spectators registered yet.\n";
    } else {
        for (size_t i = 0; i < spectators.size(); i++) {
            spectators[i].displayInformation();
        }
    }
    std::cout << "=====================================================================\n";
}

const std::vector<Spectator>& FootballLeague::getSpectators() const {
    return spectators;
}

// ----------------- STADIUM SHOP OPERATIONS -----------------

StadiumShop& FootballLeague::getShop() {
    return shop;
}

const StadiumShop& FootballLeague::getShop() const {
    return shop;
}

void FootballLeague::addProductToShop(Product* product) {
    shop.addProduct(product);
}

void FootballLeague::restockShopProduct(int productId, int quantity) {
    shop.restock(productId, quantity);
}

void FootballLeague::displayShopInventory() const {
    shop.displayInventory();
}

std::string FootballLeague::processShopSale(int productId, int quantity, double paymentAmount,
                                            double& outSubtotal, double& outTax, double& outTotal, double& outChange) {
    return shop.completeSale(productId, quantity, paymentAmount, outSubtotal, outTax, outTotal, outChange);
}

// ----------------- PERSISTENCE OPERATIONS -----------------

void FootballLeague::saveAllData() {
    // 1. Teams
    std::vector<std::string> teamRecs;
    for (size_t i = 0; i < teams.size(); i++) {
        teamRecs.push_back(teams[i].toRecord());
    }
    fileManager.saveRecords("team.txt", teamRecs);

    // 2. Players
    std::vector<std::string> playerRecs;
    for (size_t i = 0; i < teams.size(); i++) {
        const std::vector<Player>& pls = teams[i].getPlayers();
        for (size_t j = 0; j < pls.size(); j++) {
            playerRecs.push_back(pls[j].toRecord());
        }
    }
    fileManager.saveRecords("players.txt", playerRecs);

    // 3. Coaches
    std::vector<std::string> coachRecs;
    for (size_t i = 0; i < teams.size(); i++) {
        const std::vector<Coach>& chs = teams[i].getCoaches();
        for (size_t j = 0; j < chs.size(); j++) {
            coachRecs.push_back(chs[j].toRecord());
        }
    }
    fileManager.saveRecords("coaches.txt", coachRecs);

    // 4. Stadiums
    std::vector<std::string> stadiumRecs;
    for (size_t i = 0; i < stadiums.size(); i++) {
        stadiumRecs.push_back(stadiums[i].toRecord());
    }
    fileManager.saveRecords("stadiums.txt", stadiumRecs);

    // 5. Officials
    std::vector<std::string> officialRecs;
    for (size_t i = 0; i < officials.size(); i++) {
        officialRecs.push_back(officials[i].toRecord());
    }
    fileManager.saveRecords("officials.txt", officialRecs);

    // 6. Fixtures
    std::vector<std::string> fixtureRecs;
    for (size_t i = 0; i < fixtures.size(); i++) {
        fixtureRecs.push_back(fixtures[i].toRecord());
    }
    fileManager.saveRecords("fixtures.txt", fixtureRecs);

    // 7. Results
    std::vector<std::string> resultRecs;
    for (size_t i = 0; i < fixtures.size(); i++) {
        if (fixtures[i].getMatchResult().getIsRecorded()) {
            resultRecs.push_back(fixtures[i].getMatchResult().toRecord());
        }
    }
    fileManager.saveRecords("results.txt", resultRecs);

    // 8. Products
    std::vector<std::string> productRecs;
    const std::vector<Product*>& inv = shop.getInventory();
    for (size_t i = 0; i < inv.size(); i++) {
        productRecs.push_back(inv[i]->toRecord());
    }
    fileManager.saveRecords("products.txt", productRecs);

    // 9. Spectators
    std::vector<std::string> specRecs;
    for (size_t i = 0; i < spectators.size(); i++) {
        specRecs.push_back(spectators[i].toRecord());
    }
    fileManager.saveRecords("spectators.txt", specRecs);

    // 10. Tickets
    std::vector<std::string> ticketRecs;
    for (size_t i = 0; i < tickets.size(); i++) {
        ticketRecs.push_back(tickets[i].toRecord());
    }
    fileManager.saveRecords("tickets.txt", ticketRecs);

    std::cout << "[System Notice] All KPFL league data successfully saved to persistent files.\n";
}

void FootballLeague::loadAllData() {
    // 1. Teams
    teams.clear();
    std::vector<std::string> teamRecs = fileManager.loadRecords("team.txt");
    for (size_t i = 0; i < teamRecs.size(); i++) {
        FootballTeam t;
        t.fromRecord(teamRecs[i]);
        teams.push_back(t);
    }

    // 2. Players
    std::vector<std::string> playerRecs = fileManager.loadRecords("players.txt");
    for (size_t i = 0; i < playerRecs.size(); i++) {
        Player p;
        p.fromRecord(playerRecs[i]);
        FootballTeam* t = findTeamById(p.getTeamId());
        if (t) {
            t->addPlayer(p);
        }
    }

    // 3. Coaches
    std::vector<std::string> coachRecs = fileManager.loadRecords("coaches.txt");
    for (size_t i = 0; i < coachRecs.size(); i++) {
        Coach c;
        c.fromRecord(coachRecs[i]);
        FootballTeam* t = findTeamById(c.getTeamId());
        if (t) {
            t->addCoach(c);
        }
    }

    // 4. Stadiums
    stadiums.clear();
    std::vector<std::string> stadiumRecs = fileManager.loadRecords("stadiums.txt");
    for (size_t i = 0; i < stadiumRecs.size(); i++) {
        Stadium s;
        s.fromRecord(stadiumRecs[i]);
        stadiums.push_back(s);
    }

    // 5. Officials
    officials.clear();
    std::vector<std::string> officialRecs = fileManager.loadRecords("officials.txt");
    for (size_t i = 0; i < officialRecs.size(); i++) {
        MatchOfficial o;
        o.fromRecord(officialRecs[i]);
        officials.push_back(o);
    }

    // 6. Fixtures
    fixtures.clear();
    std::vector<std::string> fixtureRecs = fileManager.loadRecords("fixtures.txt");
    for (size_t i = 0; i < fixtureRecs.size(); i++) {
        Fixture f;
        f.fromRecord(fixtureRecs[i]);
        fixtures.push_back(f);
    }

    // 7. Results
    std::vector<std::string> resultRecs = fileManager.loadRecords("results.txt");
    for (size_t i = 0; i < resultRecs.size(); i++) {
        MatchResult res;
        res.fromRecord(resultRecs[i]);
        Fixture* f = findFixtureById(res.getFixtureId());
        if (f) {
            f->getMatchResult() = res;
            if (res.getIsRecorded()) {
                f->setStatus("Completed");
            }
        }
    }

    // 8. Products
    shop.clearInventory();
    std::vector<std::string> productRecs = fileManager.loadRecords("products.txt");
    for (size_t i = 0; i < productRecs.size(); i++) {
        std::vector<std::string> fields = FileManager::splitFields(productRecs[i]);
        if (!fields.empty()) {
            if (fields[0] == "Merchandise") {
                Merchandise* m = new Merchandise();
                m->fromRecord(productRecs[i]);
                shop.addProduct(m);
            } else if (fields[0] == "FoodItem" || fields[0] == "Beverage" || fields[0] == "Food") {
                FoodItem* fi = new FoodItem();
                fi->fromRecord(productRecs[i]);
                shop.addProduct(fi);
            }
        }
    }

    // 9. Spectators
    spectators.clear();
    std::vector<std::string> specRecs = fileManager.loadRecords("spectators.txt");
    for (size_t i = 0; i < specRecs.size(); i++) {
        Spectator sp;
        sp.fromRecord(specRecs[i]);
        spectators.push_back(sp);
    }

    // 10. Tickets
    tickets.clear();
    std::vector<std::string> ticketRecs = fileManager.loadRecords("tickets.txt");
    for (size_t i = 0; i < ticketRecs.size(); i++) {
        Ticket tk;
        tk.fromRecord(ticketRecs[i]);
        tickets.push_back(tk);
    }

    // Synchronize standings
    recomputeStandingsFromResults();

    std::cout << "[System Notice] All KPFL league data successfully reloaded from persistent files.\n";
}

// ----------------- MANAGEMENT REPORTS (REQUIREMENT 11) -----------------

void FootballLeague::generateStandingsAndTopScorersReport() const {
    std::cout << "\n========================================================================================\n";
    std::cout << "                 MANAGEMENT REPORT 1: LEAGUE STANDINGS & TOP SCORERS                    \n";
    std::cout << "========================================================================================\n";
    displayStandings();

    std::cout << "\n----------------------- KPFL GOLDEN BOOT (TOP SCORERS) -------------------------\n";
    std::cout << std::left << std::setw(6)  << "Rank"
              << std::setw(24) << "Player Name"
              << std::setw(22) << "Club"
              << std::setw(8)  << "Jersey"
              << std::setw(8)  << "Goals" << "\n";
    std::cout << "--------------------------------------------------------------------------------\n";

    struct ScorerEntry {
        std::string playerName;
        std::string teamName;
        int jersey;
        int goals;
    };
    std::vector<ScorerEntry> scorers;

    for (size_t i = 0; i < teams.size(); i++) {
        const std::vector<Player>& pls = teams[i].getPlayers();
        for (size_t j = 0; j < pls.size(); j++) {
            if (pls[j].getGoals() > 0) {
                ScorerEntry se = { pls[j].getName(), teams[i].getName(), pls[j].getJerseyNumber(), pls[j].getGoals() };
                scorers.push_back(se);
            }
        }
    }

    std::sort(scorers.begin(), scorers.end(), [](const ScorerEntry& a, const ScorerEntry& b) {
        return a.goals > b.goals;
    });

    if (scorers.empty()) {
        std::cout << "No goals recorded yet this season.\n";
    } else {
        for (size_t i = 0; i < scorers.size(); i++) {
            std::cout << std::left << std::setw(6)  << (i + 1)
                      << std::setw(24) << scorers[i].playerName
                      << std::setw(22) << scorers[i].teamName
                      << "#" << std::setw(7) << scorers[i].jersey
                      << std::setw(8)  << scorers[i].goals << "\n";
        }
    }
    std::cout << "================================================================================\n";
}

void FootballLeague::generateTicketSalesAndAttendanceReport() const {
    std::cout << "\n========================================================================================\n";
    std::cout << "          MANAGEMENT REPORT 2: MATCH-DAY ATTENDANCE & TICKET REVENUE AUDIT              \n";
    std::cout << "========================================================================================\n";
    std::cout << std::left << std::setw(8)  << "Fix ID"
              << std::setw(28) << "Fixture Matchup"
              << std::setw(22) << "Stadium Venue"
              << std::setw(10) << "Capacity"
              << std::setw(8)  << "Sold"
              << std::setw(12) << "Attendance %"
              << std::setw(12) << "Base Rev ($)"
              << std::setw(12) << "Tax GCT ($)" << "\n";
    std::cout << "----------------------------------------------------------------------------------------\n";

    int totalTicketsSold = 0;
    double totalGrossRevenue = 0.0;
    double totalGCT = 0.0;

    for (size_t i = 0; i < fixtures.size(); i++) {
        const Fixture& f = fixtures[i];
        const FootballTeam* h = findTeamById(f.getHomeTeamId());
        const FootballTeam* a = findTeamById(f.getAwayTeamId());
        const Stadium* s = findStadiumById(f.getStadiumId());

        std::string matchup = (h ? h->getName() : "Team 1") + " vs " + (a ? a->getName() : "Team 2");
        std::string stadName = s ? s->getName() : "Stadium";
        int cap = s ? s->getCapacity() : 1;
        int sold = f.getTicketsSold();
        double pct = (static_cast<double>(sold) / cap) * 100.0;

        double baseRev = 0.0;
        double tax = 0.0;
        for (size_t j = 0; j < tickets.size(); j++) {
            if (tickets[j].getFixtureId() == f.getFixtureId() && tickets[j].getIsSold()) {
                baseRev += tickets[j].getPrice();
                tax += tickets[j].calculateTax();
            }
        }
        totalTicketsSold += sold;
        totalGrossRevenue += (baseRev + tax);
        totalGCT += tax;

        std::cout << std::left << std::setw(8)  << f.getFixtureId()
                  << std::setw(28) << matchup
                  << std::setw(22) << stadName
                  << std::setw(10) << cap
                  << std::setw(8)  << sold
                  << std::fixed << std::setprecision(1) << std::setw(11) << pct << "%"
                  << std::fixed << std::setprecision(2) << "$" << std::setw(11) << baseRev
                  << "$" << std::setw(11) << tax << "\n";
    }

    std::cout << "----------------------------------------------------------------------------------------\n";
    std::cout << "TOTAL TICKETS SOLD:     " << totalTicketsSold << "\n";
    std::cout << "TOTAL 15% GCT TAX:      $" << std::fixed << std::setprecision(2) << totalGCT << "\n";
    std::cout << "TOTAL REVENUE COLLECTED: $" << totalGrossRevenue << "\n";
    std::cout << "========================================================================================\n";
}

void FootballLeague::generateShopInventoryAndFinancialReport() const {
    std::cout << "\n========================================================================================\n";
    std::cout << "           MANAGEMENT REPORT 3: STADIUM SHOP INVENTORY & FINANCIAL AUDIT                \n";
    std::cout << "========================================================================================\n";
    std::cout << std::left << std::setw(6)  << "ID"
              << std::setw(30) << "Product Name"
              << std::setw(14) << "Category"
              << std::setw(10) << "Stock"
              << std::setw(12) << "Unit Price"
              << std::setw(14) << "Stock Value"
              << std::setw(14) << "Value w/ GCT" << "\n";
    std::cout << "----------------------------------------------------------------------------------------\n";

    double totalAssetValue = 0.0;
    double totalAssetValueGCT = 0.0;
    int totalUnits = 0;

    const std::vector<Product*>& inv = shop.getInventory();
    for (size_t i = 0; i < inv.size(); i++) {
        const Product* p = inv[i];
        double val = p->getPrice() * p->getStock();
        double valGCT = p->calculateTotal(p->getStock());
        totalAssetValue += val;
        totalAssetValueGCT += valGCT;
        totalUnits += p->getStock();

        std::cout << std::left << std::setw(6)  << p->getProductId()
                  << std::setw(30) << p->getName()
                  << std::setw(14) << p->getProductType()
                  << std::setw(10) << p->getStock()
                  << "$" << std::fixed << std::setprecision(2) << std::setw(11) << p->getPrice()
                  << "$" << std::setw(13) << val
                  << "$" << std::setw(13) << valGCT << "\n";
    }

    std::cout << "----------------------------------------------------------------------------------------\n";
    std::cout << "TOTAL UNITS IN STOCK:       " << totalUnits << "\n";
    std::cout << "TOTAL INVENTORY COST ASSETS: $" << std::fixed << std::setprecision(2) << totalAssetValue << "\n";
    std::cout << "POTENTIAL RETAIL GROSS VAL:  $" << totalAssetValueGCT << " (incl. 15% GCT)\n";
    shop.displayFinancialSummary();
}

void FootballLeague::generateClubSquadsAndPersonnelReport() const {
    std::cout << "\n========================================================================================\n";
    std::cout << "              MANAGEMENT REPORT 4: COMPLETE CLUB SQUADS & PERSONNEL ROSTER              \n";
    std::cout << "========================================================================================\n";
    for (size_t i = 0; i < teams.size(); i++) {
        teams[i].displayRoster();
    }
}

void FootballLeague::generateMatchScheduleAndOfficialsReport() const {
    std::cout << "\n========================================================================================\n";
    std::cout << "            MANAGEMENT REPORT 5: MATCH SCHEDULE & OFFICIALS CONFLICT AUDIT              \n";
    std::cout << "========================================================================================\n";
    displayAllFixtures();
    displayAllOfficials();
}
