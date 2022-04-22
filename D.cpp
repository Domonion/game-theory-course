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
 
const int N = 5000;
int f[N + 1];
char used[N];
 
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
 
    forn(u, 1, v) {
        int other = v - u;
        if (other > u) {
            grandi.insert(dfs(other));
        } else {
            grandi.insert(dfs(u));
        }
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
    int a, b, c;
    cin >> a >> b >> c;
 
    int result = dfs(a) ^ dfs(b) ^ dfs(c);
 
//    if (a == 2 && b == c == 1){
//        cout << "YES\n";
//        cout << 1 << ' ' << 1 << ' ' << 1;
//        return 0;
//    }
//
//    if (a == 1 && b == 1 && c == 1){
//        cout << "NO\n";
//        return 0;
//    }
//
//    if (a == 1 && b == 1 && c == 10){
//        return 1;
//    }
 
//    return -1;
 
//    if (a == 1)
//        return 1;
 
//    if (b == 1)
//        return 1;
 
//    if (c == 10)
//        return 1;
 
    if (result == 0) {
        cout << "NO";
    } else {
        cout << "YES\n";
 
        forn(i, 1, a) {
            int other = a - i;
            int next;
 
            if (other > i) {
                next = dfs(other);
            } else {
                next = dfs(i);
            }
 
            int nextResult = next ^ dfs(b) ^ dfs(c);
 
            if (nextResult == 0) {
                cout << max(other, i) << ' ' << b << ' ' << c << '\n';
                return 0;
            }
        }
 
        forn(i, 1, b) {
            int other = b - i;
            int next;
 
            if (other > i) {
                next = dfs(other);
            } else {
                next = dfs(i);
            }
 
            int nextResult = dfs(a) ^ next ^ dfs(c);
 
            if (nextResult == 0) {
                cout << a << ' ' << max(other, i) << ' ' << c << '\n';
                return 0;
            }
        }
 
        forn(i, 1, c) {
            int other = c - i;
            int next;
 
            if (other > i) {
                next = dfs(other);
            } else {
                next = dfs(i);
            }
 
            int nextResult = dfs(a) ^ dfs(b) ^ next;
 
            if (nextResult == 0) {
                cout << a << ' ' << b << ' ' << max(other, i) << '\n';
                return 0;
            }
        }
 
        throw runtime_error("bad");
    }
 
    return 0;
}