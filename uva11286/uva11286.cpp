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

    int n, tmp;
    set<int> courses;
    map<set<int>, int> combinations;

    cin >> n;
    do {
        int maxStudents = -1;
        combinations.clear();
        loop(i, 0, n) {
            courses.clear();
            loop(j, 0, 5) {
                cin >> tmp;
                courses.insert(tmp);
            }

            if (combinations.find(courses) == combinations.end()) {
                combinations[courses] = 1;
            }
            else {
                combinations[courses]++;
            }
            maxStudents = max(maxStudents, combinations[courses]);
        }
        int totalStudents = 0;
        for (auto it = combinations.begin(); it != combinations.end(); it++) {
            if (it->second == maxStudents) {
                totalStudents += it->second;
            }
        }
        cout << totalStudents << endl;
        cin >> n;
    } while (n > 0);


    if (argc > 1) {
        cin.rdbuf(backup);
    }

#ifndef DEBUG
    clog.clear();
#endif

    return 0;
}
