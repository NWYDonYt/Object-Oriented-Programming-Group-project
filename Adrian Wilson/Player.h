//Player Header File
#ifndef PLAYER_H
#define PLAYER_H

#include <string>

// Step 1: the Player's own data only. Inheritance from Person comes next.
class Player {
private:
    string position;
    int jerseyNumber;
    int goals;
    string playingStatus;

public:
    Player(string playerPosition, int shirtNumber, int goalsScored, string status);

    string getPosition() const;
    int getJerseyNumber() const;
    int getGoals() const;
    string getPlayingStatus() const;

    void setPosition(string newPosition);
    void setJerseyNumber(int newNumber);
    void setPlayingStatus(string newStatus);
    void addGoals(int extraGoals);

    void displayInformation() const;
};

#endif
