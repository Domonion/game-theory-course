#include <iostream>
#include <iomanip>
#include <algorithm>
#include <random>
#include <bitset>
 
using namespace std;
 
typedef long long ll;
 
struct edge {
    int color, u, v;
 
    edge() : color(-1), u(-1), v(-1) {}
 
    edge(const edge &another) : color(another.color), u(another.u), v(another.v) {}
 
    edge(int _color, int _v, int _u) : color(_color), u(_u), v(_v) {}
 
    int go(int vertex) const {
        if (v == vertex)
            return u;
 
        if (u == vertex) {
            return v;
        }
 
        if (vertex == -1 || u == -1 || v == -1) {
            throw runtime_error("uninitialized");
        }
 
        throw runtime_error("edge");
    }
};
 
const int N = 21;
const int M = 20;
edge edges[N];
char win[1 << M][2];
 
#define forn(i, s, n) for (auto (i) = (s); (i) < (n); (i)++)
#define fora(i, a) for (auto (i) : (a))
#define eb emplace_back
 
int used_counter;
int used[N];
int used_edges[M];
int allowed_edges[M];
vector<int> g[N];
 
void initialize(int mask) {
    used_counter++;
 
    forn(i, 0, M) {
        char should = mask & 1;
 
        mask >>= 1;
 
        if (!should)
            continue;
 
        allowed_edges[i] = used_counter;
    }
}
 
void check_edges(int v) {
    used[v] = used_counter;
 
    fora(i, g[v]) {
        if (allowed_edges[i] != used_counter)
            continue;
 
        used_edges[i] = used_counter;
 
        int u = edges[i].go(v);
 
        if (used[u] == used_counter)
            continue;
 
        check_edges(u);
    }
}
 
int get_real_mask() {
    int answer = 0;
 
    forn(i, 0, M) {
        if (used_edges[i] == used_counter) {
            answer ^= 1 << i;
        }
    }
 
    return answer;
}
 
char solve(int mask, int who) {
    if (!win[mask][who]) {
        initialize(mask);
        check_edges(0);
 
        int real_mask = get_real_mask();
 
        if (real_mask < mask) {
            win[mask][who] = solve(real_mask, who);
        } else {
            char result = 2;
 
            forn(i, 0, M) {
                int color = edges[i].color;
 
                if (color == !who)
                    continue;
 
                int next_mask = mask ^ (1 << i);
 
                if (next_mask > mask) {
                    continue;
                }
 
                char next_result = solve(next_mask, !who);
 
                if (next_result == 2) {
                    result = 1;
                }
            }
 
            win[mask][who] = result;
        }
    }
 
    return win[mask][who];
}
 
string answer(char state, int who) {
    if (state != 1 && state != 2) {
        throw runtime_error("not calculated!");
    }
 
    string left = "Left";
    string right = "Right";
 
    if (who == 1)
        swap(left, right);
 
    return state == 1 ? left : right;
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
 
    for (int i = 0; i < m; i++) {
        int from, to, c;
        cin >> from >> to >> c;
        from--, to--;
        edges[i] = edge(c, from, to);
        g[from].eb(i);
        g[to].eb(i);
    }
 
    cout << answer(solve((1 << m) - 1, 0), 0) << ' ' << answer(solve((1 << m) - 1, 1), 1);
 
    return 0;
}