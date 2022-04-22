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
 
#ifndef big_integer_H
#define big_integer_H
#include <vector>
#include <string>
#include <climits>
#include <algorithm>
#include <cstring>
#include <cstdio>
#include <iostream>
#define size(a) (int((a).size()))
 
class big_integer {
 
private:
    bool minus;
    std::vector<unsigned int> num;
 
    void check();
 
public:
 
    const std::vector<unsigned int>& getNum() const {
        return num;
    }
 
    big_integer(std::vector<unsigned int> const &number, bool sign);
 
    big_integer();
 
    big_integer(big_integer const &other) = default;
 
    big_integer(int a);
 
    explicit big_integer(std::string s);
 
    ~big_integer() = default;
 
    big_integer inverse() const;
 
    big_integer(unsigned long long a);
 
    big_integer(unsigned int a);
 
    big_integer &operator=(big_integer const &other) = default;
 
    big_integer &operator+=(big_integer const &other);
 
    big_integer &operator-=(big_integer const &other);
 
    big_integer &operator/=(big_integer const &other);
 
    big_integer &operator%=(big_integer const &other);
 
    big_integer &operator*=(big_integer const &other);
 
    big_integer &operator&=(big_integer const &other);
 
    big_integer &operator|=(big_integer const &other);
 
    big_integer &operator^=(big_integer const &other);
 
    big_integer &operator<<=(unsigned int other);
 
    big_integer &operator>>=(unsigned int other);
 
    big_integer operator+() const;
 
    big_integer operator-() const;
 
    big_integer operator~() const;
 
    big_integer &operator++();
 
    big_integer operator++(int);
 
    big_integer &operator--();
 
    big_integer operator--(int);
 
    friend bool operator==(big_integer const &a, big_integer const &b);
 
    friend bool operator!=(big_integer const &a, big_integer const &b);
 
    friend bool operator<(big_integer const &a, big_integer const &b);
 
    friend bool operator>(big_integer const &a, big_integer const &b);
 
    friend bool operator<=(big_integer const &a, big_integer const &b);
 
    friend bool operator>=(big_integer const &a, big_integer const &b);
 
    friend std::string to_string(big_integer const &a);
 
    friend std::ostream &operator<<(std::ostream &s, big_integer const &a);
 
    friend big_integer operator+(big_integer a, big_integer const &b);
 
    friend big_integer operator-(big_integer a, big_integer const &b);
 
    friend big_integer operator*(big_integer, big_integer const &b);
 
    friend std::vector<unsigned int> divU(std::vector<unsigned int> const &, unsigned int b);
 
    friend big_integer operator/(big_integer, big_integer const &b);
 
    friend big_integer operator%(big_integer, big_integer const &b);
 
    friend big_integer operator&(big_integer, big_integer const &b);
 
    friend big_integer operator|(big_integer, big_integer const &b);
 
    friend big_integer operator^(big_integer, big_integer const &b);
 
    friend big_integer operator<<(big_integer, int b);
 
    friend big_integer operator>>(big_integer, int b);
};
 
void fastdiv(std::vector<unsigned int> const &a, std::vector<unsigned int> const &b, std::vector<unsigned int> & c);
 
bool isLess(std::vector<unsigned int> const &a, std::vector<unsigned int> const &b);
 
void add(std::vector<unsigned int> const &a, std::vector<unsigned int> const &b, std::vector<unsigned int> & res);
 
void sub(std::vector<unsigned int> const &a, std::vector<unsigned int> const &b, std::vector<unsigned int> & res);
 
void mul(std::vector<unsigned int> const &a, std::vector<unsigned int> const &b, std::vector<unsigned int> & res);
 
void and_long(std::vector<unsigned int> const &a, std::vector<unsigned int> const &b, std::vector<unsigned int> & res);
 
void or_long(std::vector<unsigned int> const &a, std::vector<unsigned int> const &b, std::vector<unsigned int> & res);
 
void xor_long(std::vector<unsigned int> const &a, std::vector<unsigned int> const &b, std::vector<unsigned int> & res);
 
void shift_left(std::vector<unsigned int> const &a, int b, std::vector<unsigned int> & res);
 
void shift_right(std::vector<unsigned int> const &a, int b, std::vector<unsigned int> & res);
 
std::vector<unsigned int> & correct(std::vector<unsigned int> & a);
 
#endif //big_integer_H
 
