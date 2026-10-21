#include <iostream>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

class Score {
public:
    int home;
    int away;

    Score() {
        home = 0;
        away = 0;
    }

    static Score parse(const string& text) {
        Score s;
        stringstream ss(text);
        string part;
        getline(ss, part, ':');
        s.home = stoi(part);
        getline(ss, part, ':');
        s.away = stoi(part);
        return s;
    }

    string toString() const {
        return to_string(home) + ":" + to_string(away);
    }
};

class Match {
public:
    string homeTeam;
    string awayTeam;
    Score score;

    bool involves(const string& team) const {
        return homeTeam == team || awayTeam == team;
    }
};

class MatchParser {
public:
    static Match parseLine(const string& line) {
        Match m;
        stringstream ss(line);
        string scoreText;
        getline(ss, m.homeTeam, ';');
        getline(ss, m.awayTeam, ';');
        getline(ss, scoreText, ';');
        m.score = Score::parse(scoreText);
        return m;
    }
};

class MatchLoader {
public:
    static vector<Match> load(const string& fileName) {
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
};

class TeamStats {
public:
    string name;
    int played;
    int wins;
    int draws;
    int losses;
    int goalsFor;
    int goalsAgainst;

    TeamStats(const string& teamName) {
        name = teamName;
        played = 0;
        wins = 0;
        draws = 0;
        losses = 0;
        goalsFor = 0;
        goalsAgainst = 0;
    }

    void addResult(int scored, int conceded) {
        played++;
        goalsFor += scored;
        goalsAgainst += conceded;
        if (scored > conceded) {
            wins++;
        } else if (scored == conceded) {
            draws++;
        } else {
            losses++;
        }
    }

    int points() const {
        return wins * 3 + draws * 1;
    }

    int goalDifference() const {
        return goalsFor - goalsAgainst;
    }
};

class TableSorter {
public:
    static bool compare(const TeamStats& a, const TeamStats& b) {
        if (a.points() != b.points()) {
            return a.points() > b.points();
        }
        if (a.goalDifference() != b.goalDifference()) {
            return a.goalDifference() > b.goalDifference();
        }
        return a.name < b.name;
    }

    static void sort(vector<TeamStats>& teams) {
        std::sort(teams.begin(), teams.end(), compare);
    }
};

class League {
public:
    vector<Match> matches;
    vector<TeamStats> teams;

    League(const vector<Match>& loadedMatches) {
        matches = loadedMatches;
        calculate();
        TableSorter::sort(teams);
    }

    bool hasTeam(const string& name) const {
        for (size_t i = 0; i < teams.size(); i++) {
            if (teams[i].name == name) {
                return true;
            }
        }
        return false;
    }

private:
    TeamStats& findOrCreate(const string& name) {
        for (size_t i = 0; i < teams.size(); i++) {
            if (teams[i].name == name) {
                return teams[i];
            }
        }
        teams.push_back(TeamStats(name));
        return teams.back();
    }

    void calculate() {
        for (size_t i = 0; i < matches.size(); i++) {
            const Match& m = matches[i];
            findOrCreate(m.homeTeam).addResult(m.score.home, m.score.away);
            findOrCreate(m.awayTeam).addResult(m.score.away, m.score.home);
        }
    }
};

class TablePrinter {
public:
    static void print(const vector<TeamStats>& teams) {
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
};

class TeamMatchesPrinter {
public:
    static void print(const League& league, const string& team) {
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
};

class App {
public:
    void run() {
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
};

int main() {
    App app;
    app.run();
    return 0;
}
