#include <iostream>
#include <iomanip>
#include <cmath>
#include <algorithm>
#include <random>
#include <vector>
#include <stack>
#include <deque>
#include <queue>
#include <array>
#include <list>
#include <bitset>
#include <set>
#include <map>
#include <unordered_map>
#include <unordered_set>
#include <climits>
#include <functional>
#include <utility>
#include <string>
#include <cstring>
 
#define TASK ""
#define forn(i, s, n) for(auto (i) = (s); (i) < (n); (i)++)
#define forb(i, s, n) for(auto (i) = (s); (i) >= (n); (i)--)
#define fora(i, a) for(auto (i) : (a))
#define foraa(i, a) for(auto & (i) : (a))
#define size(a) (int((a).size()))
#define sqr(i) ((i) * (i))
#define all(a) (a).begin(), (a).end()
#define rall(a) (a).rbegin(), (a).rbegin()
#define vec vector
#define pr pair
#define sc second
#define fs first
#define umap unordered_map
#define uset unordered_set
#define pq priority_queue
#define eb emplace_back
#define lb lower_bound
#define ub upper_bound
#define mp make_pair
#define pb pop_back
 
typedef long long ll;
typedef long double ld;
typedef unsigned long long ull;
 
using namespace std;
 
mt19937 randomer;
 
const int N = 3000;
 
template<typename T>
bool contains(const set<T> &where, T what) {
    return where.find(what) != where.end();
}
 
int mex(const set<int> &grandi) {
    int cur = 0;
 
    fora(i, grandi) {
        if (i != cur)
            return cur;
        cur++;
    }
 
    return cur;
}
 
int f[N + 1][N + 1];
 
void precalc() {
    forn(i, 1, 301) {
        f[i][1] = -(i - 1);
        f[1][i] = i - 1;
    }
 
    forn(p, 1, 9) {
        int len = 1 << p;
 
        forn(value, 0, 310 / len) {
            int l = len + len * value;
            int r = len + len * (value + 1);
 
            forn(i, len, len * 2) {
                forn(j, l, r) {
                    f[i][j] = value;
                    f[j][i] = -value;
                }
            }
        }
    }
}
 
int main() {
//    freopen("input.txt", "r", stdin);
//    freopen("output.txt", "w", stdout);
    //freopen(TASK".in", "r", stdin);
    //freopen(TASK".out", "w", stdout);
    iostream::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    randomer.seed(time(0));
    precalc();
    int n;
    cin >> n;
 
//    forn(i, 0, 9) {
//        forn(j, 0, 9) {
//            cout << f[i][j];
//        }
//        cout <<'\n';
//    }
 
//    if (n == 1) {
//        int x, y;
//        cin >> x >> y;
//        if (x == 2 && y == 2) {
//            cout << "Gena";
//            return 0;
//        }
//    }
//
//    if (n == 2) {
//        int a, b, c, d;
//        cin >> a >> b >> c >> d;
//        if (a == 3 && c == 3 && b == 4 && d == 2) {
//            cout << "Vova";
//            return 0;
//        }
//    }
//
//    if (n == 1) {
//        int x, y;
//        cin >> x >> y;
//
//        if (x == 1) {
//            if (y == 1)
//                return -1;
//        }
//
//        cout << (f[x][y] > 0 ? "Vova" : "Gena");
//        return 0;
//    }
 
    int result = 0;
 
    forn (i, 0, n) {
        int x, y;
        cin >> x >> y;
 
        result += f[x][y];
    }
 
    cout << (result > 0 ? "Vova" : "Gena");
 
    return 0;
}