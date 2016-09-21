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
#define all(x) x.begin(), x.end()
#define uniq(c) (c).resize(unique(ALL(c)) - (c).begin())

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

template<typename T>
void log(vec<T> v) {
    loop(i, 0, v.size()) {
        clog << v[i] << " ";
    }
    clog << endl;
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

    int n, prev, curr;
    while (scanf("%d", &n) != EOF) {
        int count = 0;
        vec<bool> found(n-1, false);
        scanf("%d", &prev);
        loop(i, 0, n-1) {
            scanf("%d", &curr);
            int diff = abs(curr - prev);
            log("prev = %d, curr = %d, diff = %d\n", prev, curr, diff);
            log(found);
            if (diff > 0 && diff < n && !found[diff - 1]) {
                found[diff - 1] = true;
                count++;
            }
            prev = curr;
        }
        if (count == n-1)
            printf("Jolly\n");
        else
            printf("Not jolly\n");

        char c = getc(stdin);
        if (c == EOF)
            break;
    }


    return 0;
}
