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

    int cases, n, tmp;
    cin >> cases;
    loop(c, 0, cases) {
        cin >> n;
        map<int, vec<int> > flakes;
        int curLen = 0;
        int maxLen = 0;
        int startIdx = 0;
        loop(f, 0, n) {
            cin >> tmp;
            if (flakes.find(tmp) == flakes.end()) {
                flakes[tmp] = vec<int>(1, f);
                curLen++;
                debug("first occurrence of", tmp, "current length =", curLen);
            }
            else {
                int prevIdx = flakes[tmp].back();
                startIdx = max(prevIdx + 1, startIdx);
                flakes[tmp].push_back(f);
                maxLen = max(maxLen, curLen);
                curLen = f - startIdx + 1;
                debug("repeating occurrence of", tmp, "new max length =", maxLen, "new current length =",
                        curLen, "new start idx =", startIdx);
            }
        }
        maxLen = max(maxLen, curLen);
        cout << maxLen << endl;
        debug("");
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
