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

ostream& operator<<(ostream &os, const vector<int> &vec)
{
    for(int n: vec)
        os << n << " ";
    return os;
}

#define DEBUG

int main(int argc, char* argv[]) {

#ifndef DEBUG
    clog.setstate(ios_base::failbit);
#endif

    if (argc > 1) { // input file
        freopen(argv[1], "r", stdin);
    }

    uint t;
    scanf("%d", &t);
    loop(i, 0, t) {
        int a, b, c;
        scanf("%d %d %d", &a, &b, &c);
        if ((a < b && b < c) || (c < b && b < a))
            printf("Case %d: %d\n", i+1, b);
        else if ((b < a && a < c) || (c < a && a < b))
            printf("Case %d: %d\n", i+1, a);
        else
            printf("Case %d: %d\n", i+1, c);
    }

#ifndef DEBUG
    clog.clear();
#endif

    return 0;
}
