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

bool compare(vec<int> a, vec<int> b) {
    if (a[0] == b[0]) {
        return a[1] < b[1];
    }
    return a[0] < b[0];
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

    int N, A, B, C;

    cin >> N;

    loop(testcase, 0, N) {
        cin >> A >> B >> C;

        bool found = false;

        for (int x = -100; x <= 100 && !found; x++) {
            if (x*x <= C) {
                for (int y = -100; y <= 100 && !found; y++) {
                    if (x != y && x*x + y*y <= C) {
                        for (int z = -100; z <= 100 && !found; z++) {
                            if (x != z && y != z) {
                                // debug("checking", x, y, z);
                                if (x + y + z == A &&
                                    x*y*z == B &&
                                    x*x + y*y + z*z == C) {
                                    found = true;
                                    cout << x << " " << y << " " << z << endl;
                                }
                            }
                        }
                    }
                }
            }
        }

        if (!found) {
            cout << "No solution." << endl;
        }
    }

    if (argc > 1) {
        cin.rdbuf(backup);
    }

#ifndef DEBUG
    clog.clear();
#endif

    return 0;
}
