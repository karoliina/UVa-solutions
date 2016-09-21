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

ostream& operator<<(ostream &os, const map<int, int> &m)
{
    for (auto it : m)
        os << it.first << "->" << it.second << endl;
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
        int lf, lv, rf, rv, mf;
        Node(int lFreq, int lVal, int rFreq, int rVal, int maxFreq) {
            lf = lFreq;
            lv = lVal;
            rf = rFreq;
            rv = rVal;
            mf = maxFreq;
        }

        Node() {}

        Node(int maxFreq) {
            mf = maxFreq;
        }
};

class SegmentTree {
    private:
        // original array
        vec<int> A;
        vec<Node> st;
        int n;

        int left (int p) {
            return p << 1;
        }

        int right (int p) {
            return (p << 1) + 1;
        }

        void build (int p, int L, int R) {
            if (L == R) {
                st[p] = Node(1, A[L], 1, A[L], 1);
                // debug("BUILD L", L, "R", R);
                // debug("left", A[L], "->", 1);
                // debug("right", A[L], "->", 1);
                // debug("max", 1);
            }
            else {
                build(left(p), L, (L+R)/2);
                build(right(p), (L+R)/2+1, R);

                Node p1 = st[left(p)], p2 = st[right(p)];
                if (p1.lv == p2.rv) { // only one value within segment
                    int freq = p1.lf + p2.rf;
                    st[p] = Node(freq, p1.lv, freq, p1.rv, freq);
                }
                else { // two or more different values within segment
                    int lf = p1.lf, lv = p1.lv, rf = p2.rf, rv = p2.rv;
                    int sumf = 0;
                    if (p1.rv == p2.lv) {
                        // debug("p1 right == p2.left");
                        if (p1.lv == p1.rv) {
                            lf += p2.lf;
                        }
                        if (p2.lv == p2.rv) {
                            rf += p1.rf;
                        }
                        sumf = p1.rf + p2.lf;
                        // debug("got lf =", lf, "rf =", rf, "mf =", mf);
                    }
                    int maxMax = max(p1.mf, p2.mf);
                    int maxLeft = max(p1.lf, p1.rf);
                    int maxRight = max(p2.lf, p2.rf);
                    int mf = max(sumf, max(maxMax, max(maxLeft, maxRight)));
                    st[p] = Node(lf, lv, rf, rv, mf);
                }
                // debug("BUILD L", L, "R", R);
                // debug("left", st[p].lv, "->", st[p].lf);
                // debug("right", st[p].rv, "->", st[p].rf);
                // debug("max", st[p].mf);
            }
        }

        Node rmq(int p, int L, int R, int i, int j) {
            Node res;
            if (i > R || j < L) { // current segment outside query range
                res = Node(-1);
            }
            else if (i <= L && j >= R) { // current segment fully inside query range
                res = st[p];
            }

            else if (j <= (L+R)/2) {
                res = rmq(left(p), L, (L+R)/2, i, j);
            }
            else if (i >= (L+R)/2 + 1) {
                res = rmq(right(p), (L+R)/2 + 1, R, i, j);
            }
            else {
                // combine left and right results
                Node p1 = rmq(left(p), L, (L+R)/2, i, j);
                Node p2 = rmq(right(p), (L+R)/2 + 1, R, i, j);

                if (p1.lv == p2.rv) {
                    int freq = p1.lf + p2.rf;
                    res = Node(freq, p1.lv, freq, p1.rv, freq);
                }
                else { // two or more different values within segment
                    int lf = p1.lf, lv = p1.lv, rf = p2.rf, rv = p2.rv;
                    int sumf = 0;
                    if (p1.rv == p2.lv) {
                        // debug("p1 right == p2.left");
                        if (p1.lv == p1.rv) {
                            lf += p2.lf;
                        }
                        if (p2.lv == p2.rv) {
                            rf += p1.rf;
                        }
                        sumf = p1.rf + p2.lf;
                        // debug("got lf =", lf, "rf =", rf, "mf =", mf);
                    }
                    int maxMax = max(p1.mf, p2.mf);
                    int maxLeft = max(p1.lf, p1.rf);
                    int maxRight = max(p2.lf, p2.rf);
                    int mf = max(sumf, max(maxMax, max(maxLeft, maxRight)));
                    res = Node(lf, lv, rf, rv, mf);
                }
            }
            // debug("L", L, "R", R, "i", i, "j", j);
            // debug("left", res.lv, "->", res.lf);
            // debug("right", res.rv, "->", res.rf);
            // debug("max", res.mf);
            return res;
        }

    public:
        SegmentTree(const vec<int> &_A) {
            A = _A;
            n = (int)A.size();
            st.resize(4*n);
            build(1, 0, n-1);
            // debug("");
        }

        int rmq(int i, int j) {
            if (A[i] == A[j]) {
                return j - i + 1;
            }
            Node res = rmq(1, 0, n-1, i, j);
            return res.mf;
        }
};


int main(int argc, char* argv[]) {
    if (argc > 1) {
        freopen(argv[1], "r", stdin);
    }

    int n, q, i, j;

    while (true) {
        scanf("%d", &n);
        if (n == 0) {
           break;
        }
        scanf("%d", &q);
        vec<int> A(n, 0);
        loop(c, 0, n) {
            scanf("%d", &A[c]);
        }

        SegmentTree st(A);

        loop(c, 0, q) {
            scanf("%d %d", &i, &j);
            printf("%d\n", st.rmq(i-1, j-1));
        }
    }

#ifndef DEBUG
    clog.clear();
#endif

    return 0;
}
