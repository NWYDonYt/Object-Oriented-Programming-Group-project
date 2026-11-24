#include "MatchResult.h"
#include "Exceptions.h"
#include "FileManager.h"
#include <iostream>

MatchResult::MatchResult()
    : fixtureId(0), homeTeamId(0), awayTeamId(0), homeScore(0), awayScore(0),
      isRecorded(false), winnerTeamId(0) {}

MatchResult::MatchResult(int fixId, int homeId, int awayId, int homeSc, int awaySc, bool recorded)
    : fixtureId(fixId), homeTeamId(homeId), awayTeamId(awayId),
      homeScore(0), awayScore(0), isRecorded(recorded), winnerTeamId(0) {
    if (recorded) {
        setScores(homeSc, awaySc);
    }
}

MatchResult::MatchResult(const MatchResult& other)
    : fixtureId(other.fixtureId), homeTeamId(other.homeTeamId), awayTeamId(other.awayTeamId),
      homeScore(other.homeScore), awayScore(other.awayScore),
      isRecorded(other.isRecorded), winnerTeamId(other.winnerTeamId) {}

int MatchResult::getFixtureId() const {
    return fixtureId;
}

int MatchResult::getHomeTeamId() const {
    return homeTeamId;
}

int MatchResult::getAwayTeamId() const {
    return awayTeamId;
}

int MatchResult::getHomeScore() const {
    return homeScore;
}

int MatchResult::getAwayScore() const {
    return awayScore;
}

bool MatchResult::getIsRecorded() const {
    return isRecorded;
}

int MatchResult::getWinnerTeamId() const {
    return winnerTeamId;
}

bool MatchResult::isDraw() const {
    return isRecorded && (winnerTeamId == -1);
}

void MatchResult::setFixtureId(int fixId) {
    if (fixId < 0) {
        throw InvalidDataException("Fixture ID cannot be negative.");
    }
    fixtureId = fixId;
}

void MatchResult::setTeams(int homeId, int awayId) {
    if (homeId <= 0 || awayId <= 0) {
        throw InvalidDataException("Team IDs must be greater than zero.");
    }
    if (homeId == awayId) {
        throw InvalidDataException("Home team and away team cannot be the same.");
    }
    homeTeamId = homeId;
    awayTeamId = awayId;
}

void MatchResult::setScores(int homeSc, int awaySc) {
    if (homeSc < 0 || awaySc < 0) {
        throw NegativeValueException("Match scores cannot be negative. Given: " +
                                     FileManager::toText(homeSc) + " - " + FileManager::toText(awaySc));
    }
    homeScore = homeSc;
    awayScore = awaySc;
    isRecorded = true;

    if (homeScore > awayScore) {
        winnerTeamId = homeTeamId;
    } else if (awayScore > homeScore) {
        winnerTeamId = awayTeamId;
    } else {
        winnerTeamId = -1; // Draw
    }
}

void MatchResult::recordResult(int fixId, int homeId, int awayId, int homeSc, int awaySc) {
    setFixtureId(fixId);
    setTeams(homeId, awayId);
    setScores(homeSc, awaySc);
}

void MatchResult::clearResult() {
    homeScore = 0;
    awayScore = 0;
    isRecorded = false;
    winnerTeamId = 0;
}

void MatchResult::displayResult(const std::string& homeName, const std::string& awayName) const {
    if (!isRecorded) {
        std::cout << "Result: Match not yet played / pending.\n";
    } else {
        std::cout << "Result: " << homeName << " " << homeScore << " - "
                  << awayScore << " " << awayName;
        if (winnerTeamId == -1) {
            std::cout << " (Full-Time Draw)\n";
        } else if (winnerTeamId == homeTeamId) {
            std::cout << " (" << homeName << " Won)\n";
        } else {
            std::cout << " (" << awayName << " Won)\n";
        }
    }
}

std::string MatchResult::toRecord() const {
    std::vector<std::string> fields;
    fields.push_back(FileManager::toText(fixtureId));
    fields.push_back(FileManager::toText(homeTeamId));
    fields.push_back(FileManager::toText(awayTeamId));
    fields.push_back(FileManager::toText(homeScore));
    fields.push_back(FileManager::toText(awayScore));
    fields.push_back(isRecorded ? "1" : "0");
    fields.push_back(FileManager::toText(winnerTeamId));
    return FileManager::joinFields(fields);
}

void MatchResult::fromRecord(const std::string& record) {
    std::vector<std::string> fields = FileManager::splitFields(record);
    if (fields.size() < 7) {
        throw FileException("MatchResult record requires 7 fields: " + record);
    }
    fixtureId = FileManager::toInt(fields[0]);
    homeTeamId = FileManager::toInt(fields[1]);
    awayTeamId = FileManager::toInt(fields[2]);
    homeScore = FileManager::toInt(fields[3]);
    awayScore = FileManager::toInt(fields[4]);
    isRecorded = (fields[5] == "1" || fields[5] == "true");
    winnerTeamId = FileManager::toInt(fields[6]);
}
