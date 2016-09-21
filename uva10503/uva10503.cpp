#include <cstdio>
#include <cmath>
#include <cstdlib>
#include <iostream>
#include <sstream>
#include <string>
#include <algorithm>
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

template <typename T>
ostream& operator<<(ostream &os, const pair<T, T> &p) {
    os << "(" << p.first << "," << p.second << ")";
    return os;
}

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

int n, m;
vec<pair<int, int>> pieces; // pieces 0 and 1 are the first and last ones
vec<int> sol; // vector of indexes into the pieces vector
vec<bool> used;
bool found;

void debugSol() {
    loop(i, 0, n+2) {
        clog << pieces[sol[i]] << " ";
    }
    clog << endl;
}

void debugPieces() {
    loop(i, 3, m+3) {
        clog << pieces[i];
        if (used[i]) {
            clog << "X";
        }
        clog << " ";
    }
    clog << endl;
}

void backtrack(int idx) {
    if (idx == n+1) {
        if (pieces[sol[idx-1]].second == pieces[sol[idx]].first) {
            found = true;
        }
        return;
    }
    // try each of the available pieces for this space
    for (int i = 3; i < m+3; i++) {
        if (!used[i]) {
            bool flipped = false;
            if (pieces[sol[idx-1]].second == pieces[i].first) {
                sol[idx] = i;
                used[i] = true;
                backtrack(idx+1);
            }
            else if (pieces[sol[idx-1]].second == pieces[i].second) {
                // flip the piece
                pieces[i] = make_pair(pieces[i].second, pieces[i].first);
                sol[idx] = i;
                used[i] = true;
                flipped = true;
                backtrack(idx+1);
            }
            // reset the used bits
            for (int j = idx; j < n+1; j++) {
                used[sol[j]] = false;
                sol[j] = 0;
            }
            // un-flip the piece
            if (flipped) {
                pieces[i] = make_pair(pieces[i].second, pieces[i].first);
            }
        }
    }
}

int main(int argc, char* argv[]) {

    while (true) {
        cin >> n;
        if (n == 0) {
            break;
        }
        cin >> m;
        sol = vec<int>(n+2);
        pieces = vec<pair<int, int>>(m+3);
        int a, b;

        pieces[0] = make_pair(-1, -1);
        cin >> a >> b;
        pieces[1] = make_pair(a, b);
        cin >> a >> b;
        pieces[2] = make_pair(a, b);
        sol[0] = 1;
        sol[n+1] = 2;

        loop(i, 3, m+3) {
            cin >> a >> b;
            pieces[i] = make_pair(a, b);
        }

        found = false;
        used = vec<bool>(m+3, false);
        backtrack(1);
        if (found) {
            cout << "YES" << endl;
        }
        else {
            cout << "NO" << endl;
        }
    }


#ifndef DEBUG
    clog.clear();
#endif

    return 0;
}
