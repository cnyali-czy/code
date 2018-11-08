#include <bits/stdc++.h>
#define  REP(i, s, e) for(register int i = s; i <= e ;i++)

using namespace std;

#define fst first
#define snd second
#define squ(x) ((LL)(x) * (x))
#define debug(...) fprintf(stderr, __VA_ARGS__)

typedef long long LL;
typedef pair<int, int> pii;

inline int read() {
    int sum = 0, fg = 1; char c = getchar();
    for (; !isdigit(c); c = getchar()) if (c == '-') fg = -1;
    for (; isdigit(c); c = getchar()) sum = (sum << 3) + (sum << 1) + (c ^ 0x30);
    return fg * sum;
}

const int maxn = 1e5 + 10;
const int maxm = 2e5 + 10;
const int maxk = 51;

struct graph {
    int Begin[maxn], Next[maxm], To[maxm], w[maxm], e;
    void init() { e = -1, memset(Begin, -1, sizeof Begin); }
    void add(int x, int y, int z) { To[++e] = y, Next[e] = Begin[x], Begin[x] = e, w[e] = z; }
}g, _g;

int f[maxn][maxk], d[maxn], mod;
bool v[maxn], hk, vis[maxn][maxk];

inline int add(int x, int y) { return (x += y) < mod ? x : x - mod; }

void dijkstra(int s) {
    memset(v, 0, sizeof v);
    memset(d, 0x3f, sizeof d), d[s] = 0;
    priority_queue<pii, vector<pii>, greater<pii> > pq;
    pq.push((pii){0, s});
    while (!pq.empty()) {
        int now = pq.top().snd; pq.pop();
        if (v[now]) continue; v[now] = 1;
        for (int i = g.Begin[now]; i + 1; i = g.Next[i]) {
            int son = g.To[i], ds = g.w[i];
            if (d[now] + ds < d[son]) {
                d[son] = d[now] + ds;
                pq.push((pii){d[son], son});
            }
        }
    }
}

int dfs(int now, int k) {
    if (~f[now][k]) return f[now][k];
    if (now == 1 && k == 0) f[now][k] = 1;
    else f[now][k] = 0;
    vis[now][k] = 1;
    for (int i = _g.Begin[now]; i + 1; i = _g.Next[i]) {
        int son = _g.To[i], ds = _g.w[i], tmp = d[now] + k - ds - d[son];
        if (tmp < 0) continue;
        if (vis[son][tmp]) hk = 1;
        f[now][k] = add(f[now][k], dfs(son, tmp));
    }
    vis[now][k] = 0;
    return f[now][k];
}

int main() {
	freopen("3953.in", "r", stdin);
    freopen("std.out", "w", stdout);

    int T = read();
    while (T--) {
        g.init(), _g.init();
        int n = read(), m = read(), k = read(), ans = 0;
        mod = read();
        for (int i = 1; i <= m; i++) {
            int x = read(), y = read(), z = read();
            g.add(x, y, z), _g.add(y, x, z);
        }
        dijkstra(1); memset(f, -1, sizeof f), hk = 0;
        for (int i = 0; i <= k; i++) ans = add(ans, dfs(n, i));
        printf("%d\n", hk ? -1 : ans);
    }

    return 0;
}
