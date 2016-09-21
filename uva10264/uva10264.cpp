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
    while (true) {
        cin >> n;
        if (cin.eof())
            break;

        int N = pow(2,n); // # of corners
        vec<int> weight(N, 0);
        loop(i, 0, N) {
            cin >> weight[i];
        }

        vec<int> potency(N, 0);
        // for each corner, flip each bit once - the resulting number is a neighbouring corner
        loop(x, 0, N) {
            loop(i, 0, n) {
                int y = x ^ (1 << i);
                potency[x] += weight[y];
            }
        }

        int maxsum = 0;
        // loop over neighbours again to find max sum of potencies
        loop(x, 0, N) {
            loop(i, 0, n) {
                int y = x ^ (1 << i);
                maxsum = max(maxsum, potency[x] + potency[y]);
            }
        }

        cout << maxsum << endl;

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
