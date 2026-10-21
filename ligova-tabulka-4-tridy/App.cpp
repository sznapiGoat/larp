#include "App.hpp"
#include <iostream>
#include <iomanip>

using namespace std;

void App::run() {
    if (!league.load("matches.txt")) {
        cout << "Soubor matches.txt nelze otevrit." << endl;
        return;
    }
    cout << "Nacteno " << league.matches.size() << " zapasu." << endl;

    league.calculate();
    printTable();

    cout << endl << "Zadej tym: ";
    string team;
    getline(cin, team);
    cout << endl;
    printTeamMatches(team);
}

void App::printTable() const {
    cout << setw(3) << "#" << " "
         << left << setw(10) << "tym" << right
         << setw(3) << "Z"
         << setw(3) << "V"
         << setw(3) << "R"
         << setw(3) << "P"
         << setw(8) << "skore"
         << setw(6) << "body" << endl;

    for (size_t i = 0; i < league.teams.size(); i++) {
        const TeamStats& t = league.teams[i];
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

void App::printTeamMatches(const string& team) const {
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
                 << m.scoreText() << endl;
        }
    }
}
