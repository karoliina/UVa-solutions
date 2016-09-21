#include <cstdio>
#include <cmath>
#include <cstdlib>
#include <ctime>
#include <iomanip>
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

    int c, count;
    string t;
    cin >> c;
    getline(cin, t);
    getline(cin, t);
    loop(testcase, 0, c) {
        count = 0;
        map<string, int> trees;
        while (getline(cin, t)) {
            if (t.empty())
                break;
            count++;
            if (trees.find(t) == trees.end()) {
                trees[t] = 1;
            }
            else {
                trees[t]++;
            }
        }
        cout << fixed << setprecision(4);
        for (auto it = trees.begin(); it != trees.end(); it++) {
            double percent = ((double)it->second / count) * 100;
            cout << it->first << " " << percent << endl;
        }
        if (testcase < c-1) {
            cout << endl;
        }
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
