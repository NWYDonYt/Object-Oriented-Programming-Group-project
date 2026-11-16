//Football League Header File
#ifndef FOOTBALLLEAGUE_H
#define FOOTBALLLEAGUE_H

#include <string>
#include <vector>

class FootballLeague {
private:
    std::string leagueName;
    int season;

public:
    FootballLeague(std::string name, int year);
    std::string getLeagueName();
    int getSeason();
    std::vector<std::string> readData(std::string filename);
    void displayInformation();
};

#endif
  