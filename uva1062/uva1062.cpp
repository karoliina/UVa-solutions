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

    string cont;
    int c = 1;

    while (getline(cin, cont)) {
        if (cont == "end") {
            return 0;
        }
        vec<stack<char> > stacks;
        loop(i, 0, cont.size()) {
            bool pushed = false;
            loop(j, 0, stacks.size()) {
                debug("top =", stacks[j].top(), "container =", cont[i]);
                if (stacks[j].top() >= cont[i]) {
                    stacks[j].push(cont[i]);
                    debug("pushing to stack", j, "new top =", stacks[j].top());
                    pushed = true;
                    break;
                }
            }
            if (!pushed) {
                stacks.push_back(stack<char>());
                stacks[stacks.size() - 1].push(cont[i]);
                debug("creating new stack, top =", stacks[stacks.size() - 1].top());
            }
        }
        cout << "Case " << c++ << ": " << stacks.size() << endl;
    }

    if (argc > 1) {
        cin.rdbuf(backup);
    }

#ifndef DEBUG
    clog.clear();
#endif

    return 0;
}
