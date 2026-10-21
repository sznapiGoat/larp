#include "Match.hpp"

using namespace std;

bool Match::involves(const string& team) const {
    return homeTeam == team || awayTeam == team;
}
