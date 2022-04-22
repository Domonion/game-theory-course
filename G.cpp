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
 
struct edge {
    const int u, v;
 
    edge(int _u, int _v) : u(_u), v(_v) {}
 
    int go(int from) const {
        if (u == from)
            return v;
 
        if (v == from)
            return u;
 
        throw runtime_error("bad edge");
    }
};
 
vec<vec<int>> g;
vec<edge> edges;
vec<int> parent_edge;
vec<int> sz;
vec<int> previous;
vec<char> used;
vec<char> is_edge_collapsed;
vec<vec<int>> back_edges;
 
int get_class(int v) {
    return previous[v] == v ? v : previous[v] = get_class(previous[v]);
}
 
int unite(int a, int b) {
    int a_class = get_class(a);
    int b_class = get_class(b);
 
    if (a_class != b_class) {
        if (sz[a_class] > sz[b_class]) {
            swap(a_class, b_class);
        }
 
        previous[a_class] = b_class;
        sz[b_class] += sz[a_class];
    }
 
    return b_class;
}
 
bool same(int a, int b) {
    return get_class(a) == get_class(b);
}
 
void dfs(int v) {
    used[v] = 1;
 
    fora(ei, g[v]) {
        if (ei == parent_edge[v])
            continue;
 
        int u = edges[ei].go(v);
 
        if (used[u] == 1) {
            back_edges[v].eb(ei);
        } else if(used[u] != 2) {
            parent_edge[u] = ei;
            dfs(u);
        }
    }
 
    used[v] = 2;
}
 
int dfs_grandi(int v) {
    used[v] = 1;
 
    int result = 0;
 
    fora(u, g[v]) {
        if (used[u])
            continue;
 
        result ^= dfs_grandi(u) + 1;
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
    randomer.seed(time(0));
 
    int n, m;
    cin >> n >> m;
 
    is_edge_collapsed.resize(m);
    back_edges.resize(n);
    sz.resize(n, 0);
    sz.shrink_to_fit();
    g.resize(n);
    g.shrink_to_fit();
    previous.resize(n);
 
    forn(i, 0, n) {
        sz[i] = 1;
        previous[i] = i;
    }
 
    forn(i, 0, m) {
        int from, to;
 
        cin >> from >> to;
        from--, to--;
 
        g[from].eb(i);
        g[to].eb(i);
        edges.eb(from, to);
    }
 
    forn(i, 0, n) {
        g[i].shrink_to_fit();
    }
 
    parent_edge.resize(n, -1);
    parent_edge.shrink_to_fit();
    used.resize(n);
    used.shrink_to_fit();
    dfs(0);
 
    forn(v, 0, n) {
        if (back_edges[v].empty())
            continue;
 
        fora(ei, back_edges[v]) {
            int u = edges[ei].go(v);
 
            is_edge_collapsed[ei] = 1;
 
            if (!same(u, v)) { // this if is a must because of loops - parent edge points to another vertex
                int cur_v = v;
                int cur_edge = parent_edge[v];
 
                while (!same(cur_v, u)) { // TODO bad place, think more
                    int cur_p = edges[cur_edge].go(cur_v);
 
                    is_edge_collapsed[cur_edge] = 1;
                    unite(cur_v, cur_p);
                    cur_v = cur_p;
                    cur_edge = parent_edge[cur_v];
                }
            }
        }
    }
 
    // ground might be collapsed!
 
    int cnt = 0;
    forn(i, 0, m) {
        if (is_edge_collapsed[i]) {
            cnt++;
        }
    }
 
    g.resize(n + cnt);
    g.shrink_to_fit();
 
    forn(i, 0, n) {
        g[i].clear();
    }
 
    forn(ei, 0, m) {
        if (is_edge_collapsed[ei]) {
            int new_vertex = n++;
            int from = get_class(edges[ei].v);
 
            g[from].eb(new_vertex);
            g[new_vertex].eb(from);
        } else {
            int from = get_class(edges[ei].u);
            int to = get_class(edges[ei].v);
 
            g[from].eb(to);
            g[to].eb(from);
        }
    }
 
    int start = get_class(0);
 
    used.resize(n);
 
    forn(i, 0, n) {
        used[i] = 0;
    }
 
    int result = dfs_grandi(start);
 
    if (result == 0) {
        cout << "Second";
    } else {
        cout << "First";
    }
 
    return 0;
}