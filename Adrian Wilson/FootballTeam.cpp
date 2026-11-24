FootballLeague::FootballLeague(string name, int year) {
    leagueName = name;
    season = year;
}

string FootballLeague::getLeagueName() const {
    return leagueName;
}

int FootballLeague::getSeason() const {
    return season;
}

vector<string> FootballLeague::readData(string filename) const {
    vector<string> records;
    ifstream file(filename);
    string line;

    while (getline(file, line)) {
        if (!line.empty()) {
            records.push_back(line);
        }
    }

    file.close();

    return records;
}

void FootballLeague::displayInformation() const {
    cout << "\nKINGSTON PREMIER FOOTBALL LEAGUE\n";
    cout << "League: " << leagueName << endl;
    cout << "Season: " << season << endl;
}