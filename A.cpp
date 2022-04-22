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
 
const int N = 50000;
const int M = 250000;
vec<int> g[N];
char type[N];
int deg[N];
char used[N];
 
void dfs(int v) {
    used[v] = 1;
 
    fora(u, g[v]) {
        if(used[u])
            continue;
 
        if(type[v] == 'l')
            type[u] = 'w';
        else if (--deg[u] == 0)
            type[u] = 'l';
        else
            continue;
        dfs(u);
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
    int n, m;
    cin >> n >> m;
 
    forn(i, 0, n) {
        deg[i] = 0;
        used[i] = 0;
        type[i] = 0;
    }
 
    forn(i, 0, m) {
        int from, to;
        cin >> from >> to;
        from--, to--;
        g[to].eb(from);
        deg[from]++;
    }
 
    forn(i, 0, n) {
        if(deg[i] == 0)
            type[i] = 'l';
    }
 
    forn(i, 0, n) {
        if(!used[i] && (type[i] == 'l' || type[i] == 'w'))
            dfs(i);
    }
 
    forn(i, 0, n) {
        if(!used[i] && (type[i] == 'l' || type[i] == 'w'))
            dfs(i);
    }
 
    forn(i, 0, n) {
        if (type[i] == 'w')
            cout << "Win\n";
        else if (type[i] == 'l')
            cout << "Loss\n";
        else
            cout << "Draw\n";
    }
 
    return 0;
}