using namespace std;
 
typedef unsigned int uint;
typedef unsigned long long ull;
 
uint get(vector<uint> const &a, int i) {
    return (i < size(a) ? a[i] : 0);
}
 
void big_integer::check() {
    num = correct(num);
    if (num.back() == 0)
        minus = false;
}
 
big_integer::big_integer(vector<uint> const &number, bool sign) : minus(sign), num(number) {
    check();
}
 
big_integer::big_integer() : minus(false) {
    num.push_back(0);
}
 
big_integer::big_integer(int a) : minus(a < 0) {
    if (minus) {
        a++;
        a *= -1;
        num.push_back(static_cast<uint>(a) + 1);
    } else {
        num.push_back(a);
    }
}
 
big_integer::big_integer(ull a) : minus(false) {
    while (a) {
        num.push_back(a & UINT_MAX);
        a >>= sizeof(uint) * 8;
    }
}
 
big_integer::big_integer(uint a) : minus(false) {
    num.push_back(a);
}
 
big_integer::big_integer(string s) {
    big_integer res(0);
    reverse(s.begin(), s.end());
    minus = false;
    if (s.back() == '-')
        s.pop_back(), minus = true;
    while (!s.empty()) {
        res *= 10;
        res += s.back() - '0';
        s.pop_back();
    }
    num = res.num;
    check();
}
 
big_integer &big_integer::operator+=(big_integer const &b) {
    if (!minus && !b.minus) {
        minus = false;
        add(num, b.num, num);
    } else if (minus && b.minus) {
        minus = true;
        add(num, b.num, num);
    } else if (!minus && b.minus) {
        minus = isLess(num, b.num);
        sub(num, b.num, num);
    } else if (minus && !b.minus) {
        minus = isLess(b.num, num);
        sub(b.num, num, num);
    }
    return *this;
}
 
big_integer &big_integer::operator-=(big_integer const &b) {
    if (!minus && !b.minus) {
        minus = isLess(num, b.num);
        sub(num, b.num, num);
    } else if (minus && b.minus) {
        minus = isLess(b.num, num);
        sub(num, b.num, num);
    } else if (!minus && b.minus) {
        minus = false;
        add(num, b.num, num);
    } else if (minus && !b.minus) {
        minus = true;
        add(num, b.num, num);
    }
    return *this;
}
 
vector<uint> divU(vector<uint> const &a, uint b) {
    big_integer res;
    res.num.resize(size(a));
    ull carry = 0;
    for (int i = size(a) - 1; i >= 0; i--) {
        ull now = a[i] + (carry << 32);
        res.num[i] = now / b;
        carry = now % b;
    }
    correct(res.num);
    return res.num;
}
 
big_integer &big_integer::operator/=(big_integer const &b) {
    if (size(b.num) == 1) {
        num = divU(num, b.num[0]);
        minus ^= b.minus;
    } else if (b != 0) {
        if (isLess(num, b.num)) {
            num = vector<uint>(1, 0);
            minus = false;
        } else {
            minus = minus ^ b.minus;
            vector<uint> res;
            fastdiv(num, b.num, res);
            num = res;
        }
    }
    check();
    return *this;
}
 
big_integer &big_integer::operator%=(big_integer const &b) {
    big_integer buffer(*this);
    buffer /= b;
    buffer *= b;
    *this -= buffer;
    return *this;
}
 
big_integer &big_integer::operator*=(big_integer const &b) {
    minus ^= b.minus;
    mul(num, b.num, num);
    return *this;
}
 
big_integer &big_integer::operator&=(big_integer const &b) {
    vector<uint> lhs = (minus ? (inverse()).getNum() : getNum());
    vector<uint> rhs = (b.minus ? (b.inverse()).getNum() : b.getNum());
    and_long(lhs, rhs, num);
    if (minus) {
        num = this->inverse().getNum();
        minus = true;
    }
    return *this;
}
 
big_integer &big_integer::operator|=(big_integer const &b) {
    or_long((minus ? (inverse()).num : num),
            (b.minus ? (b.inverse()).num : b.num), num);
    minus |= b.minus;
    if (minus) {
        num = this->inverse().getNum();
        minus = true;
    }
    return *this;
}
 
