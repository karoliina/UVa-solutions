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

class SegmentTree {
    private:
        // original array
        vec<int> A;
        // heap of maps from values to occurrences
        vec<map<int, int> > st;
        vec<int> maxfreq; // maximum frequency for each segment
        int n;

        int left (int p) {
            return p << 1;
        }

        int right (int p) {
            return (p << 1) + 1;
        }

        void build (int p, int L, int R) {
            // debug("building segment", p, L, R);
            if (L == R) {
                map<int, int> tmp;
                tmp[A[L]] = 1;
                st[p] = tmp;
                maxfreq[p] = 1;
            }
            else {
                build(left(p), L, (L+R)/2);
                build(right(p), (L+R)/2+1, R);

                map<int, int> m1 = st[left(p)], m2 = st[right(p)];
                map<int, int> tmp;
                int mf = 0;

                // debug("left:");
                // debug(m1);
                // debug("right:");
                // debug(m2);
                for (auto it = m1.begin(); it != m1.end(); it++) {
                    tmp[it->first] = it->second;
                    mf = max(mf, it->second);
                }
                for (auto it = m2.begin(); it != m2.end(); it++) {
                    if (tmp.find(it->first) != tmp.end()) {
                        tmp[it->first] += it->second;
                        mf = max(mf, tmp[it->first]);
                    }
                    else {
                        tmp[it->first] = it->second;
                        mf = max(mf, it->second);
                    }
                }

                st[p] = tmp;
                maxfreq[p] = mf;
                // debug("range", L, R, "maxfreq", mf);
                // debug(tmp);
            }
        }

        // returns a pair of the maximum frequency and the map of values to their frequencies within the
        // interval [i, j]
        pair<int, map<int, int> > rmq(int p, int L, int R, int i, int j) {
            map<int, int> tmp;
            int mf = 0;

            if (i > R || j < L) { // current segment outside query range
                return make_pair(-1, tmp);
            }
            if (i <= L && j >= R) { // inside query range
                return make_pair(maxfreq[p], st[p]);
            }

            if (j <= (L+R)/2) {
                return rmq(left(p), L, (L+R)/2, i, j);
            }
            else if (i >= (L+R)/2 + 1) {
                return rmq(right(p), (L+R)/2 + 1, R, i, j);
            }
            else {
                // combine left and right results
                pair<int, map<int, int> > mf1 = rmq(left(p), L, (L+R)/2, i, j);
                pair<int, map<int, int> > mf2 = rmq(right(p), (L+R)/2 + 1, R, i, j);

                map<int, int> vals1 = mf1.second;
                map<int, int> vals2 = mf2.second;
                for (auto it = vals1.begin(); it != vals1.end(); it++) {
                    tmp[it->first] = it->second;
                    mf = max(mf, it->second);
                }
                for (auto it = vals2.begin(); it != vals2.end(); it++) {
                    if (tmp.find(it->first) != tmp.end()) {
                        tmp[it->first] += it->second;
                        mf = max(mf, tmp[it->first]);
                    }
                    else {
                        tmp[it->first] = it->second;
                        mf = max(mf, it->second);
                    }
                }

                return make_pair(mf, tmp);
            }
        }

    public:
        SegmentTree(const vec<int> &_A) {
            A = _A;
            n = (int)A.size();
            st.resize(4*n);
            maxfreq.resize(4*n);
            build(1, 0, n-1);
        }

        int rmq(int i, int j) {
            pair<int, map<int, int> > res = rmq(1, 0, n-1, i, j);
            return res.first;
        }
};


int main(int argc, char* argv[]) {
    // streambuf* backup;
    // streambuf* filebuf;
    //
    // if (argc > 1) { // input file
    //     static ifstream fs(argv[1]);
    //     if (!fs) {
    //         cout << "can't open file" << endl;
    //         exit(1);
    //     }
    //     backup = cin.rdbuf();
    //     filebuf = fs.rdbuf();
    //     cin.rdbuf(filebuf);
    // }

    if (argc > 1) {
        freopen(argv[1], "r", stdin);
    }

    int n, q, i, j;

    while (true) {
        // cin >> n;
        scanf("%d", &n);
        if (n == 0) {
           break;
        }
        // cin >> q;
        scanf("%d", &q);
        vec<int> A(n, 0);
        loop(c, 0, n) {
            // cin >> A[c];
            scanf("%d", &A[c]);
        }

        SegmentTree st(A);

        loop(c, 0, q) {
            // cin >> i >> j;
            // cout << st.rmq(i-1, j-1) << endl;
            scanf("%d %d", &i, &j);
            printf("%d\n", st.rmq(i-1, j-1));
        }
    }

    // if (argc > 1) {
    //     cin.rdbuf(backup);
    // }

#ifndef DEBUG
    clog.clear();
#endif

    return 0;
}
