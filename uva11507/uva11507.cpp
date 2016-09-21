#include <cstdio>
#include <cmath>
#include <cstdlib>
#include <ctime>
#include <cstdarg>
#include <iostream>
#include <sstream>
#include <string>
#include <algorithm>
#include <regex>
#include <vector>
#include <map>
#include <unordered_map>
#include <set>
#include <unordered_set>

using namespace std;

#define loop(x, start, end) for (uint x = start; x < end; ++x)

#define INF 100000000
#define PI 2*acos(0.0)

typedef long long ll;

template<typename T>
using vec = vector<T>;

template<typename T>
using uset = unordered_set<T>;

template<typename K, typename V>
using umap = unordered_map<K, V>;


void log(vec<int> v) {
    loop(i, 0, v.size()) {
        fprintf(stderr, "%d ", v[i]);
    }
    fprintf(stderr, "\n");
}


void log(const char* format, ...) {
    va_list args;
    va_start(args, format);
    vfprintf(stderr, format, args);
    va_end(args);
}


// #define DEBUG

int main(int argc, char* argv[]) {

#ifndef DEBUG
    freopen("/dev/null", "w", stderr);
#endif

    if (argc > 1) { // input file
        freopen(argv[1], "r", stdin);
    }

    long L;
    while (1) {
        scanf("%ld", &L);
        if (L == 0)
            return 0;

        string dir = "+x";
        char b[3];
        for (long i = 0; i < L-1; i++) {
            scanf("%s", b);
            string d(b);

            string old = dir;
            if (d == "No") {
                log("no bend\n");
                continue;
            }
            if (d == "+z") {
                if (dir == "+x")
                    dir = "+z";
                else if (dir == "+z")
                    dir = "-x";
                else if (dir == "-x")
                    dir = "-z";
                else if (dir == "-z")
                    dir = "+x";
                else if (dir == "+y")
                    dir = "+y";
                else if (dir == "-y")
                    dir = "-y";
            }
            else if (d == "-z") {
                if (dir == "+z")
                    dir = "+x";
                else if (dir == "+x")
                    dir = "-z";
                else if (dir == "-z")
                    dir = "-x";
                else if (dir == "-x")
                    dir = "+z";
                else if (dir == "+y")
                    dir = "+y";
                else if (dir == "-y")
                    dir = "-y";
            }
            else if (d == "+y") {
                if (dir == "+y")
                    dir = "-x";
                else if (dir == "-x")
                    dir = "-y";
                else if (dir == "-y")
                    dir = "+x";
                else if (dir == "+x")
                    dir = "+y";
                else if (dir == "+z")
                    dir = "+z";
                else if (dir == "-z")
                    dir = "-z";
            }
            else if (d == "-y") {
                if (dir == "+x")
                    dir = "-y";
                else if (dir == "-y")
                    dir = "-x";
                else if (dir == "-x")
                    dir = "+y";
                else if (dir == "+y")
                    dir = "+x";
                else if (dir == "+z")
                    dir = "+z";
                else if (dir == "-z")
                    dir = "-z";
            }
            log("old = %s, new = %s\n", old.c_str(), dir.c_str());
        }
        printf("%s\n", dir.c_str());
    }

    return 0;
}
