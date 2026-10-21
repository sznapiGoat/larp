#pragma once
#include <string>
#include <vector>
#include "Match.hpp"
#include "TeamStats.hpp"

class League {
public:
    std::vector<Match> matches;
    std::vector<TeamStats> teams;

    League(const std::vector<Match>& loadedMatches);
    bool hasTeam(const std::string& name) const;

private:
    TeamStats& findOrCreate(const std::string& name);
    void calculate();
};
