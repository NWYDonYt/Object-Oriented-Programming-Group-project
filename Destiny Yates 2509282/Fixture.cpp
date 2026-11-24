#include "Fixture.h"
#include "Exceptions.h"
#include "FileManager.h"
#include <iostream>
#include <iomanip>
#include <sstream>
#include <algorithm>
using namespace std;

Fixture::Fixture()
    : fixtureId(0), homeTeamId(0), awayTeamId(0), stadiumId(0),
      date("2026-01-01"), time("15:00"), status("Scheduled"), ticketsSold(0) {}

Fixture::Fixture(int id, int homeId, int awayId, int stadId,
                 const std::string& fixDate, const std::string& fixTime,
                 const std::string& fixStatus)
    : ticketsSold(0) {
    setFixtureId(id);
    setTeams(homeId, awayId);
    setStadiumId(stadId);
    setDate(fixDate);
    setTime(fixTime);
    setStatus(fixStatus);
}

Fixture::Fixture(const Fixture& other)
    : fixtureId(other.fixtureId), homeTeamId(other.homeTeamId), awayTeamId(other.awayTeamId),
      stadiumId(other.stadiumId), date(other.date), time(other.time),
      status(other.status), assignedOfficialIds(other.assignedOfficialIds),
      matchResult(other.matchResult), ticketsSold(other.ticketsSold) {}

int Fixture::getFixtureId() const {
    return fixtureId;
}

int Fixture::getHomeTeamId() const {
    return homeTeamId;
}

int Fixture::getAwayTeamId() const {
    return awayTeamId;
}

int Fixture::getStadiumId() const {
    return stadiumId;
}

std::string Fixture::getDate() const {
    return date;
}

std::string Fixture::getTime() const {
    return time;
}

std::string Fixture::getStatus() const {
    return status;
}

const std::vector<int>& Fixture::getAssignedOfficialIds() const {
    return assignedOfficialIds;
}

const MatchResult& Fixture::getMatchResult() const {
    return matchResult;
}

MatchResult& Fixture::getMatchResult() {
    return matchResult;
}

int Fixture::getTicketsSold() const {
    return ticketsSold;
}

void Fixture::setFixtureId(int id) {
    if (id < 0) {
        throw InvalidDataException("Fixture ID cannot be negative.");
    }
    fixtureId = id;
}

void Fixture::setHomeTeamId(int homeId) {
    if (homeId <= 0) {
        throw InvalidDataException("Home team ID must be greater than zero.");
    }
    if (homeId == awayTeamId && awayTeamId != 0) {
        throw InvalidDataException("Home team and away team cannot be the same.");
    }
    homeTeamId = homeId;
}

void Fixture::setAwayTeamId(int awayId) {
    if (awayId <= 0) {
        throw InvalidDataException("Away team ID must be greater than zero.");
    }
    if (awayId == homeTeamId && homeTeamId != 0) {
        throw InvalidDataException("Home team and away team cannot be the same.");
    }
    awayTeamId = awayId;
}

void Fixture::setTeams(int homeId, int awayId) {
    if (homeId <= 0 || awayId <= 0) {
        throw InvalidDataException("Team IDs must be greater than zero.");
    }
    if (homeId == awayId) {
        throw InvalidDataException("A team cannot play against itself.");
    }
    homeTeamId = homeId;
    awayTeamId = awayId;
}

void Fixture::setStadiumId(int stadId) {
    if (stadId < 0) {
        throw InvalidDataException("Stadium ID cannot be negative.");
    }
    stadiumId = stadId;
}

void Fixture::setDate(const std::string& fixDate) {
    if (fixDate.empty()) {
        throw InvalidDataException("Fixture date cannot be empty.");
    }
    date = fixDate;
}

void Fixture::setTime(const std::string& fixTime) {
    if (fixTime.empty()) {
        throw InvalidDataException("Fixture time cannot be empty.");
    }
    time = fixTime;
}

void Fixture::setStatus(const std::string& fixStatus) {
    if (fixStatus != "Scheduled" && fixStatus != "In Progress" &&
        fixStatus != "Completed" && fixStatus != "Postponed" && fixStatus != "Cancelled") {
        throw InvalidDataException("Invalid fixture status: " + fixStatus);
    }
    status = fixStatus;
}