big_integer &big_integer::operator^=(big_integer const &b) {
    xor_long((minus ? (inverse()).getNum() : getNum()),
             (b.minus ? (b.inverse()).getNum() : b.getNum()), num);
    minus ^= b.minus;
    if (minus) {
        num = this->inverse().getNum();
        minus = true;
    }
    return *this;
}
 
big_integer &big_integer::operator<<=(uint b) {
    shift_left(num, b,num );
    return *this;
}
 
big_integer &big_integer::operator>>=(uint b) {
    shift_right(num, b, num);
    if (minus)
        add(num, vector<uint>(1, 1), num);
    check();
    return *this;
}
 
big_integer big_integer::operator+() const {
    return *this;
}
 
big_integer big_integer::operator-() const {
    big_integer res(num, !minus);
    return res;
}
 
big_integer big_integer::operator~() const {
    big_integer res(*this);
    return -(res + 1);
}
 
big_integer &big_integer::operator++() {
    *this += 1;
    return *this;
}
 
big_integer big_integer::operator++(int) {
    big_integer res = *this;
    ++*this;
    return res;
}
 
big_integer &big_integer::operator--() {
    *this -= 1;
    return *this;
}
 
big_integer big_integer::operator--(int) {
    big_integer res = *this;
    ++*this;
    return res;
}
 
bool operator<(big_integer const &a_in, big_integer const &b_in) {
    bool cond = false;
    if (a_in.minus && b_in.minus)
        cond = true;
    if (a_in.minus && !b_in.minus)
        return true;
    if (!a_in.minus && b_in.minus)
        return false;
    big_integer const &a = (cond ? b_in : a_in);
    big_integer const &b = (cond ? a_in : b_in);
    return isLess(a.num, b.num);
}
 
bool operator>=(big_integer const &a, big_integer const &b) {
    return !(a < b);
}
 
bool operator==(big_integer const &a, big_integer const &b) {
    if (a.minus != b.minus)
        return false;
    return a.num == b.num;
}
 
bool operator>(big_integer const &a, big_integer const &b) {
    return b < a;
}
 
bool operator!=(big_integer const &a, big_integer const &b) {
    return !(a == b);
}
 
bool operator<=(big_integer const &a, big_integer const &b) {
    return !(a > b);
}
 
string to_string(big_integer const &a) {
    string res;
    big_integer buf = a;
    if (buf == 0)
        return "0";
    while (buf != 0) {
        res += to_string((buf % 10).getNum().back());
        buf /= 10;
    }
    if (a.minus)
        res.push_back('-');
    reverse(res.begin(), res.end());
    return res;
}
 
ostream &operator<<(ostream &os, big_integer const &a) {
    string output = to_string(a);
    os << a;
    return os;
}
 
big_integer operator+(big_integer a, big_integer const &b) {
    return a += b;
}
 
big_integer operator-(big_integer a, big_integer const &b) {
    return a -= b;
}
 
big_integer operator*(big_integer a, big_integer const &b) {
    return a *= b;
}
 
big_integer operator/(big_integer a, big_integer const &b) {
    return a /= b;
}
 
big_integer operator%(big_integer a, big_integer const &b) {
    return a %= b;
}
 
big_integer big_integer::inverse() const {
    big_integer res(*this);
    for (auto &i : res.num) i = UINT_MAX - i;
    res.minus ^= true;
    return res + 1;
}
 
big_integer operator&(big_integer a, big_integer const &b) {
    return a &= b;
}
 
big_integer operator|(big_integer a, big_integer const &b) {
    return a |= b;
}
 
big_integer operator^(big_integer a, big_integer const &b) {
    return a ^= b;
}
 
big_integer operator<<(big_integer a, int b) {
    return a <<= b;
}
 
big_integer operator>>(big_integer a, int b) {
    return a >>= b;
}
 
bool isLess(vector<uint> const &a, vector<uint> const &b) {
    if (size(a) < size(b))
        return true;
    if (size(a) > size(b))
        return false;
    return lexicographical_compare(a.rbegin(), a.rend(), b.rbegin(), b.rend());
}
 
inline vector<uint> &correct(vector<uint> &res) {
    while (size(res) > 1 && res.back() == 0)
        res.pop_back();
    return res;
}
 
void add(vector<uint> const &a, vector<uint> const &b, vector<uint> &res) {
    res.resize(max(size(a), size(b)) + 1);
    uint carry = 0;
    for (int i = 0; i < max(size(a), size(b)); i++) {
        uint val_a = get(a, i);
        uint val_b = get(b, i);
        res[i] = carry + val_a + val_b;
        if (UINT_MAX - val_a < val_b)
            carry = 1;
        else {
            carry = (UINT_MAX - val_a < val_b + carry);
        }
    }
    if (carry)
        res.back() = 1;
    correct(res);
}
 
