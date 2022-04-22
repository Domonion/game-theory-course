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
 
const int N = 10000;
const int M = 100000;
char used[N];
vec<int> g[N];
int f[N];
 
bool contains(const set<int> &where, int what) {
    return where.find(what) != where.end();
}
 
int mex(const set<int> &grandi) {
    forn(i, 0, N + 1) {
        if (!contains(grandi, i)) {
            return i;
        }
    }
 
    throw runtime_error("very bad");
}
 
int dfs(int v) {
    if (used[v])
        return f[v];
 
    used[v] = 1;
 
    set<int> grandi;
 
    fora(u, g[v]) {
        grandi.insert(dfs(u));
    }
 
    f[v] = mex(grandi);
 
    return f[v];
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
    int n, m;
    cin >> n >> m;
 
    forn(i, 0, m) {
        int from, to;
        cin >> from >> to;
        from--, to--;
        g[from].eb(to);
    }
 
    forn(i, 0, n) {
        dfs(i);
    }
 
    forn(i, 0, n) {
        cout << f[i] << '\n';
    }
 
    return 0;
}