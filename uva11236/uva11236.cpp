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

    float d, s, p, ra, rb, rc, rd;
    int count = 0;

    for (float a = 0.01; a <= 19.97; a += 0.01) {
        for (float b = 0.01; b <= 19.97 && a + b <= 19.98 && a*b <= 20.0; b += 0.01) {
            for (float c = 0.01; c <= 19.97 && a + b + c <= 19.99 && a*b*c <= 20.0; c += 0.01) {
                ra = twoDecimals(a);
                rb = twoDecimals(b);
                rc = twoDecimals(c);

                d = (ra + rb + rc)/(ra*rb*rc - 1.0);
                rd = twoDecimals(d);

                // printf("%10.6f %10.6f %10.6f %10.6f\n", a, b, c, d);
                if (d < 0.01 || d > 19.97 || abs(float(round(d*100)) - d*100) > 1e-8) {
                    c = twoDecimals(c);
                    continue;
                }

                s = ra + rb + rc + rd;
                p = ra*rb*rc*rd;

                if (s <= 20.0 && p <= 20.0 && abs(s - p) < 1e-13) {
                    debug("solution:", ra, rb, rc, rd, "sum =", s, "product =", p);
                    debug("actual:  ", a, b, c, d);
                    count++;
                }

                if (count > 10) {
                    return 0;
                }

                c = twoDecimals(c);
            }
            b = twoDecimals(b);
        }
        a = twoDecimals(a);
    }
    debug(count);

    if (argc > 1) {
        cin.rdbuf(backup);
    }

#ifndef DEBUG
    clog.clear();
#endif

    return 0;
}
