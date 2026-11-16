#ifndef Footballleague_H
#define Footballleague_H

class Footballleague {
    private:
        string leagueName;
        int season;
       
    public:
        Footballleague(string name, int year);
        void sheduleFixtur();
        void recordResult();
        void showStandings();
};