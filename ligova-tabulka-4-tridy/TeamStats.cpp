#include "TeamStats.hpp"

using namespace std;

TeamStats::TeamStats(const string& teamName) {
    name = teamName;
    played = 0;
    wins = 0;
    draws = 0;
    losses = 0;
    goalsFor = 0;
    goalsAgainst = 0;
}

void TeamStats::addResult(int scored, int conceded) {
    played++;
    goalsFor += scored;
    goalsAgainst += conceded;
    if (scored > conceded) {
        wins++;
    } else if (scored == conceded) {
        draws++;
    } else {
        losses++;
    }
}

int TeamStats::points() const {
    return wins * 3 + draws * 1;
}

int TeamStats::goalDifference() const {
    return goalsFor - goalsAgainst;
}
