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

// #define DEBUG

int main(int argc, char* argv[]) {

#ifndef DEBUG
    clog.setstate(ios_base::failbit);
#endif

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

    int c, n, t, m;
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
        cin >> n >> t >> m;
        // store arrival and departure times per car
        vec<int> arr(m, -1);
        vec<int> dep(m, -1);
        loop(car, 0, m) {
            cin >> arr[car] >> side;
            if (side == "left") {
                left.push_back(car);
            }
            else {
                right.push_back(car);
            }
        }

        // simulate ferry
        string pos = "left";
        string oldPos;
        int time = 0;
        while (!left.empty() || !right.empty()) {
            // unload ferry
            while (!ferry.empty()) {
                dep[ferry.front()] = time;
                ferry.pop_front();
            }
            // load up n cars from current side
            if (pos == "left") {
                while (!left.empty() && ferry.size() < n && arr[left.front()] <= time) {
                    ferry.push_back(left.front());
                    left.pop_front();
                }
            }
            else {
                while (!right.empty() && ferry.size() < n && arr[right.front()] <= time) {
                    ferry.push_back(right.front());
                    right.pop_front();
                }
            }
            // if there are no cars waiting right now but will be later, increment time to the next arrival
            // time of a car
            int nextLeft = left.empty() ? -1 : arr[left.front()];
            int nextRight = right.empty() ? -1 : arr[right.front()];
            if (ferry.empty() && (nextLeft >= 0 || nextRight >= 0)) {
                oldPos = pos;
                int oldTime = time;
                if (nextLeft >= 0 && nextRight >= 0 && nextLeft == nextRight) { // stay on same side
                    time = nextLeft;
                }
                // car waiting on left side only
                else if (nextRight < 0 && nextLeft >= 0) {
                    time = max(time, nextLeft);
                    pos = "left";
                }
                // car waiting on right side only
                else if (nextLeft < 0 && nextRight >= 0) {
                    time = max(time, nextRight);
                    pos = "right";
                }
                // cars on both sides
                else if (nextLeft >= 0 && nextRight >= 0) {
                    if (nextLeft < nextRight) {
                        time = max(time, nextLeft);
                        pos = "left";
                    }
                    else {
                        time = max(time, nextRight);
                        pos = "right";
                    }
                }
                if (oldPos != pos) {
                    time += t; // account for time taken to travel to the other side
                }
                if (time <= oldTime) {
                    cout << "OMG" << endl;
                    break;
                }
            }
            else { // cars on ferry or car currently waiting on other side
                // travel to other side and increment time by t
                pos = pos == "left" ? "right" : "left";
                time += t;
            }
        }

        while (!ferry.empty()) {
            dep[ferry.front()] = time;
            ferry.pop_front();
        }

        loop(i, 0, dep.size()) {
            if (dep[i] < 0) {
                break;
            }
            // cout << i << " " << dep[i] << endl;
            cout << dep[i] << endl;
        }

        if (testcase < c - 1) {
            cout << endl;
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
