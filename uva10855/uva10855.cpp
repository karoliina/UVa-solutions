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

// debug() functions for an arbitrary number of arguments with arbitrary types
template <class T>
void debug(T t) {
    clog << t << endl;
}

template <class T, class... Args>
void debug(T t, Args... args)
{
    clog << t << " ";
    debug(args...);
}

// rotate arr clockwise by 90 degrees
void rotate(vec<vec<char> > &arr, int n) {
    vec<vec<char> > tmp(n);
    loop(i, 0, n) {
        tmp[i] = vec<char>(n);
    }

    int ti = 0;
    int tj = n-1;
    loop(i, 0, n) {
        loop(j, 0, n) {
            tmp[ti][tj] = arr[i][j];
            ti++;
        }
        ti = 0;
        tj--;
    }

    arr = tmp;
}

int count(vec<vec<char> > &big, vec<vec<char> > &small, int N, int n) {
    int count = 0;
    int si, sj;

    // check each possible top-left corner location of the smaller array
    loop(i, 0, N-n+1) {
        loop(j, 0, N-n+1) {
            bool found = true;
            si = 0;
            sj = 0;
            loop(bi, i, i+n) {
                loop(bj, j, j+n) {
                    if (big[bi][bj] != small[si][sj]) {
                        found = false;
                        break;
                    }
                    sj++;
                }
                if (!found)
                    break;
                sj = 0;
                si++;
            }
            if (found) {
                count++;
            }
        }
    }

    return count;
}

#define DEBUG

int main(int argc, char* argv[]) {

#ifndef DEBUG
    clog.setstate(ios_base::failbit);
#endif

    if (argc > 1) { // input file
        freopen(argv[1], "r", stdin);
    }

    // START SOLUTION

    int N, n;
    scanf("%d %d", &N, &n);

    while (N > 0 && n > 0) {
        vec<vec<char> > big(N, vec<char>(N+1));
        vec<vec<char> > small(n, vec<char>(n+1));

        loop(i, 0, N) {
            scanf("%s", &big[i][0]);
        }
        loop(i, 0, n) {
            scanf("%s", &small[i][0]);
        }

        printf("%d ", count(big, small, N, n));
        rotate(small, n);
        printf("%d ", count(big, small, N, n));
        rotate(small, n);
        printf("%d ", count(big, small, N, n));
        rotate(small, n);
        printf("%d\n", count(big, small, N, n));

        scanf("%d %d", &N, &n);
    }

#ifndef DEBUG
    clog.clear();
#endif

    return 0;
}
