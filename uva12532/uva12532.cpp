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

int sign(int x) {
    return (x > 0) - (x < 0);
}

class SegmentTree {
    private:
        vec<int> st, A;
        int n;

        int left(int p) {
            return p << 1;
        }

        int right(int p) {
            return (p << 1) + 1;
        }

        void build(int p, int L, int R) {
            if (L == R) {
                st[p] = sign(A[L]);
            }
            else {
                build(left(p), L, (L+R)/2);
                build(right(p), (L+R)/2 + 1, R);
                int s1 = st[left(p)], s2 = st[right(p)];
                if (s1 == 1 && s2 == 1) {
                    st[p] = s1;
                }
                else if (s1 == 0 || s2 == 0) {
                    st[p] = 0;
                }
                else if (s1 == -1 && s2 == -1) {
                    st[p] = 1;
                }
                else if (s1 == -1 || s2 == -1) {
                    st[p] = -1;
                }
                else {
                    st[p] = 1;
                }
            }
            // debug("build: p", p, "L", L, "R", R, "st[p]", st[p]);
        }

        int query(int p, int L, int R, int i, int j) {
            if (i > R || j < L) {
                return INF;
            }
            if (i <= L && j >= R) {
                return st[p];
            }

            int s1 = query(left(p), L, (L+R)/2, i, j);
            int s2 = query(right(p), (L+R)/2 + 1, R, i, j);
            int res;

            if (s1 == INF) {
                res = s2;
            }
            else if (s2 == INF) {
                res = s1;
            }

            else if (s1 == 1 && s2 == 1) {
                res = s1;
            }
            else if (s1 == 0 || s2 == 0) {
                res = 0;
            }
            else if (s1 == -1 && s2 == -1) {
                res = 1;
            }
            else if (s1 == -1 || s2 == -1) {
                res = -1;
            }
            else {
                res = 1;
            }

            return res;
        }

        void update(int p, int L, int R, int i, int val) {
            int oldVal = INF, newVal = INF;
            // update child nodes, if not leaf
            if (i >= L && i <= (L+R)/2 && L != R) {
                oldVal = st[left(p)];
                update(left(p), L, (L+R)/2, i, val);
                newVal = st[left(p)];
            }
            else if (i >= (L+R)/2 + 1 && i <= R && L != R) {
                oldVal = st[right(p)];
                update(right(p), (L+R)/2+1, R, i, val);
                newVal = st[right(p)];
            }
            else { // leaf node
                oldVal = st[p];
                st[p] = sign(val);
                newVal = st[p];
            }
            // debug("update: p", p, "L", L, "R", R, "i", i, "val", val);
            // update current (non-leaf) node
            if (L != R && oldVal != newVal) {
                int s1 = st[left(p)], s2 = st[right(p)];
                // debug("left child", s1, "right child", s2);
                if (s1 == 1 && s2 == 1) {
                    st[p] = s1;
                }
                else if (s1 == 0 || s2 == 0) {
                    st[p] = 0;
                }
                else if (s1 == -1 && s2 == -1) {
                    st[p] = 1;
                }
                else if (s1 == -1 || s2 == -1) {
                    st[p] = -1;
                }
                else {
                    st[p] = 1;
                }
            }
            // debug("new value:", st[p]);
        }

    public:
        SegmentTree(const vec<int> &_A) {
            A = _A;
            n = (int)A.size();
            st.assign(4*n, 0);
            build(1, 0, n-1);
        }

        int query(int i, int j) {
            return query(1, 0, n-1, i, j);
        }

        void update(int i, int val) {
            A[i] = val;
            return update(1, 0, n-1, i, val);
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

    int n, k, i, j;
    char command;

    while (true) {
        cin >> n;
        if (cin.eof()) {
            break;
        }

        vec<int> x(n, 0);
        cin >> k;

        loop(c, 0, n) {
            cin >> x[c];
        }

        SegmentTree st(x);

        string result = "";
        loop(c, 0, k) {
            cin >> command >> i >> j;
            // debug(command, i, j);
            if (command == 'C') {
                st.update(i-1, j);
            }
            else if (command == 'P') {
                int res = st.query(i-1, j-1);
                if (res == 1) {
                    result += '+';
                }
                else if (res == -1) {
                    result += '-';
                }
                else {
                    result += '0';
                }
            }
        }
        cout << result << endl;

    }




    if (argc > 1) {
        cin.rdbuf(backup);
    }

#ifndef DEBUG
    clog.clear();
#endif

    return 0;
}
