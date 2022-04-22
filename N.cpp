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
#define point pair<int, int>
#define x first
#define y second
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
 
const int N = 100;
int A[N][N];
int B[N][N];
 
set<point > solve(int n, int m) {
    set<point > result;
 
    forn(i, 0, n) {
        forn(j, 0, m) {
            char bad = false;
 
            forn(k, 0, m) {
                if (B[i][k] > B[i][j]) {
                    bad = true;
                    break;
                }
            }
 
            if (!bad) {
                forn(k, 0, n) {
                    if (A[k][j] > A[i][j]) {
                        bad = true;
                        break;
                    }
                }
            }
 
            if (!bad) {
                result.emplace(i + 1, j + 1);
            }
        }
    }
 
    return result;
}
 
int main() {
//    freopen("input.txt", "r", stdin);
//    freopen("output.txt", "w", stdout);
//freopen(TASK".in", "r", stdin);
//freopen(TASK".out", "w", stdout);
    iostream::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
 
    int n, m;
    cin >> n >> m;
 
    forn(i, 0, n) {
        forn(j, 0, m) {
            cin >> A[i][j];
            B[i][j] = -A[i][j];
        }
    }
 
    set<point > result = solve(n, m);
    set<int> first_optimal;
    set<int> second_optimal;
 
    transform(all(result), inserter(first_optimal, first_optimal.begin()), [](point p) { return p.x; });
    transform(all(result), inserter(second_optimal, second_optimal.begin()), [](point p) { return p.y; });
 
    cout << size(first_optimal) << ' ' << size(second_optimal) << '\n';
 
    fora(i, first_optimal) {
        cout << i << ' ';
    }
 
    cout << '\n';
 
    fora(i, second_optimal) {
        cout << i << ' ';
    }
 
    return 0;
}