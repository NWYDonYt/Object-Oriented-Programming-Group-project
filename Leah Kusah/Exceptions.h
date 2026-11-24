#ifndef EXCEPTIONS_H
#define EXCEPTIONS_H

#include <stdexcept>
#include <string>

// Base exception for all KPFL league operations
class LeagueException : public std::runtime_error {
public:
    explicit LeagueException(const std::string& message)
        : std::runtime_error(message) {}
};

// Entity lookup exceptions
class TeamNotFoundException : public LeagueException {
public:
    explicit TeamNotFoundException(const std::string& message)
        : LeagueException("Team Error: " + message) {}
};

class PlayerNotFoundException : public LeagueException {
public:
    explicit PlayerNotFoundException(const std::string& message)
        : LeagueException("Player Error: " + message) {}
};

class CoachNotFoundException : public LeagueException {
public:
    explicit CoachNotFoundException(const std::string& message)
        : LeagueException("Coach Error: " + message) {}
};

class OfficialNotFoundException : public LeagueException {
public:
    explicit OfficialNotFoundException(const std::string& message)
        : LeagueException("Match Official Error: " + message) {}
};

class StadiumNotFoundException : public LeagueException {
public:
    explicit StadiumNotFoundException(const std::string& message)
        : LeagueException("Stadium Error: " + message) {}
};

class FixtureNotFoundException : public LeagueException {
public:
    explicit FixtureNotFoundException(const std::string& message)
        : LeagueException("Fixture Error: " + message) {}
};

class ProductNotFoundException : public LeagueException {
public:
    explicit ProductNotFoundException(const std::string& message)
        : LeagueException("Product Error: " + message) {}
};

// Business rule exceptions
class InvalidDataException : public LeagueException {
public:
    explicit InvalidDataException(const std::string& message)
        : LeagueException("Invalid Data Error: " + message) {}
};

class NegativeValueException : public LeagueException {
public:
    explicit NegativeValueException(const std::string& message)
        : LeagueException("Negative Value Error: " + message) {}
};

class CapacityExceededException : public LeagueException {
public:
    explicit CapacityExceededException(const std::string& message)
        : LeagueException("Capacity Exceeded Error: " + message) {}
};

class SchedulingConflictException : public LeagueException {
public:
    explicit SchedulingConflictException(const std::string& message)
        : LeagueException("Scheduling Conflict Error: " + message) {}
};

class TeamIneligibleException : public LeagueException {
public:
    explicit TeamIneligibleException(const std::string& message)
        : LeagueException("Team Eligibility Error: " + message) {}
};

class InsufficientPaymentException : public LeagueException {
public:
    explicit InsufficientPaymentException(const std::string& message)
        : LeagueException("Payment Error: " + message) {}
};

class FixtureNotCompletedException : public LeagueException {
public:
    explicit FixtureNotCompletedException(const std::string& message)
        : LeagueException("Fixture Completion Error: " + message) {}
};

// File persistence exception
class FileException : public LeagueException {
public:
    explicit FileException(const std::string& message)
        : LeagueException("File Error: " + message) {}
};

#endif // EXCEPTIONS_H
