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
    int s = vec.size();
    int k = 0;
    for (T n : vec) {
        os << n;
        if (k++ < s-1) {
           os << " ";
        }
    }
    return os;
}

template <typename T>
ostream& operator<<(ostream &os, const set<T> &vec)
{
    int s = vec.size();
    int k = 0;
    for (T n : vec) {
        os << n;
        if (k++ < s-1) {
           os << " ";
        }
    }
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

int fact(int n) {
    return (n == 1 || n == 0) ? 1 : n*fact(n-1);
}

int nCombinations(int n, int r) {
    return int(fact(n)/double(fact(r)*fact(n-r)));
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

    int n, nt, m, t;
    int testcase = 1;

    while (true) {
        cin >> n >> nt;
        if (n == 0) {
            break;
        }
        vec<int> towers(n); // # of customers served by the tower
        loop(i, 0, n) {
            cin >> towers[i];
        }
        cin >> m;
        vec<pair<set<int>, int> > common(m);
        loop(i, 0, m) {
            cin >> t;
            set<int> s;
            int tmp;
            loop(j, 0, t) {
                cin >> tmp;
                s.insert(tmp);
            }
            cin >> tmp;
            common[i] = make_pair(s, tmp);
        }

        int nc = pow(2, n); // # of combinations

        int maxCust = 0;
        vec<int> recommended;
        loop(i, 1, nc) {
            vec<int> inclTowers(nt, -1);
            int k = 0;
            int cust = 0;
            loop(j, 0, n) { // check if tower j is included
                if (k >= nt) {
                    break;
                }
                if ((i & (1 << j)) != 0) {
                    inclTowers[k++] = j+1;
                    cust += towers[j];
                }
            }
            if (k != nt) {
                continue;
            }
            else {
                // debug("included:", inclTowers, "with", cust, "customers");
                loop(cc, 0, m) {
                    set<int> coverages = common[cc].first;
                    int covered = common[cc].second;
                    // set<int> intersect;
                    // insert_iterator<set<int> > insertIt(intersect, intersect.begin());
                    // set_intersection(coverages.begin(), coverages.end(), inclTowers.begin(),
                    //             inclTowers.end(), insertIt);
                    // debug("intersection:", intersect);
                    // int ss = intersect.size();

                    int ss = 0;
                    for (int j = 0; j < nt; j++) {
                        if (coverages.find(inclTowers[j]) != coverages.end()) {
                            ss++;
                        }
                    }
                    if (ss > 1) {
                        cust -= (ss-1)*covered;
                    }
                    // for (int k = 2; k <= ss; k++) {
                    //     int nComb = nCombinations(ss, k);
                    //     if (k % 2 == 0) {
                    //         // debug("-", nComb*common[cc].second);
                    //         cust -= nComb*common[cc].second;
                    //     }
                    //     else {
                    //         // debug("+", nComb*common[cc].second);
                    //         cust += nComb*common[cc].second;
                    //     }
                    // }
                }
                if (cust > maxCust) {
                    maxCust = cust;
                    recommended = inclTowers;
                }
                else if (cust == maxCust) {
                    maxCust = cust;
                    bool better = false;
                    loop(j, 0, nt) {
                        if (inclTowers[j] < recommended[j]) {
                            better = true;
                            break;
                        }
                        else if (inclTowers[j] > recommended[j]) {
                            better = false;
                            break;
                        }
                        // if equal, continue
                    }
                    if (better) {
                        recommended = inclTowers;
                    }
                }
            }
        }
        cout << "Case Number  " << testcase++ << endl;
        cout << "Number of Customers: " << maxCust << endl;
        cout << "Locations recommended: " << recommended << endl << endl;
    }

    if (argc > 1) {
        cin.rdbuf(backup);
    }

#ifndef DEBUG
    clog.clear();
#endif

    return 0;
}
