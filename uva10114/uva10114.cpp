#include <cstdio>
#include <cmath>
#include <cstdlib>
#include <ctime>
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

#define INF 100000000
#define PI 2*acos(0.0)

typedef long long ll;

template<typename T>
using vec = vector<T>;

template<typename T>
using uset = unordered_set<T>;

template<typename K, typename V>
using umap = unordered_map<K, V>;

ostream& operator<<(ostream &os, const vector<int> &vec)
{
    for(int n: vec)
        os << n << " ";
    return os;
}

#define DEBUG

int main(int argc, char* argv[]) {

#ifndef DEBUG
    clog.setstate(ios_base::failbit);
#endif

    if (argc > 1) { // input file
        freopen(argv[1], "r", stdin);
    }

    while (true) {
        int dur;
        uint records;
        double down, total;
        scanf("%d %lf %lf %u", &dur, &down, &total, &records);

        if (dur < 0)
            return 0;

        vec<int> month(records);
        vec<double> percent(records);
        loop(i, 0, records) {
            cin >> month[i];
            string tmp;
            cin >> tmp;
            percent[i] = stod(tmp);
        }

        double owing = total;
        double value = total + down;
        double payment = total/dur;
        value *= (1.0 - percent[0]); // after month 0

        uint r = 0;
        int m = 1;
        while (value <= owing && m < dur) {
            // printf("start of month %d: value = %.8lf, owing = %.8lf\n", m, value, owing);
            // printf("m = %d, month[r] = %d\n", m, month[r]);
            if (m == month[r+1] && r < records - 1) {
                r++;
                // printf("changing to the percentage %.5lf\n", percent[r]);
            }
            value *= (1.0 - percent[r]);
            owing -= payment;
            m++;
        }
        // printf("end of month %d: value = %.8lf, owing = %.8lf\n", m-1, value, owing);
        if (m == 2 || (m == dur && dur == 1))
            printf("1 month\n");
        else if (m == dur) {
            if (value > owing) {
                printf("%d months\n", m-1);
            }
            else {
                printf("%d months\n", dur);
            }
        }
        else
            printf("%d months\n", m-1);

        month.clear();
        percent.clear();
    }



#ifndef DEBUG
    clog.clear();
#endif

    return 0;
}
