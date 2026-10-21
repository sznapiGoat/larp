#include "TablePrinter.hpp"
#include <iostream>
#include <iomanip>
#include <string>

using namespace std;

void TablePrinter::print(const vector<TeamStats>& teams) {
    cout << setw(3) << "#" << " "
         << left << setw(10) << "tym" << right
         << setw(3) << "Z"
         << setw(3) << "V"
         << setw(3) << "R"
         << setw(3) << "P"
         << setw(8) << "skore"
         << setw(6) << "body" << endl;

    for (size_t i = 0; i < teams.size(); i++) {
        const TeamStats& t = teams[i];
        string score = to_string(t.goalsFor) + ":" + to_string(t.goalsAgainst);
        cout << setw(3) << (i + 1) << " "
             << left << setw(10) << t.name << right
             << setw(3) << t.played
             << setw(3) << t.wins
             << setw(3) << t.draws
             << setw(3) << t.losses
             << setw(8) << score
             << setw(6) << t.points() << endl;
    }
}
