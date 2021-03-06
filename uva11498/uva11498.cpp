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

    uint k;
    while (scanf("%d", &k) != EOF) {
        if (k == 0)
            break;

        int n, m, x, y;
        scanf("%d %d", &n, &m);
        loop(i, 0, k) {
            scanf("%d %d", &x, &y);
            if (x == n || y == m)
                puts("divisa");
            else if (x < n) {
                y < m ? puts("SO") : puts("NO");
            }
            else if (x > n) {
                y < m ? puts("SE") : puts("NE");
            }
        }
    }

    if (argc > 1) {
        cin.rdbuf(backup);
    }

#ifndef DEBUG
    clog.clear();
#endif

    return 0;
}
