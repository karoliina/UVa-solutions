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

    int h, u, d, f;
    while(1) {
        scanf("%d %d %d %d", &h, &u, &d, &f);
        if (h == 0)
            return 0;

        log("%d %d %d %d\n", h, u, d, f);
        double pos = 0;
        int day = 0;
        double fatigue = double(f)/100*u; // distance lost to fatigue each day
        log("fatigue = %.4lf\n", fatigue);
        while (pos >= 0.0 && pos <= h) {
            if (u - day*fatigue >= 0) {
                pos += u - day*fatigue;
            }
            day++;
            if (pos > h) {
                log("pos = %.4lf\n", pos);
                break;
            }
            pos -= d;
            log("after day %d: pos = %.4lf\n", day, pos);
        }
        if (pos > h) {
            printf("success on day %d\n", day);
        }
        else {
            printf("failure on day %d\n", day);
        }
    }

    return 0;
}
