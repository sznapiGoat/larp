#pragma once
#include <string>
#include "League.hpp"

class App {
public:
    void run();

private:
    League league;

    void printTable() const;
    void printTeamMatches(const std::string& team) const;
};
