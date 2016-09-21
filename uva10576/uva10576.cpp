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

vec<int> sol; // current solution
vec<vec<int>> solutions; // all valid solutions
int s, d;

bool checkPartials(int idx, int newVal) {
    // compute and check value of the partial sum ending at this index
    if (idx < 4) { // no partial sum is ending before index 4
        return true;
    }
    int psum = 0;
    for (int i = idx-4; i < idx; i++) {
        psum += sol[i];
    }
    return psum + newVal < 0;
}

void backtrack(int idx) {
    // debug("idx =", idx);
    // debug("sol =", sol);
    if (idx == 12) {
        solutions.push_back(sol);
        return;
    }
    // try both the surplus and deficit for this index
    if (checkPartials(idx, s)) {
        sol[idx] = s;
        backtrack(idx+1);
    }
    if (checkPartials(idx, d)) {
        sol[idx] = d;
        backtrack(idx+1);
    }
}

int main(int argc, char* argv[]) {
    while (true) {
        cin >> s >> d;
        if (cin.eof()) {
            break;
        }
        d *= -1;

        sol = vec<int>(12, 0);
        solutions.clear();

        backtrack(0);

        int surplus = 0;
        for (int i = 0; i < solutions.size(); i++) {
            // debug(solutions[i]);
            int total = 0;
            for (int j = 0; j < 12; j++) {
                total += solutions[i][j];
            }
            // debug("sum:", total);
            surplus = max(total, surplus);
        }
        if (surplus == 0) {
            cout << "Deficit" << endl;
        }
        else {
            cout << surplus << endl;
        }
    }

#ifndef DEBUG
    clog.clear();
#endif

    return 0;
}
