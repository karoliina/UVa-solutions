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
ostream& operator<<(ostream &os, const multiset<T> &vec)
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
    // streambuf* backup;
    // streambuf* filebuf;

    if (argc > 1) { // input file
        // static ifstream fs(argv[1]);
        // if (!fs) {
        //     cout << "can't open file" << endl;
        //     exit(1);
        // }
        // backup = cin.rdbuf();
        // filebuf = fs.rdbuf();
        // cin.rdbuf(filebuf);
        freopen(argv[1], "r", stdin);
    }

    int n, b, sg, sb, tmp;
    multiset<int> green;
    multiset<int> blue;
    multiset<int> greenLeftovers;
    multiset<int> blueLeftovers;
    // cin >> n;
    scanf("%d", &n);

    loop(c, 0, n) {
        green.clear();
        blue.clear();
        // cin >> b >> sg >> sb;
        scanf("%d %d %d", &b, &sg, &sb);
        loop(i, 0, sg) {
            // cin >> tmp;
            scanf("%d", &tmp);
            green.insert(tmp);
        }
        loop(i, 0, sb) {
            // cin >> tmp;
            scanf("%d", &tmp);
            blue.insert(tmp);
        }

        while (!green.empty() && !blue.empty()) {
            greenLeftovers.clear();
            blueLeftovers.clear();
            loop(bf, 0, b) {
                int gPower = *(green.rbegin());
                int bPower = *(blue.rbegin());
                green.erase(--green.end());
                blue.erase(--blue.end());
                int diff = gPower - bPower;
                if (diff > 0) {
                    greenLeftovers.insert(diff);
                }
                else if (diff < 0) {
                    blueLeftovers.insert(-1*diff);
                }
                if (green.empty() || blue.empty()) {
                    break;
                }
            }
            for (auto it = greenLeftovers.begin(); it != greenLeftovers.end(); it++) {
                green.insert(*it);
            }
            for (auto it = blueLeftovers.begin(); it != blueLeftovers.end(); it++) {
                blue.insert(*it);
            }
        }
        if (!green.empty() && blue.empty()) {
            // cout << "green wins" << endl;
            printf("green wins\n");
            for (auto it = green.rbegin(); it != green.rend(); it++) {
                // cout << *it << endl;
                printf("%d\n", *it);
            }
        }
        else if (green.empty() && !blue.empty()) {
            // cout << "blue wins" << endl;
            printf("blue wins\n");
            for (auto it = blue.rbegin(); it != blue.rend(); it++) {
                // cout << *it << endl;
                printf("%d\n", *it);
            }
        }
        else {
            // cout << "green and blue died" << endl;
            printf("green and blue died\n");
        }
        if (c < n-1) {
            // cout << endl;
            printf("\n");
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
