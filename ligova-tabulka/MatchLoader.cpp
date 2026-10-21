#include "MatchLoader.hpp"
#include "MatchParser.hpp"
#include <fstream>
#include <iostream>

using namespace std;

vector<Match> MatchLoader::load(const string& fileName) {
    vector<Match> matches;
    ifstream file(fileName);
    if (!file.is_open()) {
        cout << "Soubor " << fileName << " nelze otevrit." << endl;
        return matches;
    }
    string line;
    while (getline(file, line)) {
        if (!line.empty() && line.back() == '\r') {
            line.pop_back();
        }
        if (line.empty()) {
            continue;
        }
        matches.push_back(MatchParser::parseLine(line));
    }
    return matches;
}
