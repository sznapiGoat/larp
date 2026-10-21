#pragma once
#include <string>

class Match {
public:
    std::string homeTeam;
    std::string awayTeam;
    int homeGoals;
    int awayGoals;

    Match();
    static Match parse(const std::string& line);
    bool involves(const std::string& team) const;
    std::string scoreText() const;
};
