#ifndef MATCHOFFICAL_H
#define MATCHOFFICAL_H

#pragma once
#include <string>
#include "Person.h"
class MatchOfficial {
    private:
        string officiatingRole;
        string rank;
        bool Available;
    public:
    // Default constructor
        MatchOfficial(){
            officiatingRole = "";
            rank = "";
            Available = false;
        };
    // Parameterized constructor
        MatchOfficial(std::string officiatingRole, std::string rank, bool Available){
            this->officiatingRole = officiatingRole;
            this->rank = rank;
            this->Available = Available;
        };
    // Copy constructor
        MatchOfficial(const MatchOfficial& MO){
            this->officiatingRole = MO.officiatingRole;
            this->rank = MO.rank;
            this->Available = MO.Available;
        };

       //Mutators
        void setOfficiatingRole(std::string officiatingRole);
        void setRank(std::string rank);
        void setAvailable(bool Available);

        //Accessors
        std::string getOfficiatingRole();
        std::string getRank();
        bool getAvailable();
};

#endif // MATCHOFFICAL_H