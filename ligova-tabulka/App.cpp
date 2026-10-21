#include "App.hpp"
#include "MatchLoader.hpp"
#include "League.hpp"
#include "TablePrinter.hpp"
#include "TeamMatchesPrinter.hpp"
#include <iostream>
#include <string>
#include <vector>

using namespace std;

void App::run() {
    vector<Match> matches = MatchLoader::load("matches.txt");
    if (matches.empty()) {
        return;
    }
    cout << "Nacteno " << matches.size() << " zapasu." << endl;

    League league(matches);
    TablePrinter::print(league.teams);

    cout << endl << "Zadej tym: ";
    string team;
    getline(cin, team);
    cout << endl;
    TeamMatchesPrinter::print(league, team);
}
