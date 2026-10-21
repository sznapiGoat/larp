#include "Score.hpp"
#include <sstream>

using namespace std;

Score::Score() {
    home = 0;
    away = 0;
}

Score Score::parse(const string& text) {
    Score s;
    stringstream ss(text);
    string part;
    getline(ss, part, ':');
    s.home = stoi(part);
    getline(ss, part, ':');
    s.away = stoi(part);
    return s;
}

string Score::toString() const {
    return to_string(home) + ":" + to_string(away);
}