void sub(vector<uint> const &a_in, vector<uint> const &b_in, vector<uint> &res) {
    bool cond = isLess(a_in, b_in);//sure???
    vector<uint> const &a = (cond ? b_in : a_in);
    vector<uint> const &b = (cond ? a_in : b_in);
    res.resize(size(a));
    for (int i = size(res) - 1; i >= 0; i--) {
        uint val_a = get(a, i);
        uint val_b = get(b, i);
        res[i] = val_a - val_b + (val_a < val_b) * UINT_MAX + (val_a < val_b);
        if (val_a < val_b) {
            int j = i + 1;
            while (res[j] == 0) {
                res[j]--;
                j++;
            }
            res[j]--;
        }
    }
    correct(res);
}
 
void mul(vector<uint> const &a, vector<uint> const &b, vector<uint> &c) {
    int n = size(a);
    c.resize(size(a) + size(b));
    c.back() = 0;
    int j = 0;
    uint carry = 0;
    ull cur = 0;
    for (int i = n - 1; i >= 0; --i) {
        uint ai = a[i];
        for (j = 0, carry = 0; j < size(b) || carry > 0; ++j) {
            cur = (ull) c[i + j] * (j != 0) + (ull) ai * (ull) get(b, j);
            c[i + j] = cur + carry;
            carry = (cur + carry) >> 32;
        }
    }
    correct(c);
}
 
void fastdiv(vector<uint> const &a_in, vector<uint> const &b_in, vector<uint> &Q) {
    const uint f = (uint) ((1ll << 32) / ull(b_in.back() + 1));
    Q.resize(0);
    vector<uint> a;
    mul(a_in, vector<uint>(1, f), a);
    vector<uint> b;
    mul(b_in, vector<uint>(1, f), b);
    int n = size(a);
    vector<uint> now;
    for (int i = n - 1; i >= 0; i--) {
        now.insert(now.begin(), a[i]);
        while (size(now) > 1 && now.back() == 0) {
            now.pop_back();
        }
        if (isLess(now, b)) {
            if (now.back() == 0)
                Q.push_back(0);
            continue;
        }
        ull digit1 = ull(now.back());
        if (size(now) != size(b)) {
            digit1 <<= 32;
            digit1 += now[size(now) - 2];
        }
        ull digit2 = b.back();
        ull digit = digit1 / digit2;
        digit = min(digit, (1ull << 32) - 1);
        vector<uint> buf;
        mul(b, vector<uint>(1, digit), buf);
        if (isLess(now, buf)) {
            sub(buf, b, buf);
            digit--;
        }
        if (isLess(now, buf)) {
            ull l = 0, r = digit;
            while (r - l > 1) {
                ull mid = (r + l) / 2;
                vector<uint> buffer;
                mul(b, vector<uint>(1, mid), buffer);
                if (isLess(now, buffer)) {
                    r = mid;
                } else
                    l = mid;
            }
            digit = l;
            mul(b, vector<uint>(1, digit), buf);
        }
        sub(now, buf, now);
        Q.push_back(digit);
    }
    reverse(Q.begin(), Q.end());
}
 
void and_long(vector<uint> const &a, vector<uint> const &b, vector<uint> & res) {
    res.resize(max(size(a), size(b)));
    for (int i = 0; i < size(res); i++)res[i] = get(a, i) & get(b, i);
    correct(res);
}
 
void or_long(vector<uint> const &a, vector<uint> const &b, vector<uint> & res) {
    res.resize(max(size(a), size(b)));
    for (int i = 0; i < size(res); ++i)res[i] = get(a, i) | get(b, i);
    correct(res);
}
 
void xor_long(vector<uint> const &a, vector<uint> const &b, vector<uint> & res) {
    res.resize(max(size(a), size(b)));
    for (int i = 0; i < size(res); i++)res[i] = get(a, i) ^ get(b, i);
    correct(res);
}
 
int getDeg(uint a) {
    int res = 0;
    while (a)
        res++, a /= 2;
    return res;
}
 
