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

class UnionFind {
    private:
        vec<int> p, rank, size;

    public:
        UnionFind(int N) {
            rank.assign(N, 0);
            size.assign(N, 1);
            p.assign(N, 0);
            loop(i, 0, N) {
                p[i] = i;
            }
        }

        int findSet(int i) {
            return (p[i] == i) ? i : (p[i] = findSet(p[i]));
        }

        int getSize(int i) {
            return (p[i] == i) ? size[i] : getSize(p[i]);
        }

        bool isSameSet(int i, int j) {
            return findSet(i) == findSet(j);
        }

        void unionSet(int i, int j) {
            if (!isSameSet(i, j)) { // if from different set
                int x = findSet(i), y = findSet(j);
                if (rank[x] > rank[y]) { // keep tree as short as possible
                    p[y] = x;
                    int sy = size[y];
                    int sx = size[x];
                    size[y] += sx;
                    size[x] += sy;
                }
                else { // rank[x] <= rank[y]
                    p[x] = y;
                    int sy = size[y];
                    int sx = size[x];
                    size[y] += sx;
                    size[x] += sy;
                    if (rank[x] == rank[y]) {
                        rank[y]++;
                    }
                }
            }
        }
};

// overload operator << for vectors of an arbitrary type
template <typename T>
ostream& operator<<(ostream &os, const vector<T> &vec)
{
    for (T n : vec)
        os << n << " ";
    return os;
}

// #define DEBUG

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

    int n, f, k;
    string a, b;

    cin >> n;
    loop(c, 0, n) {
        cin >> f;
        UnionFind uf(2*f);
        map<string, int> names;
        k = 0;
        loop(i, 0, f) {
            cin >> a >> b;
            if (names.find(a) == names.end()) {
                names[a] = k++;
            }
            if (names.find(b) == names.end()) {
                names[b] = k++;
            }
            uf.unionSet(names[a], names[b]);
            cout << uf.getSize(names[a]) << endl;
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
