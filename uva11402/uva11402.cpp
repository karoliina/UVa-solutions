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

class Node {
    public:
        int buccaneer, barbary;

        Node(int buc, int bar) {
            buccaneer = buc;
            barbary = bar;
        }

        Node() {} // default constructor for resize()
};

class SegmentTree {
    private:
        vec<int> A; // original array
        vec<Node> st;
        vec<bool> lazyBuccaneer;
        vec<bool> lazyBarbary;
        vec<bool> lazyInvert;
        int n;

        const int BUCCANEER = 1;
        const int BARBARY = 2;
        const int INVERT = 3;

        int left(int p) {
            return p << 1;
        }

        int right(int p) {
            return (p << 1) + 1;
        }

        void build(int p, int L, int R) {
            if (L == R) {
                st[p] = Node(A[L], 1 - A[L]);
            }
            else {
                build(left(p), L, (L+R)/2);
                build(right(p), (L+R)/2 + 1, R);

                Node& s1 = st[left(p)], s2 = st[right(p)];
                st[p] = Node(s1.buccaneer + s2.buccaneer, s1.barbary + s2.barbary);
            }
        }

        void setLazy(int p, int type) {
            if (type == BUCCANEER) { // buccaneer overrides barbary and invert
                lazyBuccaneer[p] = true;
                lazyBarbary[p] = false;
                lazyInvert[p] = false;
            }
            else if (type == BARBARY) { // barbary overrides buccaneer and invert
                lazyBuccaneer[p] = false;
                lazyBarbary[p] = true;
                lazyInvert[p] = false;
            }
            else if (type == INVERT) { // invert does not override buccaneer or barbary!
                lazyInvert[p] = !lazyInvert[p];
            }
        }

        void updateLazy(int p, int L, int R) {
            int total = st[p].buccaneer + st[p].barbary;
            // carry out lazy updates, if any are pending
            if (lazyBuccaneer[p]) {
                // debug("L =", L, "R =", R, "- pending lazy buccaneer update: set to", total, "buccaneers");
                st[p].buccaneer = total;
                st[p].barbary = 0;
                if (L != R) {
                    setLazy(left(p), BUCCANEER);
                    setLazy(right(p), BUCCANEER);
                }
                lazyBuccaneer[p] = false;
            }
            else if (lazyBarbary[p]) {
                // debug("L =", L, "R =", R, "- pending lazy barbary update: set to", total, "barbaries");
                st[p].buccaneer = 0;
                st[p].barbary = total;
                if (L != R) {
                    setLazy(left(p), BARBARY);
                    setLazy(right(p), BARBARY);
                }
                lazyBarbary[p] = false;
            }
            if (lazyInvert[p]) {
                // debug("L =", L, "R =", R, "- pending lazy invert update: set to", st[p].barbary,
                //         "buccaneers and", st[p].buccaneer, "barbaries");
                int tmp = st[p].buccaneer;
                st[p].buccaneer = st[p].barbary;
                st[p].barbary = tmp;
                if (L != R) {
                    setLazy(left(p), INVERT);
                    setLazy(right(p), INVERT);
                }
                lazyInvert[p] = false;
            }
        }

        int buccaneers(int p, int L, int R, int i, int j) {
            // debug("QUERY: L =", L, "R =", R, "i =", i, "j =", j);
            if (i > R || j < L) {
                return -1;
            }

            updateLazy(p, L, R);

            if (i <= L && j >= R) {
                return st[p].buccaneer;
            }

            int s1 = buccaneers(left(p), L, (L+R)/2, i, j);
            int s2 = buccaneers(right(p), (L+R)/2 + 1, R, i, j);
            // debug("L =", L, "R =", R, "i =", i, "j =", j);
            // debug("left child:", s1, "buccaneers");
            // debug("right child:", s2, "buccaneers");

            if (s1 == -1) {
                return s2;
            }
            if (s2 == -1) {
                return s1;
            }

            return s1 + s2;
        }

