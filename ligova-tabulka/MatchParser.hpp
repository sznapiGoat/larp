#pragma once
#include <string>
#include "Match.hpp"

class MatchParser {
public:
    static Match parseLine(const std::string& line);
};
