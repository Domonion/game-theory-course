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
 
const int N = 50;
const int M = 250000;
char type[N][N][N][N][2];
char bad[N][N];
int deg[N][N][N][N][2];
char used[N][N][N][N][2];
int gox[8] = {0, 1, 1, 1, 0, -1, -1, -1};
int goy[8] = {1, 1, 0, -1, -1, -1, 0, 1};
int n, m;
 
bool valid(int x, int y) {
    return x >= 0 && x < n && y >= 0 && y < n && !bad[x][y];
}
 
bool valid2(int x, int y, int x2, int y2) {
    return !(x == x2 && y == y2);
}
 
char color(int who) {
    if (who == 0)
        return 'w';
    else
        return 'b';
}
 
void dfs(int xw, int yw, int xb, int yb, int who) {
    used[xw][yw][xb][yb][who] = 1;
//    cout << "POSITION: " << xw << " " << yw << ' ' << xb << ' ' << yb << ' ' << who << endl;
    int whoPrev = !who;
    char curWin = type[xw][yw][xb][yb][who];
 
    // if whoPrev == type -> all his moves here are win
    // if whoPrev != type -> reduce by one
 
    if (color(whoPrev) == curWin)
    {
        forn(step, 0, 8) {
            if (whoPrev == 0) {
                int prevxw = xw + gox[step], prevyw = yw + goy[step];
                if (valid(prevxw, prevyw) && valid2(prevxw, prevyw, xb, yb)) {
                    if (!used[prevxw][prevyw][xb][yb][whoPrev]) {
                        type[prevxw][prevyw][xb][yb][whoPrev] = type[xw][yw][xb][yb][who];
                        dfs(prevxw, prevyw, xb, yb, whoPrev);
                    }
                }
            } else {
                int prevxb = xb + gox[step], prevyb = yb + goy[step];
                if (valid(prevxb, prevyb) && valid2(xw, yw, prevxb, prevyb)) {
                    if (!used[xw][yw][prevxb][prevyb][whoPrev]) {
                        type[xw][yw][prevxb][prevyb][whoPrev] = type[xw][yw][xb][yb][who];
                        dfs(xw, yw, prevxb, prevyb, whoPrev);
                    }
                }
            }
        }
    }
    else {
        forn(step, 0, 8) {
            if (whoPrev == 0) {
                int prevxw = xw + gox[step], prevyw = yw + goy[step];
                if (valid(prevxw, prevyw) && valid2(prevxw, prevyw, xb, yb)) {
                    if (!used[prevxw][prevyw][xb][yb][whoPrev] &&
                        --deg[prevxw][prevyw][xb][yb][whoPrev] == 0) {
                        type[prevxw][prevyw][xb][yb][whoPrev] = type[xw][yw][xb][yb][who];
                        dfs(prevxw, prevyw, xb, yb, whoPrev);
                    }
                }
            } else {
                int prevxb = xb + gox[step], prevyb = yb + goy[step];
                if (valid(prevxb, prevyb) && valid2(xw, yw, prevxb, prevyb)) {
                    if (!used[xw][yw][prevxb][prevyb][whoPrev] &&
                        --deg[xw][yw][prevxb][prevyb][whoPrev] == 0) {
                        type[xw][yw][prevxb][prevyb][whoPrev] = type[xw][yw][xb][yb][who];
                        dfs(xw, yw, prevxb, prevyb, whoPrev);
                    }
                }
            }
        }
    }
 
//    fora(u, g[v]) {
//        if (used[u])
//            continue;
//
//        if (type[v] == 'l')
//            type[u] = 'w';
//        else if (--deg[u] == 0)
//            type[u] = 'l';
//        else
//            continue;
//        dfs(u);
//    }
}
 
char win(int who) {
    if (who == 0)
        return 'b';
    else
        return 'w';
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
    cin >> n >> m;
    int sxw, syw, sxb, syb;
    cin >> sxw >> syw >> sxb >> syb;
    sxw--, syw--, sxb--, syb--;
 
    forn(i, 0, m) {
        int from, to;
        cin >> from >> to;
        from--, to--;
        bad[from][to] = 1;
    }
 
    forn(x, 0, n) {
        forn(y, 0, n) {
            forn(who, 0, 2) {
                type[x][y][x][y][who] = win(who);
            }
        }
    }
 
    forn(xw, 0, n) {
        forn(yw, 0, n) {
            if (bad[xw][yw])
                continue;
 
            forn(xb, 0, n) {
                forn(yb, 0, n) {
                    if (bad[xb][yb])
                        continue;
 
                    forn(who, 0, 2) {
                        if (type[xw][yw][xb][yb][who])
                            continue;
 
                        forn(step, 0, 8) {
                            if (who == 0) {
                                int nextxw = xw + gox[step], nextyw = yw + goy[step];
                                if (valid(nextxw, nextyw))
                                    deg[xw][yw][xb][yb][who]++;
                            } else {
                                int nextxb = xb + gox[step], nextyb = yb + goy[step];
                                if (valid(nextxb, nextyb))
                                    deg[xw][yw][xb][yb][who]++;
                            }
                        }
                    }
 
                }
            }
        }
    }
 
    forn(xw, 0, n) {
        forn(yw, 0, n) {
            if (bad[xw][yw])
                continue;
 
            forn(xb, 0, n) {
                forn(yb, 0, n) {
                    if (bad[xb][yb])
                        continue;
 
//                    cout << "START: " << xb << ' ' << yw << ' ' << xb << ' ' << yb << endl;
                    forn(who, 0, 2) {
                        if (!used[xw][yw][xb][yb][who] && type[xw][yw][xb][yb][who]) {
//                            cout << "START: " << xb << ' ' << yw << ' ' << xb << ' ' << yb << ' ' << who << endl;
                            dfs(xw, yw, xb, yb, who);
                        }
                    }
                }
            }
        }
    }
//
//    forn(xw, 0, n) {
//        forn(yw, 0, n) {
//            if (bad[xw][yw])
//                continue;
//
//            forn(xb, 0, n) {
//                forn(yb, 0, n) {
//                    if (bad[xb][yb])
//                        continue;
//
//                    forn(who, 0, 2) {
//                        if (!used[xw][yw][xb][yb][who] && type[xw][yw][xb][yb][who])
//                            dfs(xw, yw, xb, yb, who);
//                    }
//                }
//            }
//        }
//    }
 
    if (type[sxw][syw][sxb][syb][0] == 'w')
        cout << "White\n";
    else if (type[sxw][syw][sxb][syb][0] == 'b')
        cout << "Black\n";
    else
        cout << "Draw\n";
 
    return 0;
}