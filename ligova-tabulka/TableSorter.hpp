#pragma once
#include <vector>
#include "TeamStats.hpp"

class TableSorter {
public:
    static bool compare(const TeamStats& a, const TeamStats& b);
    static void sort(std::vector<TeamStats>& teams);
};
