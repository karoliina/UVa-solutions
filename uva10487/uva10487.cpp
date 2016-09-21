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

    int n, m, q, closest;
    int c = 1;

    cin >> n;
    while (n != 0) {
        vec<int> nums(n);
        loop(i, 0, n) {
            cin >> nums[i];
        }

        sort(nums.begin(), nums.end());

        printf("Case %d:\n", c);

        cin >> m;
        loop(query, 0, m) {
            cin >> q;
            closest = INF;

            loop(i, 0, n) {
                loop(j, i+1, n) {
                    int s = nums[i] + nums[j];
                    if (abs(s - q) < abs(closest - q)) {
                        closest = s;
                    }
                }
            }

            printf("Closest sum to %d is %d.\n", q, closest);
        }

        cin >> n;
        c++;
    }

    if (argc > 1) {
        cin.rdbuf(backup);
    }

#ifndef DEBUG
    clog.clear();
#endif

    return 0;
}
