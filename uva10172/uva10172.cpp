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
ostream& operator<<(ostream &os, const deque<T> &vec)
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

    int SET, N, S, Q, Qi, tmp;
    vec<deque<int> > B; // queues
    deque<int> carrier; // stack
    cin >> SET;
    loop(c, 0, SET) {
        cin >> N >> S >> Q;
        B.resize(N);
        loop(i, 0, N) {
            B[i] = deque<int>();
            cin >> Qi;
            loop(j, 0, Qi) {
                cin >> tmp;
                B[i].push_back(tmp);
            }
        }

        // simulation
        int station = 1;
        int time = 0;
        bool allQueuesEmpty = false;
        carrier.clear();
        do {
            deque<int> queue = B[station-1];
            debug("STATION:", station, "carrier:", carrier, "B:", B[station-1], "time:", time);
            // unload
            while (!carrier.empty()) {
                if (carrier.back() == station) {
                    debug("DESTINATION:", carrier.back());
                    carrier.pop_back();
                    time++;
                }
                else if (B[station-1].size() < Q) {
                    debug("enqueue", carrier.back(), "to queue B");
                    B[station-1].push_back(carrier.back());
                    carrier.pop_back();
                    time++;
                }
                else {
                    break;
                }
            }

            // load from queue
            while (!B[station-1].empty() && carrier.size() < S) {
                debug("push", B[station-1].front(), "to carrier stack");
                carrier.push_back(B[station-1].front());
                B[station-1].pop_front();
                time++;
            }

            // check which queues are empty
            allQueuesEmpty = true;
            loop(q, 0, N) {
                if (!B[q].empty()) {
                    allQueuesEmpty = false;
                    break;
                }
                debug("all queues empty!");
            }

            if (!carrier.empty() || !allQueuesEmpty) {
                debug("LEAVING STATION:", station, "carrier:", carrier, "B:", B[station-1]);
                station = (station % N) + 1;
                time += 2;
            }
        }
        while (!carrier.empty() || !allQueuesEmpty);

        cout << time << endl;
    }


    if (argc > 1) {
        cin.rdbuf(backup);
    }

#ifndef DEBUG
    clog.clear();
#endif

    return 0;
}
