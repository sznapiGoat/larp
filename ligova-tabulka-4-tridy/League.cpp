#include "League.hpp"
#include <fstream>
#include <algorithm>

using namespace std;

bool League::load(const string& fileName) {
    ifstream file(fileName);
    if (!file.is_open()) {
        return false;
    }
    string line;
    while (getline(file, line)) {
        if (!line.empty() && line.back() == '\r') {
            line.pop_back();
        }
        if (line.empty()) {
            continue;
        }
        matches.push_back(Match::parse(line));
    }
    return true;
}

void League::calculate() {
    for (size_t i = 0; i < matches.size(); i++) {
        const Match& m = matches[i];
        findOrCreate(m.homeTeam).addResult(m.homeGoals, m.awayGoals);
        findOrCreate(m.awayTeam).addResult(m.awayGoals, m.homeGoals);
    }
    sort(teams.begin(), teams.end(), compare);
}

bool League::hasTeam(const string& name) const {
    for (size_t i = 0; i < teams.size(); i++) {
        if (teams[i].name == name) {
            return true;
        }
    }
    return false;
}

TeamStats& League::findOrCreate(const string& name) {
    for (size_t i = 0; i < teams.size(); i++) {
        if (teams[i].name == name) {
            return teams[i];
        }
    }
    teams.push_back(TeamStats(name));
    return teams.back();
}

bool League::compare(const TeamStats& a, const TeamStats& b) {
    if (a.points() != b.points()) {
        return a.points() > b.points();
    }
    if (a.goalDifference() != b.goalDifference()) {
        return a.goalDifference() > b.goalDifference();
    }
    return a.name < b.name;
}
