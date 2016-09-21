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
#include <utility>

using namespace std;

#define loop(x, start, end) for (uint x = start; x < end; ++x)

#define INF 100000000
#define PI 2*acos(0.0)

typedef long long ll;

template <typename T>
using vec = vector<T>;

typedef pair<int, int> ii;
typedef vector<ii> vii;

// overload operator << for vectors of an arbitrary type
template <typename T>
ostream& operator<<(ostream &os, const vector<T> &vec)
{
    for (T n : vec)
        os << n << " ";
    return os;
}

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

    int m, n, tmp, nums;
    vector<vii> adj; // vector of vectors of pairs
    vector<vii> res;

    while (!cin.eof()) {
        cin >> m >> n;
        if (m == 0 && n == 0) {
            break;
        }
        adj.clear();
        res.clear();
        adj.resize(m);
        res.resize(n);
        loop(i, 0, m) {
            cin >> nums;
            vec<int> idx(nums);
            loop(j, 0, nums) {
                cin >> idx[j];
            }
            loop(j, 0, nums) {
                cin >> tmp;
                adj[i].push_back(make_pair(idx[j], tmp));
            }
        }

        loop(i, 0, m) {
            loop(j, 0, adj[i].size()) {
                ii p = adj[i][j];
                res[p.first - 1].push_back(make_pair(i+1, p.second));
            }
        }
        cout << n << " " << m << endl;
        loop(i, 0, n) {
            cout << res[i].size();
            loop(j, 0, res[i].size()) {
                cout << " " << res[i][j].first;
            }
            cout << endl;
            loop(j, 0, res[i].size()) {
                cout << res[i][j].second;
                if (j < res[i].size() - 1) {
                    cout << " ";
                }
            }
            cout << endl;
        }
        m = 0;
        n = 0;
    }

    if (argc > 1) {
        cin.rdbuf(backup);
    }

#ifndef DEBUG
    clog.clear();
#endif

    return 0;
}
