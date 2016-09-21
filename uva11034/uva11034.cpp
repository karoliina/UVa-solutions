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
#include <deque>

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
ostream& operator<<(ostream &os, const deque<T> &dq)
{
    for (T n : dq)
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

    int c, l, m;
    int len;
    string side;
    deque<int> left;
    deque<int> right;
    deque<int> ferry;
    cin >> c;
    loop(testcase, 0, c) {
        left.clear();
        right.clear();
        ferry.clear();
        // queue cars
        cin >> l >> m;
        l *= 100;
        loop(car, 0, m) {
            cin >> len >> side;
            if (side == "left") {
                left.push_back(len);
            }
            else {
                right.push_back(len);
            }
        }

        // simulate ferry
        string pos = "left";
        int ferryLength = 0;
        string oldPos;
        int crosses = 0;
        while (!left.empty() || !right.empty()) {
            debug("crosses =", crosses);
            debug("left:", left);
            debug("right:", right);
            debug("ferry:", ferry);
            // unload ferry
            while (!ferry.empty()) {
                debug("unloading car", ferry.front());
                ferry.pop_front();
            }
            ferryLength = 0;
            // load up n cars from current side
            if (pos == "left") {
                while (!left.empty() && ferryLength + left.front() <= l) {
                    debug("loading car", left.front(), "from left");
                    ferryLength += left.front();
                    ferry.push_back(left.front());
                    left.pop_front();
                }
            }
            else {
                while (!right.empty() && ferryLength + right.front() <= l) {
                    debug("loading car", right.front(), "from right");
                    ferryLength += right.front();
                    ferry.push_back(right.front());
                    right.pop_front();
                }
            }

            pos = pos == "left" ? "right" : "left";
            crosses++;
        }

        // while (!ferry.empty()) {
        //     ferry.pop_front();
        // }

        cout << crosses << endl;
    }

    if (argc > 1) {
        cin.rdbuf(backup);
    }

#ifndef DEBUG
    clog.clear();
#endif

    return 0;
}
