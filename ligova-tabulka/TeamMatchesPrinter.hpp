#pragma once
#include <string>
#include "League.hpp"

class TeamMatchesPrinter {
public:
    static void print(const League& league, const std::string& team);
};
