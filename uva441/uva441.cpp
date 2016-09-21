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

    int k;
    cin >> k;

    while (true) {
        if (k == 0) {
            break;
        }

        vec<int> S(k);
        loop(i, 0, k) {
            cin >> S[i];
        }

        for (int a = 0; a < k-5; a++) {
            for (int b = a+1; b < k-4; b++) {
                for (int c = b+1; c < k-3; c++) {
                    for (int d = c+1; d < k-2; d++) {
                        for (int e = d+1; e < k-1; e++) {
                            for (int f = e+1; f < k; f++) {
                                printf("%d %d %d %d %d %d\n", S[a], S[b], S[c], S[d], S[e], S[f]);
                            }
                        }
                    }
                }
            }
        }

        cin >> k;
        if (k == 0) {
            break;
        }

        printf("\n");
    }

    if (argc > 1) {
        cin.rdbuf(backup);
    }

#ifndef DEBUG
    clog.clear();
#endif

    return 0;
}