void Fixture::setTicketsSold(int sold) {
    if (sold < 0) {
        throw NegativeValueException("Fixture tickets sold cannot be negative.");
    }
    ticketsSold = sold;
}

void Fixture::addTicketsSold(int count) {
    if (count < 0) {
        throw NegativeValueException("Cannot add negative ticket count.");
    }
    ticketsSold += count;
}

void Fixture::assignOfficial(int officialId) {
    if (officialId <= 0) {
        throw InvalidDataException("Official ID must be greater than zero.");
    }
    if (hasOfficial(officialId)) {
        throw InvalidDataException("Official #" + FileManager::toText(officialId) + " is already assigned to fixture #" + FileManager::toText(fixtureId));
    }
    assignedOfficialIds.push_back(officialId);
}

bool Fixture::removeOfficial(int officialId) {
    auto it = std::find(assignedOfficialIds.begin(), assignedOfficialIds.end(), officialId);
    if (it != assignedOfficialIds.end()) {
        assignedOfficialIds.erase(it);
        return true;
    }
    return false;
}

bool Fixture::hasOfficial(int officialId) const {
    return std::find(assignedOfficialIds.begin(), assignedOfficialIds.end(), officialId) != assignedOfficialIds.end();
}

void Fixture::clearOfficials() {
    assignedOfficialIds.clear();
}

void Fixture::recordResult(int homeScore, int awayScore) {
    matchResult.recordResult(fixtureId, homeTeamId, awayTeamId, homeScore, awayScore);
}

void Fixture::completeFixture() {
    if (!matchResult.getIsRecorded()) {
        throw FixtureNotCompletedException("Cannot complete fixture #" + FileManager::toText(fixtureId) +
                                          " until a valid match result has been recorded.");
    }
    status = "Completed";
}

void Fixture::displayInformation() const {
    std::cout << "[Fixture #" << fixtureId << "] Date: " << date << " " << time
              << " | Teams: #" << homeTeamId << " vs #" << awayTeamId
              << " | Stadium: #" << stadiumId
              << " | Status: " << std::left << std::setw(11) << status
              << " | Tickets Sold: " << ticketsSold;
    if (matchResult.getIsRecorded()) {
        std::cout << " | Score: " << matchResult.getHomeScore() << " - " << matchResult.getAwayScore();
    }
    std::cout << std::endl;
}

std::string Fixture::toRecord() const {
    std::vector<std::string> fields;
    fields.push_back(FileManager::toText(fixtureId));
    fields.push_back(FileManager::toText(homeTeamId));
    fields.push_back(FileManager::toText(awayTeamId));
    fields.push_back(FileManager::toText(stadiumId));
    fields.push_back(date);
    fields.push_back(time);
    fields.push_back(status);

    // Join official IDs with commas
    std::string officialList;
    for (size_t i = 0; i < assignedOfficialIds.size(); i++) {
        if (i > 0) officialList += ",";
        officialList += FileManager::toText(assignedOfficialIds[i]);
    }
    fields.push_back(officialList);
    fields.push_back(FileManager::toText(ticketsSold));

    return FileManager::joinFields(fields);
}

void Fixture::fromRecord(const std::string& record) {
    std::vector<std::string> fields = FileManager::splitFields(record);
    if (fields.size() < 9) {
        throw FileException("Fixture record requires 9 fields: " + record);
    }
    setFixtureId(FileManager::toInt(fields[0]));
    setTeams(FileManager::toInt(fields[1]), FileManager::toInt(fields[2]));
    setStadiumId(FileManager::toInt(fields[3]));
    setDate(fields[4]);
    setTime(fields[5]);
    setStatus(fields[6]);

    assignedOfficialIds.clear();
    std::string offStr = fields[7];
    if (!offStr.empty()) {
        std::stringstream ss(offStr);
        std::string offId;
        while (std::getline(ss, offId, ',')) {
            if (!offId.empty()) {
                assignedOfficialIds.push_back(FileManager::toInt(offId));
            }
        }
    }
    setTicketsSold(FileManager::toInt(fields[8]));
}
