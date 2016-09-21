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

// helper function for permutation generation - also returns ones that start with o
vec<Permutation> perms(int len) {
    vec<Permutation> newPermutations;
    if (len <= 0) {
        newPermutations.push_back(Permutation(0, 0, ""));
    }
    else {
        vec<Permutation> shorter = perms(len-1);
        for (auto p : shorter) {
            newPermutations.push_back(Permutation(p.is + 1, p.os, "i" + p.seq));
            newPermutations.push_back(Permutation(p.is, p.os + 1, "o" + p.seq));
        }
    }

    return newPermutations;
}

vec<string> generate_permutations(int len) {

    // generate permutations recursively
    //  - i + permutations of length n-1, check validity of each
    //  (permutations cannot start with an o/pop)
    vec<Permutation> shorter = perms(len-1);

    vec<string> permutations;
    for (auto p : shorter) {
        if (p.is == p.os - 1) {
            permutations.push_back("i" + p.seq);
        }
    }
    sort(permutations.begin(), permutations.end());
    return permutations;
}

#define DEBUG

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

    vec<vec<string> > permutations(100000);
    string word1, word2;
    while (getline(cin, word1)) {
        if (word1.size() == 0) {
            continue;
        }
        getline(cin, word2);
        while (word2.size() == 0) {
            getline(cin, word2);
        }

        cout << "[" << endl;
        // 1. check if word1 and word2 can be anagrams - if not, print empty result and continue
        string sorted1 = word1;
        string sorted2 = word2;
        sort(sorted1.begin(), sorted1.end());
        sort(sorted2.begin(), sorted2.end());
        if (word1.size() != word2.size() || sorted1.compare(sorted2) != 0) {
            continue;
        }

        else {
            int len = word1.size()*2;
            // 2. if necessary, generate all possible permutations of length 2*len where
            // number of i's == number of o's 
            //      - memoize the permutations for further use
            if (permutations[len].size() == 0) {
                permutations[len] = generate_permutations(len);
            }

            for (auto p : permutations[len]) {
                // simulate pushing and popping letters on the stack according to p. if at any point p
                // instructs to pop an empty stack, stop processing p
                stack<char> st;
                string result = ""; // this should be equal to word2 in the end
                int j = 0;
                loop(i, 0, p.size()) {
                    if (p[i] == 'i') {
                        st.push(word1[j++]);
                    }
                    else if (p[i] == 'o' && !st.empty()) {
                        result += st.top();
                        st.pop();
                    }
                    else {
                        break;
                    }
                }
                if (result.compare(word2) == 0) {
                    loop(j, 0, p.size() - 1) {
                        cout << p[j] << " ";
                    }
                    cout << p[p.size() - 1] << endl;
                }
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