void shift_left(vector<uint> const &a, int b, vector<uint> & res) {
    int maxDeg = getDeg(a.back());
    int rem = b % 32;
    int carry = (maxDeg + rem > 32);
    res.resize(size(a) + b / 32 + carry);
    copy(a.begin(), a.end(), res.begin());
    for (int i = (int) size(res) - 1; i >= (int) size(res) - (int) size(a); i--) {
        res[i] <<= rem;
        if (i != (int) size(res) - (int) size(a))
            res[i] += res[i - 1] >> (32 - maxDeg);
    }
    //return res;
}
 
void shift_right(vector<uint> const &a, int b,vector<uint> & res) {
    res.resize(max(0, (int) size(a) - b / 32));
    copy(a.begin() + b / 32, a.end(), res.begin());
    if (res.empty())
        res.push_back(0);
    else {
        uint next = 0;
        for (int i = 0; i < b; i++)next *= 2, next += 1;
        for (int i = 0; i < size(res); i++) {
            res[i] >>= b;
            if (i != size(res) - 1)
                res[i] += (res[i + 1] & next) << (sizeof(uint) * 8 - b);
        }
    }
    correct(res);
    //return res;
}
 
struct edge {
    const int color;
    const int u, v;
 
    edge(int _color, int _v, int _u) : color(_color), u(_u), v(_v) {}
 
    int go(int vertex) const {
        if (v == vertex)
            return u;
 
        if (u == vertex) {
            return v;
        }
 
        throw runtime_error("keks");
    }
};
 
big_integer abs(const big_integer& a) {
    if (a < 0)
        return a * -1;
    return a;
}
 
struct fraction {
 
    fraction(big_integer v) : _numerator(v), _denominator(1) {}
 
    fraction() : _numerator(0), _denominator(1) {}
 
    string answer() {
        auto _gcd = gcd(abs(_numerator), abs(_denominator));
        return to_string(_numerator / _gcd) + " " + to_string(_denominator / _gcd);
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
 
        return *this;
    }
 
    fraction operator/=(const fraction &another) {
        _numerator *= another.denominator();
        _denominator *= another.numerator();
 
        return *this;
    }
 
    fraction operator/(const fraction &another) const {
        fraction result = *this;
 
        return result /= another;
    }
 
    big_integer denominator() const {
        return _denominator;
    }
 
    big_integer numerator() const {
        return _numerator;
    }
 
    big_integer sign() const {
        return sign(sign(numerator()) * sign(denominator()));
    }
 
private:
    big_integer _numerator, _denominator;
 
    static big_integer gcd(big_integer a, big_integer b) {
        return b != 0 ? gcd(b, a % b) : a;
    }
 
    static big_integer sign(big_integer a) {
        return a >= 0 ? 1 : -1;
    }
};
 
const int N = 1000;
vector<edge> g[N];
char used[N];
 
big_integer bin_pow(big_integer power) {
    if (size(power.getNum()) == 1 && power <= 30)
        return big_integer(1 << power.getNum().back());
 
    if (power % 2 == 1)
        return bin_pow(power - 1) * 2;
 
    auto result = bin_pow(power / 2);
 
    return result * result;
}
 
fraction calc_value(fraction value, int color) {
    big_integer sign = color ? -1 : 1;
    big_integer l = 0;
    big_integer r = 1000000;
 
    while(r - l > 1) {
        big_integer i = (l + r) / 2;
        fraction result = value + fraction(sign * i);
 
        if (result.sign() == sign && abs(result.numerator() / result.denominator()) >= 1) {
            r = i;
        }
        else {
            l = i;
        }
    }
 
    big_integer to_divide = bin_pow(r - 1);
 
    return (value + fraction(sign * r)) / fraction(to_divide);
}
 
fraction dfs(int v) {
    used[v] = 1;
 
    fraction result;
 
    for(auto e : g[v]) {
        int u = e.go(v);
        int color = e.color;
 
        if (used[u])
            continue;
 
        fraction sub_result = dfs(u);
        fraction sub_result_on_edge = calc_value(sub_result, color);
 
        result += sub_result_on_edge;
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
 
    int n;
    cin >> n;
 
    for(int i = 0; i < n - 1; i++) {
        int from, to, c;
        cin >> from >> to >> c;
        from--, to--;
        g[from].emplace_back(c, from, to);
        g[to].emplace_back(c, to, from);
    }
 
    cout << dfs(0).answer();
 
    return 0;
}