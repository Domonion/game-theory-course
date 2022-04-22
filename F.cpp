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
 
const int N = 500;
const int K = 1000;
vec<int> g[N];
vec<int> rg[N];
int f[N];
int undefinedSons[N];
int start[K];
int instead[N];
set<int> kSet[N];
 
bool contains(const set<int> &where, int what) {
    return where.find(what) != where.end();
}
 
bool bad(int v) {
    return instead[v] != v;
}
 
int mex(const set<int> &grandi) {
    int cur = 0;
 
    fora(i, grandi) {
        if (i != cur)
            return cur;
        cur++;
    }
 
//    forn(i, 0, N + 1) {
//        if (!contains(grandi, i)) {
//            return i;
//        }
//    }
 
    return cur;
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
 
    int n, m, k, q;
    cin >> n >> m >> k >> q;
 
    forn(i, 0, k) {
        cin >> start[i];
        start[i]--;
    }
 
    forn(i, 0, n) {
        instead[i] = i;
    }
 
    forn(i, 0, m) {
        int from, to;
        cin >> from >> to;
        from--, to--;
        instead[from] = to;
    }
 
    forn(i, 0, n) {
        if (bad(i))
            continue;
 
        forn(j, 0, q) {
            int next = i + j + 1;
 
            if (next >= n)
                break;
 
            int insteadNext = instead[next];
            g[i].eb(insteadNext);
            rg[insteadNext].eb(i);
            undefinedSons[i]++;
        }
    }
 
    forn(i, 0, n) {
        f[i] = -1;
    }
 
    bool changed;
 
    do {
        changed = false;
 
        forn(v, 0, n) {
            // mogno hodit po vector indecs les & les
            if (bad(v))
                continue;
 
            if (f[v] != -1)
                continue;
 
            bool undefined = undefinedSons[v] != 0;
 
            // 3. рандом шафл + индксы по которым ходим
            // 4. проверка - за 1 контейнс
 
//            fora(u, g[v]) {
//                if (f[u] == -1) {
//                    undefined = true;
//                    break;
//                }
//            }
 
//            set<int> result; // no new sets every times
//
//            fora(u, g[v]) {
//                if (f[u] != -1) {
//                    result.insert(f[u]);
//                }
//            }
 
            int current = mex(kSet[v]);
            // mb first some operations - on related edges
 
            if (undefined == false) {
                f[v] = current;
                changed = true;
                fora(u, rg[v]) {
                    kSet[u].insert(current);
                    undefinedSons[u]--;
                }
            } else {
                bool allHasNext = true;
 
                fora(u, g[v]) {
                    // may be not counter -> set of next edges
                    if (f[u] != -1) {
                        continue;
                    }
 
                    bool hasCurrent = contains(kSet[u], current);
 
                    // this can be made as map!
//                    fora(next, g[u]) {
//                        if (f[next] == current) {
//                            hasCurrent = true;
//                            break;
//                        }
//                    }
 
                    if (!hasCurrent) {
                        allHasNext = false;
                        break;
                    }
                }
 
                if (allHasNext) {
                    changed = true;
                    f[v] = current;
                    fora(u, rg[v]) {
                        kSet[u].insert(current);
                        undefinedSons[u]--;
                    }
                }
            }
        }
    } while (changed);
 
    // 1 - n * n * log
//    forn(i, 0, n) {
//        if (f[i] != -1 || bad(i))
//            continue;
//
//        set<int> &result = kSet[i];
//
//        fora(u, g[i]) {
//            if (f[u] != -1) {
//                result.insert(f[u]);
//            }
//        }
//    }
 
    int undefinedCount = 0;
 
    forn(i, 0, k) {
        int curStart = start[i];
 
        if (f[curStart] == -1) {
            undefinedCount++;
        }
    }
 
 
    if (undefinedCount > 1) {
        cout << "Draw";
        return 0;
    }
 
    if (undefinedCount == 1) {
        int undefinedPlace;
        int undefinedIndex;
 
        forn(i, 0, k) {
            int curStart = start[i];
 
            if (f[curStart] == -1) {
                undefinedIndex = i;
                undefinedPlace = curStart;
                break;
            }
        }
 
        int result = 0;
 
        forn(i, 0, k) {
            int curStart = start[i];
 
            if (f[curStart] != -1) {
                result ^= f[curStart];
            }
        }
 
        if (contains(kSet[undefinedPlace], result)) {
            // win
            cout << "Arkadii\n";
            cout << undefinedIndex << ' ';
            forn(j, 0, size(g[undefinedPlace])) {
                int u = g[undefinedPlace][j];
 
                if (f[u] == result) {
                    cout << j + 1;
                    return 0;
                }
            }
 
            throw runtime_error("should be impossible");
        } else {
            cout << "Draw";
        }
 
        return 0;
    }
 
    int result = 0;
 
    forn(i, 0, k) {
        int curStart = start[i];
 
        result ^= f[curStart];
    }
 
    if (result == 0) {
        cout << "Boris";
        return 0;
    }
 
    cout << "Arkadii\n";
 
    forn(i, 0, k) {
        int curStart = start[i];
        int curF = f[curStart];
        int mustBecame = f[curStart] ^ result;
 
        if (curF > mustBecame) {
            forn(j, 0, size(g[curStart])) {
                int next = g[curStart][j];
                int nextF = f[next];
 
                if (nextF == mustBecame) {
                    cout << i + 1 << ' ' << j + 1;
                    return 0;
                }
            }
        }
    }
 
    // if more than 1 undefined - auto draw
    // if 1 undefined - xor all other games, check from undefined i has same game. has -> move from undefined here. otherwise draw
    // if no undefined - xor everything, if win -> i definetely have move from some vertex that will be correct flex, just check all.
    // more precise -> if result is X, then some Y should become Y^X, so must Y >= Y^X, and substract I must (Y - Y^X)
    // and because even on incorrect nims beucase it's value is mex of first-neighbour vertices -> i has Y^X < Y nim
    // if lose -> boris ofc
    return 1;
}