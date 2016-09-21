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
#include <queue>

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

int gcd_inner(int a, int b) {
    return b == 0 ? a : gcd_inner(b, a % b);
}

int gcd(vec<int> vals) {
    if (vals.size() < 1) {
        return 0;
    }
    if (vals.size() < 2) {
        return vals[0];
    }
    int res = vals[0];
    for (int i = 1; i < vals.size(); i++) {
        res = gcd_inner(res, vals[i]);
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

    priority_queue<vec<int> > queries;
    string s;
    int query, f, k;

    while (cin >> s) {
        if (s == "#") {
            break;
        }
        cin >> query >> f;
        queries.push(vec<int>({-f, -query, -f})); // next return time, ID, frequency
    }

    cin >> k;
    loop(i, 0, k) {
        auto v = queries.top();
        queries.pop();
        cout << -v[1] << endl;
        queries.push(vec<int>({v[0] += v[2], v[1], v[2]}));
    }

    if (argc > 1) {
        cin.rdbuf(backup);
    }

#ifndef DEBUG
    clog.clear();
#endif

    return 0;
}
