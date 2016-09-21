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

#define loop(x, start, end) for (int x = start; x < end; ++x)

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

    int M;
    string s;
    while (true) {
        cin >> M;
        getline(cin, s);

        if (cin.eof()) {
            break;
        }

        vec<vec<int> > A(M);
        loop(i, 0, M) {
            A[i] = vec<int>(M);
            getline(cin, s);
            loop(j, 0, M) {
                A[i][j] = s[j] - '0';
            }
        }

        int maxOfMins = 0;
        loop(i, 0, M) {
            loop(j, 0, M) {
                if (A[i][j] == 1) {
                    int minSteps = INF;
                    loop(x, 0, M) {
                        loop(y, 0, M) {
                            if (A[x][y] == 3) {
                                minSteps = min(abs(x-i) + abs(y-j), minSteps);
                            }
                        }
                    }
                    maxOfMins = max(minSteps, maxOfMins);
                }
            }
        }
        cout << maxOfMins << endl;
    }

    if (argc > 1) {
        cin.rdbuf(backup);
    }

#ifndef DEBUG
    clog.clear();
#endif

    return 0;
}
