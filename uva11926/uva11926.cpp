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

// #define DEBUG

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

    int n, m, s, e, r;

    while (true) {
        cin >> n >> m;
        if (n == 0 && m == 0)
            break;

        bitset<1000000> slots;

        bool conflict = false;
        loop(i, 0, n) {
            cin >> s >> e;
            loop(j, s, e) {
                if (slots.test(j)) {
                    conflict = true;
                    debug("conflict at position", j);
                    debug("s", s, "e", e);
                    break;
                }
                slots.set(j);
            }
        }

        loop(i, 0, m) {
            cin >> s >> e >> r;
            int m = e;
            for (int k = s; k < 1000000; k += r) {
                for (int j = k; j < m && j < 1000000; j++) {
                    if (slots.test(j)) {
                        conflict = true;
                        debug("conflict at position", j);
                        debug("s", s, "e", e, "r", r);
                        break;
                    }
                    slots.set(j);
                }
                m += r;
            }
        }

        if (conflict)
            cout << "CONFLICT" << endl;
        else
            cout << "NO CONFLICT" << endl;
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
