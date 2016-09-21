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
#include <string>

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

vec<vec<int> > f(vec<vec<int> > &g) {
    vec<vec<int> > h(3, vec<int>(3, 0));
    loop(i, 0, 3) {
        loop(j, 0, 3) {
            int s = 0;
            if (i > 0)
                s += g[i-1][j];
            if (i < 2)
                s += g[i+1][j];
            if (j > 0)
                s += g[i][j-1];
            if (j < 2)
                s += g[i][j+1];
            h[i][j] = s % 2;
        }
    }
    return h;
}

bool allZero(vec<vec<int> > &g) {
    loop(i, 0, 3) {
        loop(j, 0, 3) {
            if (g[i][j] != 0)
                return false;
        }
    }
    return true;
}

#define DEBUG

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

    int n;
    cin >> n;
    cin.get();
    string line;
    getline(cin, line);
    loop(c, 0, n) {
        vec<vec<int> > g(3, vec<int>(3, 0));
        loop(i, 0, 3) {
            getline(cin, line);
            loop(j, 0, 3) {
                g[i][j] = line[j] - '0';
            }
        }
        getline(cin, line);

        // loop(i, 0, 3) {
        //     clog << g[i] << endl;
        // }
        // clog << endl;

        vec<vec<int> > h = g;

        int count = -1;
        while (!allZero(h)) {
            h = f(h);
            count++;
        }
        cout << count << endl;
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
