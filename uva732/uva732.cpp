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
#include <stack>
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

class Permutation {
    public:
        int is, os;
        string seq;
        Permutation(int, int, string);
};

Permutation::Permutation(int i, int o, string s) {
    is = i;
    os = o;
    seq = s;
}

vec<string> createPermutations(string &input, string &output, int iPos, int oPos, char nextOperation,
                               stack<char> currentStack, Permutation currentPermutation) {
    vec<string> perms;

    if (nextOperation == 'i') {
        if (iPos < input.size()) {
            // push input[iPos] on the stack
            currentStack.push(input[iPos++]);
            // increment number of pushes in current permutation
            currentPermutation.is++;
            currentPermutation.seq += "i";
        }
        else { // no more characters to push, this path is invalid
            return perms;
        }
    }
    else if (nextOperation == 'o') {
        // try to pop stack, possibly return if permutation is found infeasible
        if (currentStack.empty()) {
            return perms;
        }
        char next = currentStack.top();
        if (oPos >= output.size() || next != output[oPos++]) {
            return perms;
        }
        currentStack.pop();
        currentPermutation.os++;
        currentPermutation.seq += "o";
    }

    if (currentPermutation.seq.size() == input.size() * 2) {
        perms.push_back(currentPermutation.seq);
        return perms;
    }

    // not a leaf node, generate the rest
    vec<string> pushes = createPermutations(input, output, iPos, oPos, 'i', currentStack,
            currentPermutation);
    vec<string> pops = createPermutations(input, output, iPos, oPos, 'o', currentStack,
            currentPermutation);

    for (auto s : pushes) {
        if (s.size() == input.size() * 2) {
            perms.push_back(s);
        }
    }
    for (auto s : pops) {
        if (s.size() == input.size() * 2) {
            perms.push_back(s);
        }
    }

    return perms;
}

vec<string> validPermutations(string &input, string &output) {
    stack<char> currentStack;
    Permutation currentPermutation(0, 0, "");
    int iPos = 0;
    int oPos = 0;
    vec<string> pushes = createPermutations(input, output, iPos, oPos, 'i', currentStack, currentPermutation);
    return pushes;
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

    // START SOLUTION

    string input, output;
    while (getline(cin, input)) {
        // if (input.size() == 0) {
        //     continue;
        // }
        getline(cin, output);
        // while (output.size() == 0) {
        //     getline(cin, output);
        // }

        cout << "[" << endl;
        // 1. check if input and output can be anagrams - if not, print empty result and continue
        string sinput = input;
        string soutput = output;
        sort(sinput.begin(), sinput.end());
        sort(soutput.begin(), soutput.end());
        if (input.size() != output.size() || sinput.compare(soutput) != 0) {
            cout << "]" << endl;
            continue;
        }

        else {
            // recursively construct permutations, pruning the branch of the call tree if the permutation
            // cannot result in a correct solution
            vec<string> perms = validPermutations(input, output);
            for (auto p : perms) {
                loop(j, 0, p.size() - 1) {
                    cout << p[j] << " ";
                }
                cout << p[p.size() - 1] << endl;
            }

        }
        cout << "]" << endl;
    }


    // END SOLUTION
    if (argc > 1) {
        cin.rdbuf(backup);
    }

#ifndef DEBUG
    clog.clear();
#endif

    return 0;
}
