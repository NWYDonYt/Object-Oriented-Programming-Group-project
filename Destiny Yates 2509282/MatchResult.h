#ifndef MATCHRESULT_H
#define MATCHRESULT_H
#pragma once
#include "Storable.h"
using namespace std;

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
        void getWinner(){
            return (homeScore > awayScore) ? "Home Team" : (awayScore > homeScore) ? "Away Team" : "Draw";
        };
        //Mutators
        void setHomeScore(int homeScore){
            this->homeScore = homeScore;
        };
        void setAwayScore(int awayScore){
            this->awayScore = awayScore;
        };
        //Accessors
        int getHomeScore(){
            return homeScore;
        };
        int getAwayScore(){
            return awayScore;
        };
};

#endif // MATCHRESULT_H