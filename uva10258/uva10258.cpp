#include <cstdio>
#include <cmath>
#include <cstdlib>
#include <ctime>
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <algorithm>
#include <regex>
#include <vector>
#include <map>
#include <set>

using namespace std;

#define loop(x, start, end) for (uint x = start; x < end; ++x)

#define INF 100000000
#define PI 2*acos(0.0)

typedef long long ll;

template <typename T>
using vec = vector<T>;

// overload operator << for vectors of an arbitrary type
template <typename T>
ostream& operator<<(ostream &os, const vector<T> &vec)
{
    for (T n : vec)
        os << n << " ";
    return os;
}

// debug() functions for an arbitrary number of arguments with arbitrary types
template <class T>
void debug(T t) {
    clog << t << endl;
}

template <class T, class... Args>
void debug(T t, Args... args)
{
    clog << t << " ";
    debug(args...);
}

bool cmp(vec<int> team1, vec<int> team2) {
    if (team1[1] == team2[1] && team1[2] == team2[2])
        return team1[0] < team2[0];
    if (team1[1] > team2[1]) {
        return true;
    }
    else if (team2[1] > team1[1]) {
        return false;
    }
    return team1[2] < team2[2];
}

bool noneAttempted(vec<int> team) {
    return team[1] == -1;
}

#define DEBUG

int main(int argc, char* argv[]) {

#ifndef DEBUG
    clog.setstate(ios_base::failbit);
#endif

    streambuf* backup;
    streambuf* filebuf;

    if (argc > 1) { // input file
        static ifstream fs(argv[1]);
        if (!fs) {
            cout << "can't open file" << endl;
            exit(1);
        }
        backup = cin.rdbuf();
        filebuf = fs.rdbuf();
        cin.rdbuf(filebuf);
    }

    // START SOLUTION

    int n, team, problem, time;
    char L;
    cin >> n;
    cin.get();

    string line;
    istringstream ss;
    getline(cin, line); // read empty line
    // debug("1:", line);
    loop(c, 0, n) {
        // debug("CASE", c);
        vec<vec<int> > teams(101, vec<int>(3, 0)); // team number, # of problems solved, total penalty time
        vec<map<int, int> > penalty(101); // accumulated penalty time per problem for each team
        vec<set<int> > solved(101); // which teams have already correctly solved which problems

        loop(i, 0, 101) {
            teams[i][0] = i;
            teams[i][1] = -1; // change to 0 if team makes a R/E/U submission
        }

        while(true) {
            getline(cin, line);
            // debug("2:", line);
            if (line == "")
                break;

            ss.str(line);
            ss >> team >> problem >> time >> L;
            if (L == 'C') {
                if (solved[team].find(problem) != solved[team].end()) {
                    // this team has already solved this problem
                    continue;
                }
                else {
                    solved[team].insert(problem);
                }
                if (teams[team][1] < 0) {
                    teams[team][1] = 1;
                }
                else {
                    teams[team][1]++;
                }
                teams[team][2] += penalty[team][problem] + time;
            }
            else if (L == 'I') {
                penalty[team][problem] += 20;
                if (teams[team][1] < 0)
                    teams[team][1] = 0;
            }
            else if ((L == 'R' || L == 'E' || L == 'U') && (teams[team][1] < 0))
                teams[team][1] = 0;
        }

        // remove teams with -1 solved problems
        auto newEnd = remove_if(teams.begin(), teams.end(), noneAttempted);

        // sort and print the scoreboard
        sort(teams.begin(), newEnd, cmp);
        for (auto it = teams.begin(); it != newEnd; it++) {
            vec<int> team = *it;
            printf("%d %d %d\n", team[0], team[1], team[2]);
        }
        if (c < n-1)
            printf("\n");
    }

    // END SOLUTION
    if (argc > 1) {
        cin.rdbuf(backup);
    }

#ifndef DEBUG
    clog.clear();
#endif

    return 0;
}
