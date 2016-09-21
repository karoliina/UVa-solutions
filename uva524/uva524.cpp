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
#include <bitset>

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

bitset<32> eratosthenes() {
    bitset<32> bs;
    bs.set();

    int p = 2;
    while (p < 31) {
        for (int i = 2*p; i < 32; i += p) {
            bs.reset(i);
        }

        for (int i = p+1; i < 32; i++) {
            if (bs.test(i)) {
                p = i;
                break;
            }
        }
    }

    return bs;
}

vec<int> sol;
int n;
bitset<32> es;
vec<vec<int>> solutions;

void backtrack(int idx) {
    if (idx == n) {
        if (es.test(sol[n-1] + sol[0])) {
            solutions.push_back(sol);
        }
    }
    vec<bool> used(n, false);
    for (int i = 0; i < idx; i++) {
        used[sol[i]-1] = true;
    }
    for (int i = idx; i < n; i++) {
        sol[i] = 0;
    }
    for (int i = 1; i <= n; i++) {
        // debug("idx =", idx, "i =", i);
        // debug(sol);
        // debug(used);
        if (idx == 0 && i > 1) {
            break;
        }
        if (!used[i-1] && (idx == 0 || es.test(sol[idx-1] + i))) {
            sol[idx] = i;
            backtrack(idx+1);
        }
    }
}

int main(int argc, char* argv[]) {
    // max sum is 15+16 = 31 => create eratosthenes sieve up to 31
    es = eratosthenes(); // number x is prime, if es.test(x) returns true

    int tc = 1;
    while (true) {
        cin >> n;

        if (cin.eof()) {
            break;
        }


        sol = vec<int>(n, 0);
        solutions.clear();
        backtrack(0);

        if (tc > 1) {
            cout << endl;
        }
        cout << "Case " << tc++ << ":" << endl;
        for (int i = 0; i < solutions.size(); i++) {
            cout << solutions[i][0];
            for (int j = 1; j < solutions[i].size(); j++) {
                cout << " " << solutions[i][j];
            }
            cout << endl;
        }
    }


#ifndef DEBUG
    clog.clear();
#endif

    return 0;
}
