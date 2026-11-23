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

// New: a value is empty, out of range, or badly formatted
class InvalidDataException : public LeagueException {
public:
    InvalidDataException(std::string message)
        : LeagueException(message) {}
};

// New: a score, quantity or count was negative
class NegativeValueException : public LeagueException {
public:
    NegativeValueException(std::string message)
        : LeagueException(message) {}
};


#endif