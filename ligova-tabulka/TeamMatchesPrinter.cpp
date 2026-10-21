#include "TeamMatchesPrinter.hpp"
#include <iostream>
#include <iomanip>

using namespace std;

void TeamMatchesPrinter::print(const League& league, const string& team) {
    if (!league.hasTeam(team)) {
        cout << "Tym " << team << " v lize neni." << endl;
        return;
    }
    cout << "Zapasy tymu " << team << ":" << endl;
    for (size_t i = 0; i < league.matches.size(); i++) {
        const Match& m = league.matches[i];
        if (m.involves(team)) {
            cout << "  " << left << setw(10) << m.homeTeam
                 << " - " << setw(10) << m.awayTeam << right
                 << m.score.toString() << endl;
        }
    }
}
