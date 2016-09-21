#include <cstdio>
#include <cmath>
#include <cstdlib>
#include <iostream>
#include <sstream>
#include <string>
#include <algorithm>
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

template <typename T>
ostream& operator<<(ostream &os, const set<T> &vec)
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

int n, k, maxBlack;
vec<vec<int>> adj;
vec<int> sol;

// color: 0 = white, 1 = black
void backtrack(int idx, int v, int color, int nBlack, vec<int> colors, set<int> visited) {
    debug("idx =", idx, "v =", v, "color =", color, "nBlack =", nBlack);
    debug(colors);
    debug(visited);
    if (visited.size() == n) {
        if (nBlack > maxBlack) {
            sol = vec<int>();
            // new best solution
            loop(i, 0, n) {
                if (colors[i] == 1) {
                    sol.push_back(i);
                }
            }
        }
        colors = vec<int>(n, 0);
        maxBlack = max(nBlack, maxBlack);
        return;
    }
    int nextColor = color == 0 ? 1 : 0;
    for (int i = 0; i < adj[v].size(); i++) {
        debug("next:", adj[v][i]);
        colors[adj[v][i]] = nextColor;
        visited.insert(adj[v][i]);
        backtrack(idx+1, adj[v][i], nextColor, nBlack + nextColor, colors, visited);
    }
}

int main(int argc, char* argv[]) {
    int m, a, b;
    cin >> m;

    loop(tc, 0, m) {
        cin >> n >> k;
        adj = vec<vec<int>>(n, vec<int>());
        loop(edge, 0, k) {
            cin >> a >> b;
            adj[a-1].push_back(b-1);
        }

        set<int> visited;
        visited.insert(0);
        backtrack(0, 0, 0, 0, vec<int>(n, 0), visited);
        vec<int> colors = vec<int>(n, 0);
        colors[0] = 1;
        visited.clear();
        visited.insert(0);
        maxBlack = 0;
        backtrack(0, 0, 1, 0, colors, visited);
        debug(maxBlack);
        debug(sol);
    }

    /*
    backtracking:
    start from vertex 0, coloring it both white and black
    recurse on each of its neighboring vertices with the opposite color
    continue until all vertices are colored, counting the number of black vertices

    TODO should be like DFS?
   */

#ifndef DEBUG
    clog.clear();
#endif

    return 0;
}
