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
 
ll count(ll n, ll l_border) {
    ll l = sqrt(l_border);
 
    if (l * l != l_border)
        throw runtime_error("should be impossible: l * l != l_border");
 
    if (n < l_border)
        throw runtime_error("should be impossible: n < l_border");
 
    if (l * l == n)
        return l;
 
    ll r_border = n;
    ll range = l + 1;
    ll diff = r_border - l_border;
    ll count_no_border = diff / range;
 
    if (count_no_border * range == diff)
        return l;
    else {
        ll new_n = n - count_no_border - 1;
        return count(new_n, sqr(l - 1));
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
    int n;
    ll result = 0;
    cin >> n;
    forn(i, 0, n) {
        ll x;
        cin >> x;
        ll l = sqrt(x);
        result ^= count(x, l * l);
    }
    cout << (result ? "First" : "Second");
    return 0;
}