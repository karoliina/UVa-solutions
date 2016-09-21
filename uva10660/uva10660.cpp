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

    int t, n;
    cin >> t;

    loop(testcase, 0, t) {
        cin >> n;
        vec<vec<int> > people(n);
        loop(i, 0, n) {
            people[i] = vec<int>(3);
            cin >> people[i][0] >> people[i][1] >> people[i][2];
        }

        int minDist = INF;
        int dist;
        int da, db, dc, dd, de;
        int ma, mb, mc, md, me;
        int limit = 25;
        for (int a = 0; a < limit; a++) { // loop over office locations
            for (int b = a+1; b < limit; b++) {
                for (int c = b+1; c < limit; c++) {
                    for (int d = c+1; d < limit; d++) {
                        for (int e = d+1; e < limit; e++) {
                            dist = 0;
                            for (int sq = 0; sq < n; sq++) { // loop over squares with people
                                // for the current square, find the office with the minimum distance
                                // among the current locations a to e, and add the corresponding distance to
                                // the total
                                int x = people[sq][0];
                                int y = people[sq][1];
                                int pop = people[sq][2];
                                da = (abs(y - a % 5) + abs(x - a/5)) * pop;
                                db = (abs(y - b % 5) + abs(x - b/5)) * pop;
                                dc = (abs(y - c % 5) + abs(x - c/5)) * pop;
                                dd = (abs(y - d % 5) + abs(x - d/5)) * pop;
                                de = (abs(y - e % 5) + abs(x - e/5)) * pop;

                                int closestDist = da;
                                closestDist = min(closestDist, db);
                                closestDist = min(closestDist, dc);
                                closestDist = min(closestDist, dd);
                                closestDist = min(closestDist, de);
                                dist += closestDist;
                            }
                            // check if total distance for this combination of locations is minimum
                            if (dist < minDist || (dist == minDist && a < ma)) {
                                minDist = dist;
                                ma = a;
                                mb = b;
                                mc = c;
                                md = d;
                                me = e;
                            }
                        }
                    }
                }
            }
        }

        printf("%d %d %d %d %d\n", ma, mb, mc, md, me);
    }

    if (argc > 1) {
        cin.rdbuf(backup);
    }

#ifndef DEBUG
    clog.clear();
#endif

    return 0;
}
