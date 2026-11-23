#ifndef MATCHRESULT_H
#define MATCHRESULT_H
#pragma once
#include "Storable.h"
class MatchResult {
    private:
        int homeScore;
        int awayScore;

    public:
        //Default Constructor
        MatchResult()
        {
            homeScore = 0;
            awayScore = 0;
        };
        //Parameterized Constructor
        MatchResult(int homeScore, int awayScore)
        {
            this->homeScore = homeScore;
            this->awayScore = awayScore;
        }
        // Copy Constructor
        MatchResult(const MatchResult& MR)
        {
            this->homeScore = MR.homeScore;
            this->awayScore = MR.awayScore;
        }
        void getWinner();

        //Mutators
        void setHomeScore(int homeScore);
        void setAwayScore(int awayScore);

        //Accessors
        int getHomeScore();
        int getAwayScore();
};

#endif // MATCHRESULT_H