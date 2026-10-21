#pragma once
#include <string>

class TeamStats {
public:
    std::string name;
    int played;
    int wins;
    int draws;
    int losses;
    int goalsFor;
    int goalsAgainst;

    TeamStats(const std::string& teamName);
    void addResult(int scored, int conceded);
    int points() const;
    int goalDifference() const;
};
