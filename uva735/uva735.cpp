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

    int x, p;
    set<int> s;
    vec<int> v;

    loop(i, 0, 21) {
        s.insert(i);
        s.insert(i*2);
        s.insert(i*3);
    }
    s.insert(50);

    v.assign(s.begin(), s.end());
    int n = v.size();

    string asterisks = "";
    loop(i, 0, 70) {
        asterisks += "*";
    }

    cin >> x;
    while (x > 0) {
        set<set<int> > c;
        p = 0;

        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                for (int k = 0; k < n; k++) {
                    if (x - v[i] - v[j] - v[k] == 0) {
                        p += 1;
                        set<int> cc;
                        cc.insert(v[i]);
                        cc.insert(v[j]);
                        cc.insert(v[k]);
                        c.insert(cc);
                    }
                }
            }
        }

        if (p > 0) {
            cout << "NUMBER OF COMBINATIONS THAT SCORES " << x << " IS " << c.size() << "." << endl;
            cout << "NUMBER OF PERMUTATIONS THAT SCORES " << x << " IS " << p << "." << endl;
        }
        else {
            cout << "THE SCORE OF " << x << " CANNOT BE MADE WITH THREE DARTS." << endl;
        }
        cout << asterisks << endl;

        cin >> x;
    }
    cout << "END OF OUTPUT" << endl;

    if (argc > 1) {
        cin.rdbuf(backup);
    }

#ifndef DEBUG
    clog.clear();
#endif

    return 0;
}
