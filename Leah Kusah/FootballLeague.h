#ifndef Footballleague_H
#define Footballleague_H

#pragma once
#include <string>
#include <vector>
#include "Storable.h"
#include "Player.h"
#include "Coach.h"
using namespace std;

class Footballleague {
    private:
        std::string leagueName;
        int season;
       
    public:
        Footballleague(std::string name, int year);
        void sheduleFixtur();
        void recordResult();
        void showStandings();
};
#endif