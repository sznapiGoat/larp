#pragma once
#include <string>
#include <vector>
#include "Match.hpp"
#include "TeamStats.hpp"

class League {
public:
    std::vector<Match> matches;
    std::vector<TeamStats> teams;

    bool load(const std::string& fileName);
    void calculate();
    bool hasTeam(const std::string& name) const;

private:
    TeamStats& findOrCreate(const std::string& name);
    static bool compare(const TeamStats& a, const TeamStats& b);
};
