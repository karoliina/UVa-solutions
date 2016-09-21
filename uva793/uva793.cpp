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

#define DEBUG

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

    int cases, n, x, y, successes, fails;
    char type;
    string line;
    istringstream iss;
    cin >> cases;
    loop(c, 0, cases) {
        cin >> n;
        UnionFind uf = UnionFind(n);
        successes = 0;
        fails = 0;
        getline(cin, line);
        while (getline(cin, line)) {
            if (line == "" || cin.eof()) {
                break;
            }
            iss.str(line);
            iss.clear();
            iss >> type >> x >> y;
            if (type == 'c') {
                uf.unionSet(x-1, y-1);
            }
            else if (type == 'q') {
                uf.isSameSet(x-1, y-1) ? successes++ : fails++;
            }
        }
        cout << successes << "," << fails << endl;
        if (c < cases - 1)
            cout << endl;
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
