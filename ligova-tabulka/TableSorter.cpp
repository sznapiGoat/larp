#include "TableSorter.hpp"
#include <algorithm>

using namespace std;

bool TableSorter::compare(const TeamStats& a, const TeamStats& b) {
    if (a.points() != b.points()) {
        return a.points() > b.points();
    }
    if (a.goalDifference() != b.goalDifference()) {
        return a.goalDifference() > b.goalDifference();
    }
    return a.name < b.name;
}

void TableSorter::sort(vector<TeamStats>& teams) {
    std::sort(teams.begin(), teams.end(), compare);
}
