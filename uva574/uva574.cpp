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

int n, t;
set<vec<int>> solutions;
vec<int> nums;
vec<int> sol;

void backtrack(int idx, int partial) {
    // debug("idx =", idx, "partial =", partial, "sol =", sol);
    if (partial == t) {
        solutions.insert(sol);
        return;
    }
    for (int i = idx; i < n; i++) {
        if (partial + nums[i] <= t) {
            sol.push_back(nums[i]);
            backtrack(i+1, partial + nums[i]);
            sol.pop_back();
        }
    }
}

int main(int argc, char* argv[]) {

    while (true) {
        cin >> t >> n;
        if (t == 0 && n == 0) {
            break;
        }

        nums = vec<int>(n, 0);
        loop(i, 0, n) {
            cin >> nums[i];
        }

        solutions.clear();
        sol.clear();
        backtrack(0, 0);

        cout << "Sums of " << t << ":" << endl;
        if (solutions.size() > 0) {
            for (auto it = solutions.rbegin(); it != solutions.rend(); it++) {
                vec<int> s = *it;
                cout << s[0];
                for (int j = 1; j < s.size(); j++) {
                    cout << "+" << s[j];
                }
                cout << endl;
            }
        }
        else {
            cout << "NONE" << endl;
        }
    }


#ifndef DEBUG
    clog.clear();
#endif

    return 0;
}
