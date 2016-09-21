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

    int T, D, Q, P;

    cin >> T;
    loop(c, 0, T) {
        cin >> D;

        vec<int> low(D);
        vec<int> high(D);
        vec<string> name(D);
        loop(l, 0, D) {
            cin >> name[l] >> low[l] >> high[l];
        }

        cin >> Q;
        loop(q, 0, Q) {
            cin >> P;
            bool found = false;
            string maker;
            loop(i, 0, D) {
                if (P >= low[i] && P <= high[i]) {
                    if (!found) {
                        found = true;
                        maker = name[i];
                    }
                    else {
                        maker = "UNDETERMINED";
                        break;
                    }
                }
            }
            if (!found) {
                maker = "UNDETERMINED";
            }
            cout << maker << endl;
        }

        if (c < T-1) {
            cout << endl;
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
