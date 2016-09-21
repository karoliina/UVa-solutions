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

ll poly(vec<ll> c, ll n) {
    ll res = 0;
    loop(i, 0, c.size()) {
        res += c[i]*pow(n, i);
    }
    return res;
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

    // sum = 1/2*n*(n+1) ???

    ll C, d, k, i;
    string s;

    cin >> C;
    loop(testcase, 0, C) {
        cin >> i;
        vec<ll> c(i+1);

        loop(coeff, 0, i+1) {
            cin >> c[coeff];
        }

        // debug("POLY:");
        // debug(c);
        // loop(j, 0, 5) {
        //     debug(j, poly(c, j));
        // }

        cin >> d >> k;

        ll occ = d;
        ll occCount = 0;
        ll totalCount = 0;
        ll prev = 0;
        ll degree = 1;
        ll val = poly(c, degree);

        while (totalCount < k) {
            // debug("totalCount =", totalCount, "val =", val, "occCount =", occCount, "occ =", occ, "val =", val);
            prev = val;
            totalCount++;
            occCount++;

            if (occCount == occ) { // next value is different
                occ += d;
                occCount = 0;
                val = poly(c, ++degree);
            }

        }

        cout << prev << endl;
    }

    if (argc > 1) {
        cin.rdbuf(backup);
    }

#ifndef DEBUG
    clog.clear();
#endif

    return 0;
}
