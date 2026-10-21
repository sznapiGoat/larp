#pragma once
#include <string>

class Score {
public:
    int home;
    int away;

    Score();
    static Score parse(const std::string& text);
    std::string toString() const;
};
