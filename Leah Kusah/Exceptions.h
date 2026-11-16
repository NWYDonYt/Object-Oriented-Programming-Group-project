//Exceptions Header File
#ifndef EXCEPTIONS_H
#define EXCEPTIONS_H

#include <stdexcept>
#include <string>

class LeagueException : public std::runtime_error {
public:
    LeagueException(std::string message)
        : std::runtime_error(message) {}
};

class TeamNotFoundException : public LeagueException {
public:
    TeamNotFoundException(std::string message)
        : LeagueException(message) {}
};

class PlayerNotFoundException : public LeagueException {
public:
    PlayerNotFoundException(std::string message)
        : LeagueException(message) {}
};

#endif