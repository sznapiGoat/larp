#pragma once
#include <string>
#include <vector>
#include "Match.hpp"

class MatchLoader {
public:
    static std::vector<Match> load(const std::string& fileName);
};
