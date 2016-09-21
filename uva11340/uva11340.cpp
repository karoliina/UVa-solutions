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


#define DEBUG

int main(int argc, char* argv[]) {

#ifndef DEBUG
    freopen("/dev/null", "w", stderr);
#endif

    if (argc > 1) { // input file
        freopen(argv[1], "r", stdin);
    }

    int n, k, v, m;
    unsigned char c;
    scanf("%d\n", &n);
    loop(i, 0, n) {
        ll totalCents = 0;
        scanf("%d", &k);
        getchar();
        vec<int> values(256, 0);
        loop(j, 0, k) {
            c = getchar();
            scanf("%d", &v);
            getchar(); // newline
            values[c] = v;
        }
        scanf("%d\n", &m);
        loop(j, 0, m) {
            while ((c = getchar()) != '\n') {
                if ((int)c > 255) {
                    continue;
                }
                // log("total = %d, next = %d, char = %c, as int = %d\n", totalCents, values[line[l]],
                //         line[l], (int)line[l]);
                totalCents += values[c];
            }
        }
        ll dollars = totalCents / 100;
        ll cents = totalCents % 100;
        printf("%lld.%02lld$\n", dollars, cents);
        values.clear();
    }

    return 0;
}
