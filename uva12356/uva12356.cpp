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

    // streambuf* backup;
    // streambuf* filebuf;

    if (argc > 1) { // input file
        // static ifstream fs(argv[1]);
        // if (!fs) {
        //     cout << "can't open file" << endl;
        //     exit(1);
        // }
        // backup = cin.rdbuf();
        // filebuf = fs.rdbuf();
        // cin.rdbuf(filebuf);
        freopen(argv[1], "r", stdin);
    }

    // START SOLUTION

    int s, b, l, r;
    while (true) {
        // cin >> s >> b;
        scanf("%d %d", &s, &b);
        if (s == 0 && b == 0)
            break;

        debug("s =", s, "b =", b);
        vec<int> left(s+1);
        vec<int> right(s+1);
        loop(i, 1, s+1) {
            left[i] = i-1;
            right[i] = i+1;
        }
        left[1] = -1;
        right[s] = -1;

        loop(i, 0, b) {
            // cin >> l >> r;
            scanf("%d %d", &l, &r);
            debug("l", l, "r", r);
            if (left[l] == -1)
                // cout << "* ";
                printf("* ");
            else
                // cout << left[l] << " ";
                printf("%d ", left[l]);
            if (right[r] == -1)
                // cout << "*" << endl;
                printf("*\n");
            else
                // cout << right[r] << endl;
                printf("%d\n", right[r]);

            // update buddies
            if (right[r] != -1)
                left[right[r]] = left[l];
            if (left[l] != -1)
                right[left[l]] = right[r];
            debug("new left buddy of", left[r], "is", left[l]);
            debug("new right buddy of", right[l], "is", right[r]);
        }
        // cout << "-" << endl;
        printf("-\n");
        // if (cin.eof())
        //     break;
    }

    // END SOLUTION

    // if (argc > 1) {
    //     cin.rdbuf(backup);
    // }

#ifndef DEBUG
    clog.clear();
#endif

    return 0;
}
