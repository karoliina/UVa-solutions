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

void log(string s) {
    clog << s << endl;
}

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

    int N;
    ll n, k;
    scanf("%d", &N);

    loop(i, 0, N) {
        scanf("%lld %lld", &n, &k);
        ll j = 0;
        while (j < n) {
            if (k & (1 << (j+1))) {
                k ^= (1 << j);
            }
            j++;
        }
        printf("%lld\n", k);
    }

    return 0;
}
