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
template <typename T>
ostream& operator<<(ostream &os, const set<T> &vec)
{
    for (T n : vec)
        os << n << " ";
    return os;
}

class UnionFind {
    private:
        vec<int> p, rank;

    public:
        UnionFind(int N) {
            rank.assign(N, 0);
            p.assign(N, 0);
            loop(i, 0, N) {
                p[i] = i;
            }
        }

        int findSet(int i) {
            return (p[i] == i) ? i : (p[i] = findSet(p[i]));
        }

        bool isSameSet(int i, int j) {
            return findSet(i) == findSet(j);
        }

        void unionSet(int i, int j) {
            if (!isSameSet(i, j)) { // if from different set
                int x = findSet(i), y = findSet(j);
                if (rank[x] > rank[y]) { // keep tree as short as possible
                    p[y] = x;
                }
                else { // rank[x] <= rank[y]
                    p[x] = y;
                    if (rank[x] == rank[y]) {
                        rank[y]++;
                    }
                }
            }
        }
};

// #define DEBUG

// debug() functions for an arbitrary number of arguments with arbitrary types
template <class T>
void debug(T t) {
#ifdef DEBUG
    clog << t << endl;
#endif
}

template <class T, class... Args>
void debug(T t, Args... args)
{
#ifdef DEBUG
    clog << t << " ";
    debug(args...);
#endif
}

int main(int argc, char* argv[]) {
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

    int n, m;
    string line;
    char a, b, c;
    char x, y;
    istringstream iss;

    while (!cin.eof()) {
        cin >> n;
        cin >> m;
        cin >> a >> b >> c;
        set<char> awake({a, b, c});
        getline(cin, line);
        int adj[50][50];
        memset(adj, 0, sizeof(adj));
        set<char> asleep;
        while (getline(cin, line)) {
            if (cin.eof() || line == "") {
                break;
            }
            iss.str(line);
            iss.clear();
            iss >> x >> y;
            int i = x - 'A', j = y - 'A';
            adj[i][j] = 1;
            adj[j][i] = 1;
            if (awake.find(x) == awake.end()) {
                asleep.insert(x);
            }
            if (awake.find(y) == awake.end()) {
                asleep.insert(y);
            }
        }

        int count = 0;
        int woken = 0;
        set<char> stillAsleep;
        set<char> nextRoundAwake(awake.begin(), awake.end());
        if (m == 0 && n == 3) {
            cout << "WAKE UP IN, 0, YEARS" << endl;
            continue;
        }
        do {
            int conn;
            stillAsleep.clear();
            woken = 0;
            for (auto it = asleep.begin(); it != asleep.end(); it++) {
                conn = 0;
                for (auto jt = awake.begin(); jt != awake.end(); jt++) {
                    if (*it != *jt && adj[*it - 'A'][*jt - 'A'] == 1) {
                        conn++;
                    }
                }
                if (conn >= 3) {
                    nextRoundAwake.insert(*it);
                    woken++;
                }
                else {
                    stillAsleep.insert(*it);
                }
            }
            if (woken > 0) {
                count++;
                asleep = stillAsleep;
                awake = nextRoundAwake;
            }
        } while (woken > 0);

        asleep.empty() && count > 0 ?
            cout << "WAKE UP IN, " << count << ", YEARS" << endl : cout << "THIS BRAIN NEVER WAKES UP" << endl;
    }

    if (argc > 1) {
        cin.rdbuf(backup);
    }

#ifndef DEBUG
    clog.clear();
#endif

    return 0;
}
