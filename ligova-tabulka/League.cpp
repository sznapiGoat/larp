#include "League.hpp"
#include "TableSorter.hpp"

using namespace std;

League::League(const vector<Match>& loadedMatches) {
    matches = loadedMatches;
    calculate();
    TableSorter::sort(teams);
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

void League::calculate() {
    for (size_t i = 0; i < matches.size(); i++) {
        const Match& m = matches[i];
        findOrCreate(m.homeTeam).addResult(m.score.home, m.score.away);
        findOrCreate(m.awayTeam).addResult(m.score.away, m.score.home);
    }
}
