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

float twoDecimals(float val) {
    return round(val * 100) / 100.0;
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

    ll d, s, p;
    float fd;

    for (ll a = 1; a < 1997; a++) {
        for (ll b = 1; b < 1997 && a + b < 1998 && a*b <= 20000000; b++) {
            if (a <= b) {
                for (ll c = 1; c < 1997 && a + b + c < 1999 && a*b*c <= 2000000000; c++) {
                    if (b <= c) {
                        fd = 1e6*(a + b + c)/(a*b*c - 1e6);

                        if (floor(fd) < c || fd < 1.0 || fd > 1997.0 || abs(float(floor(fd)) - fd) > 1e-8) {
                            continue;
                        }

                        d = floor(fd);

                        s = a + b + c + d;
                        p = a*b*c*d;

                        if (s <= 2000 && p <= 2000*1e6 && 1e6*s == p) {
                            printf("%.2f %.2f %.2f %.2f\n", a/100.0, b/100.0, c/100.0, d/100.0);
                        }
                    }
                }
            }
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
