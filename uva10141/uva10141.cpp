#include <cstdio>
#include <cmath>
#include <cstdlib>
#include <ctime>
#include <cstdarg>
#include <iostream>
#include <sstream>
#include <string>
#include <algorithm>
#include <regex>
#include <vector>
#include <map>
#include <unordered_map>
#include <set>
#include <unordered_set>

using namespace std;

#define loop(x, start, end) for (uint x = start; x < end; ++x)

#define INF 1000000000
#define PI 2*acos(0.0)

typedef long long ll;

template<typename T>
using vec = vector<T>;

template<typename T>
using uset = unordered_set<T>;

template<typename K, typename V>
using umap = unordered_map<K, V>;

void log(string s) {
    fprintf(stderr, "%s\n", s.c_str());
}


void log(vec<int> v) {
    loop(i, 0, v.size()) {
        fprintf(stderr, "%d ", v[i]);
    }
    fprintf(stderr, "\n");
}


void log(const char* format, ...) {
    va_list args;
    va_start(args, format);
    vfprintf(stderr, format, args);
    va_end(args);
}


// #define DEBUG

int main(int argc, char* argv[]) {

#ifndef DEBUG
    freopen("/dev/null", "w", stderr);
#endif

    if (argc > 1) { // input file
        freopen(argv[1], "r", stdin);
    }

    int n, p;
    int rfp = 1;
    while (1) {
        scanf("%d %d", &n, &p);
        if (n == 0 && p == 0)
            return 0;

        double compliance = -1.0; // best compliance so far
        double price = INF; // best price so far
        string bestProposal;

        getc(stdin);

        // vector<string> reqs(n);
        string line;
        loop(i, 0, n) {
            getline(cin, line);
            // reqs[i] = line;
        }

        loop(i, 0, p) {
            string proposal;
            getline(cin, proposal);

            double d;
            int r;
            int met = 0;
            string item;
            scanf("%lf %d", &d, &r);
            getc(stdin);
            loop(j, 0, r) {
                getline(cin, item);
                met++;
                // if (find(reqs.begin(), reqs.end(), item) != reqs.end()) {
                //     met++;
                // }
            }
            double comp = double(met)/n;
            log("compliance for %s = %.4lf\n", proposal.c_str(), comp);
            if (comp > compliance || (comp == compliance && d < price)) {
                compliance = comp;
                price = d;
                bestProposal = proposal;
            }
        }
        if (rfp > 1) {
            puts("");
        }
        printf("RFP #%d\n", rfp);
        printf("%s\n", bestProposal.c_str());

        rfp++;
    }


    return 0;
}
