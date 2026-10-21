#pragma once
#include <string>
#include "Score.hpp"

class Match {
public:
    std::string homeTeam;
    std::string awayTeam;
    Score score;

    bool involves(const std::string& team) const;
};
