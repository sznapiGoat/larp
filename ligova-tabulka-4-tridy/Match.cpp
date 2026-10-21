#include "Match.hpp"
#include <sstream>

using namespace std;

Match::Match() {
    homeGoals = 0;
    awayGoals = 0;
}

Match Match::parse(const string& line) {
    Match m;
    stringstream ss(line);
    string scoreText;
    getline(ss, m.homeTeam, ';');
    getline(ss, m.awayTeam, ';');
    getline(ss, scoreText, ';');

    stringstream scoreStream(scoreText);
    string part;
    getline(scoreStream, part, ':');
    m.homeGoals = stoi(part);
    getline(scoreStream, part, ':');
    m.awayGoals = stoi(part);
    return m;
}

bool Match::involves(const string& team) const {
    return homeTeam == team || awayTeam == team;
}

string Match::scoreText() const {
    return to_string(homeGoals) + ":" + to_string(awayGoals);
}
