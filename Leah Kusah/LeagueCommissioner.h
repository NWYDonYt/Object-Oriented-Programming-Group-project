#ifdef LeagueCommissioner_h
#define LeagueCommissioner_h

class LeagueCommissioner {
    private:
        string commissionerName;
        FootballLeague* league;
    public:
       LeagueCommissioner(string name, FootballLeague* teamLeague);
       void approveTeam() const;
       void displayInfo() const;
};

#endif