        void update(int p, int L, int R, int i, int j, int val) {
            // debug("UPDATE: L =", L, "R =", R, "i =", i, "j =", j);
            updateLazy(p, L, R);

            // return if not within range of segment
            if (i > j || L > j || R < i) {
                return;
            }

            // update leaf node (end of recursion)
            if (L == R && i <= L && j >= R) {
                st[p].buccaneer = val;
                st[p].barbary = 1 - val;
                // debug("L = R =", L, "->", st[p].buccaneer, "buccaneers", st[p].barbary, "barbaries");
                return;
            }

            // lazy update if current node is completely contained in [i, j]
            if (i <= L && R <= j) {
                int total = st[p].buccaneer + st[p].barbary;
                if (val == 1) {
                    st[p].buccaneer = total;
                    st[p].barbary = 0;
                    setLazy(left(p), BUCCANEER);
                    setLazy(right(p), BUCCANEER);
                }
                else {
                    st[p].buccaneer = 0;
                    st[p].barbary = total;
                    setLazy(left(p), BARBARY);
                    setLazy(right(p), BARBARY);
                }
                return;
            }

            // update child nodes, if not leaf
            update(left(p), L, (L+R)/2, i, j, val);
            update(right(p), (L+R)/2+1, R, i, j, val);

            // update current (non-leaf) node after its children have updated
            if (L != R) {
                // debug("update current node: L =", L, "R =", R);
                Node& s1 = st[left(p)], s2 = st[right(p)];
                // debug("left child:", s1.buccaneer, "buccaneers,", s1.barbary, "barbaries");
                // debug("right child:", s2.buccaneer, "buccaneers,", s2.barbary, "barbaries");
                st[p].buccaneer = s1.buccaneer + s2.buccaneer;
                st[p].barbary = s1.barbary + s2.barbary;
                // debug("current node:", st[p].buccaneer, "buccaneers", st[p].barbary, "barbaries");
            }
        }

        void invert(int p, int L, int R, int i, int j) {
            // debug("INVERT: L =", L, "R =", R, "i =", i, "j =", j);
            updateLazy(p, L, R);

            // return if not within range of segment
            if (i > j || L > j || R < i) {
                return;
            }

            // invert leaf node (end of recursion)
            if (L == R && i <= L && j >= R) {
                st[p].buccaneer = !st[p].buccaneer;
                st[p].barbary = !st[p].barbary;
                // debug("L = R =", L, "->", st[p].buccaneer, "buccaneers", st[p].barbary, "barbaries");
                return;
            }

            // lazy invert if current node is completely contained in [i, j]
            if (i <= L && R <= j) {
                int tmp = st[p].buccaneer;
                st[p].buccaneer = st[p].barbary;
                st[p].barbary = tmp;
                setLazy(left(p), INVERT);
                setLazy(right(p), INVERT);
                return;
            }

            // invert child nodes, if not leaf
            invert(left(p), L, (L+R)/2, i, j);
            invert(right(p), (L+R)/2+1, R, i, j);

            // update current (non-leaf) node after its children have updated
            if (L != R) {
                Node& s1 = st[left(p)], s2 = st[right(p)];
                st[p].buccaneer = s1.buccaneer + s2.buccaneer;
                st[p].barbary = s1.barbary + s2.barbary;
                // debug("L =", L, "R =", R, "->", st[p].buccaneer, "buccaneers", st[p].barbary, "barbaries");
            }
        }

    public:
        SegmentTree(const vec<int> &_A) {
            A = _A;
            n = (int)A.size();
            st.resize(4*n);
            lazyBuccaneer.resize(4*n, false);
            lazyBarbary.resize(4*n, false);
            lazyInvert.resize(4*n, false);
            build(1, 0, n-1);
        }

        int buccaneers(int i, int j) {
            return buccaneers(1, 0, n-1, i, j);
        }

        void toBuccaneer(int i, int j) {
            return update(1, 0, n-1, i, j, 1);
        }

        void toBarbary(int i, int j) {
            return update(1, 0, n-1, i, j, 0);
        }

        void invert(int i, int j) {
            return invert(1, 0, n-1, i, j);
        }
};


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

    int cases, M, T, Q, a, b;
    char queryType;
    string s;

    cin >> cases;
    loop(c, 0, cases) {
        cout << "Case " << c+1 << ":" << endl;
        cin >> M;
        vec<int> A(1024000, 0);
        int k = 0;
        loop(p, 0, M) {
            cin >> T;
            getline(cin, s);
            getline(cin, s);
            loop(t, 0, T) {
                loop(i, 0, s.size()) {
                    A[k++] = s[i] - '0';
                }
            }
        }
        A.resize(k);
        SegmentTree st(A);

        cin >> Q;
        int numQueries = 0;
        loop(q, 0, Q) {
            cin >> queryType >> a >> b;

            switch(queryType) {
                case 'F':
                    // mutate to buccaneer
                    st.toBuccaneer(a, b);
                    break;
                case 'E':
                    // mutate to barbary
                    st.toBarbary(a, b);
                    break;
                case 'I':
                    // invert
                    st.invert(a, b);
                    break;
                case 'S':
                    // print number of buccaneers
                    cout << "Q" << ++numQueries << ": " << st.buccaneers(a, b) << endl;
                    break;
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
