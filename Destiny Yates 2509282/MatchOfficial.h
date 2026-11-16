#ifndef MATCHOFFICAL_H
#define MATCHOFFICAL_H

#pragma once
#include <string>
#include "Person.h"
class MatchOfficial {
    private:
        std::string officiatingRole;
        std::string rank;
        bool Available;
    public:
        MatchOfficial();
        MatchOfficial(std::string officiatingRole, std::string rank, bool Available);
        MatchOfficial(const MatchOfficial& MO);
        void setOfficiatingRole(std::string officiatingRole);
        void setRank(std::string rank);
        void setAvailable(bool Available);
        std::string getOfficiatingRole();
        std::string getRank();
        bool getAvailable();
};

#endif // MATCHOFFICAL_H