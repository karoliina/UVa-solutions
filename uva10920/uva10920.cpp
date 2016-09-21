#include <cstdio>
#include <cmath>
#include <cstdlib>
#include <ctime>
#include <climits>
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

    ll sz, p;
    cin >> sz >> p;
    while (sz > 0 && p > 0) {
        ll k = ceil(sqrt(p));
        if (k % 2 == 0) {
            k++;
        }

        ll c = ll(pow(k, 2)); // current spiral coordinate
        ll i = ll((sz-k)/2);
        ll j = sz - 1 - ll((sz-k)/2);

        int dir = 2; // 0 = up, 1 = left, 2 = down, 3 = right
        int dirCount = 0;
        int maxDirCount = k-1;
        while (c > p) {
            if (dirCount == maxDirCount) {
                dirCount = 0;
                if (dir == 0) {
                    dir = 3;
                    maxDirCount = k-2;
                }
                else if (dir == 1 || dir == 2 || dir == 3) {
                    dir--;
                    maxDirCount = k-1;
                }
            }
            if (dir == 0) {
                i--;
            }
            else if (dir == 1) {
                j--;
            }
            else if (dir == 2) {
                i++;
            }
            else if (dir == 3) {
                j++;
            }
            c--;
            dirCount++;
        }

        // cout << "Line = " << sz - i << ", column = " << j+1 << "." << endl;
        printf("Line = %lld, column = %lld.\n", sz-i, j+1);
        cin >> sz >> p;

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
