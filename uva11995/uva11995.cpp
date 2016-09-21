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
#include <stack>
#include <queue>

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

    int n, op, val;

    while (cin >> n) {
        bool canBeStack = true;
        bool canBeQueue = true;
        bool canBePriorityQueue = true;
        stack<int> st;
        queue<int> q;
        priority_queue<int> pq;
        loop(i, 0, n) {
            cin >> op >> val;
            if (op == 1) {
                if (canBeStack) {
                    st.push(val);
                }
                if (canBeQueue) {
                    q.push(val);
                }
                if (canBePriorityQueue) {
                    pq.push(val);
                }
            }
            else {
                if (canBeStack && (st.empty() || st.top() != val)) {
                    canBeStack = false;
                }
                else if (!st.empty()) {
                    st.pop();
                }
                if (canBeQueue && (q.empty() || q.front() != val)) {
                    canBeQueue = false;
                }
                else if (!q.empty()) {
                    q.pop();
                }
                if (canBePriorityQueue && (pq.empty() || pq.top() != val)) {
                    canBePriorityQueue = false;
                }
                else if (!pq.empty()) {
                    pq.pop();
                }
            }
        }
        if (canBeStack && !canBeQueue && !canBePriorityQueue) {
            cout << "stack" << endl;
        }
        else if (!canBeStack && canBeQueue && !canBePriorityQueue) {
            cout << "queue" << endl;
        }
        else if (!canBeStack && !canBeQueue && canBePriorityQueue) {
            cout << "priority queue" << endl;
        }
        else if (!canBeStack && !canBeQueue && !canBePriorityQueue) {
            cout << "impossible" << endl;
        }
        else {
            cout << "not sure" << endl;
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
