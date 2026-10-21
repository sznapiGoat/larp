#pragma once
#include <vector>
#include "TeamStats.hpp"

class TablePrinter {
public:
    static void print(const std::vector<TeamStats>& teams);
};
