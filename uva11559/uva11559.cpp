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

    int n, b, h, w, p, beds;
    while (scanf("%d %d %d %d", &n, &b, &h, &w) != EOF) {
        int cost = INF;
        log("%d %d %d %d\n", n, b, h, w);
        loop(i, 0, h) {
            scanf("%d", &p);
            log("%d\n", p);
            loop(j, 0, w) {
                scanf("%d", &beds);
                if (beds < n) {
                    continue;
                }
                if (n*p <= b && n*p < cost) {
                    cost = n*p;
                }
            }
        }
        if (cost < INF) {
            printf("%d\n", cost);
        }
        else {
            printf("stay home\n");
        }
    }

    return 0;
}
