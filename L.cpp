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
 
struct fraction {
    fraction(const fraction &other) : _numerator(other._numerator), _denominator(other._denominator) {}
 
    fraction(ll v) : _numerator(v), _denominator(1) {}
 
    fraction(ll num, ll denom) : _numerator(num), _denominator(denom) {
        ll _gcd = gcd(num, denom);
        _numerator /= _gcd;
        _denominator /= _gcd;
    }
 
    fraction() : _numerator(0), _denominator(1) {}
 
    string answer() const {
        if (_denominator < 0) {
            return to_string(_numerator * -1) + " " + to_string(_denominator * -1);
        }
        return to_string(_numerator) + " " + to_string(_denominator);
    }
 
    fraction operator+(const fraction &another) const {
        fraction current = *this;
        current += another;
 
        return current;
    }
 
    fraction operator+=(const fraction &another) {
        _numerator *= another.denominator();
        _numerator += another.numerator() * denominator();
        _denominator *= another.denominator();
 
        normalize();
 
        return *this;
    }
 
    fraction operator/=(const fraction &another) {
        _numerator *= another.denominator();
        _denominator *= another.numerator();
 
        normalize();
 
        return *this;
    }
 
    bool operator<(const fraction &another) const {
        ll numa = numerator();
        ll denuma = denominator();
 
        if (denuma < 0) {
            numa *= -1;
            denuma *= -1;
        }
 
        ll other_numa = another.numerator();
        ll other_denuma = another.denominator();
 
        if (other_denuma < 0) {
            other_denuma *= -1;
            other_numa *= -1;
        }
 
        ll our = numa * other_denuma;
        ll their = other_numa * denuma;
 
        return our < their;
    }
 
    fraction operator/(const fraction &another) const {
        fraction result = *this;
 
        return result /= another;
    }
 
    ll denominator() const {
        return _denominator;
    }
 
    ll numerator() const {
        return _numerator;
    }
 
    ll sign() const {
        return sign(sign(numerator()) * sign(denominator()));
    }
 
    ll old_sign() const {
        return old_sign(old_sign(numerator()) * old_sign(denominator()));
    }
 
private:
    static const bool should_normalize = true;
 
    void normalize() {
        if (should_normalize == false)
            return;
 
        ll _gcd = gcd(numerator(), denominator());
 
        _numerator /= _gcd;
        _denominator /= _gcd;
    }
 
    ll _numerator, _denominator;
 
    static ll gcd(ll a, ll b) {
        return b != 0 ? gcd(b, a % b) : a;
    }
 
    static ll sign(ll a) {
        if (a == 0)
            return 0;
 
        return a > 0 ? 1 : -1;
    }
 
    static ll old_sign(ll a) {
        return a >= 0 ? 1 : -1;
    }
};
 
const int N = 21;
const int M = 20;
edge edges[N];
 
#define forn(i, s, n) for (auto (i) = (s); (i) < (n); (i)++)
#define fora(i, a) for (auto (i) : (a))
#define eb emplace_back
 
bool contains(int mask, int index) {
    return mask & (1 << index);
}
 
fraction simplest(const fraction& l, const fraction& r, const fraction& current) {
    if (l.sign() * r.sign() == -1)
        return fraction();
 
    if (current.sign() == -1) {
        return simplest(r / -1, l / -1, current / -1) / -1;
    }
 
    if (abs(current.denominator()) == 1) {
        int best_l = 0;
        int best_r = current.numerator();
 
        while (best_r - best_l > 1) {
            int mid = (best_l + best_r) / 2;
 
            if (l < mid) {
                best_r = mid;
            } else {
                best_l = mid;
            }
        }
 
        return best_r;
    } else {
        int p = (current.numerator() - 1) / 2;
        int q = current.denominator() / 2;
        fraction mid_left_parent(p, q);
        fraction mid_right_parent(p + 1, q);
 
        bool left_valid = l < mid_left_parent && mid_left_parent < r;
        bool right_valid = l < mid_right_parent && mid_right_parent < r;
 
        if (!left_valid && !right_valid)
            return current;
 
        if (left_valid && !right_valid)
            return simplest(l, r, mid_left_parent);
 
        return simplest(l, r, mid_right_parent);
    }
}
 
char is_calculated[1 << M];
fraction result[1 << M];
int used_counter;
int used[N];
int cycle_used[N];
int dfs_used[N];
int used_edges[M];
int allowed_edges[M];
vector<int> g[N];
 
fraction calc_value(fraction value, int color) {
    ll sign = color ? -1 : 1;
    ll l = 0;
    ll r = 30;
 
    while (r - l > 1) {
        ll i = (l + r) / 2ll;
        fraction calc_result = value + fraction(sign * i);
 
        if (calc_result.old_sign() == sign && abs(calc_result.numerator() / calc_result.denominator()) >= 1ll) {
            r = i;
        } else {
            l = i;
        }
    }
 
    ll to_divide = 1ll << (r - 1ll);
 
    return (value + fraction(sign * r)) / fraction(to_divide);
}
 
fraction dfs(int v) {
    dfs_used[v] = used_counter;
 
    fraction dfs_result;
 
    for (auto i: g[v]) {
        if (allowed_edges[i] != used_counter)
            continue;
 
        int u = edges[i].go(v);
        int color = edges[i].color;
 
        if (dfs_used[u] == used_counter)
            continue;
 
        fraction sub_result = dfs(u);
        fraction sub_result_on_edge = calc_value(sub_result, color);
 
        dfs_result += sub_result_on_edge;
    }
 
    return dfs_result;
}
 
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
 
bool has_cycle(int v, int p) {
    cycle_used[v] = used_counter;
 
    fora(i, g[v]) {
        if (allowed_edges[i] != used_counter || i == p)
            continue;
 
        int u = edges[i].go(v);
 
        if (cycle_used[u] == used_counter)
            return true;
 
        if (has_cycle(u, i))
            return true;
    }
 
    return false;
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
 
// fractions references, int and gcd - more!
// not M indeces -  only real edges set
// may be smaller graph - fast rebuild on query, not all graph with allowed
// may be no has_cycle
// may be no shifts - cache them
// simplest cache
 
int get_real_mask() {
    int answer = 0;
 
    forn(i, 0, M) {
        if (used_edges[i] == used_counter) {
            answer ^= 1 << i;
        }
    }
 
    return answer;
}
 
const fraction& solve(int mask) {
    if (!is_calculated[mask]) {
        is_calculated[mask] = 1;
        initialize(mask);
        check_edges(0);
 
        int real_mask = get_real_mask();
 
        if (real_mask < mask) {
            result[mask] = solve(real_mask);
        } else if (has_cycle(0, -1)) {
            fraction left(-987654), right(+987654);
 
            forn(i, 0, M) {
                int next_mask = mask ^ (1 << i);
 
                if (next_mask > mask) {
                    continue;
                }
 
                int color = edges[i].color;
                const fraction& next_result = solve(next_mask);
 
                if (color == 0) {
                    if (left < next_result)
                        left = next_result;
                } else {
                    if (next_result < right)
                        right = next_result;
                }
            }
 
            result[mask] = simplest(left, right, (left + right) / 2);
        } else {
            result[mask] = dfs(0);
        }
    }
 
    return result[mask];
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
 
    cout << solve((1 << m) - 1).answer();
 
    return 0;
}