#include "MatchParser.hpp"
#include <sstream>

using namespace std;

Match MatchParser::parseLine(const string& line) {
    Match m;
    stringstream ss(line);
    string scoreText;
    getline(ss, m.homeTeam, ';');
    getline(ss, m.awayTeam, ';');
    getline(ss, scoreText, ';');
    m.score = Score::parse(scoreText);
    return m;
}
