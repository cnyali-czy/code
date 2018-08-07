#include <bits/stdc++.h>

#define getchar getchar_unlocked
#define For(i, j, k) for (int i = j; i <= k; i++)
#define Forr(i, j, k) for (int i = j; i >= k; i--)

using namespace std;

int Read() {
	char c = getchar(); int x = 0;
	while (c > '9' || c < '0') c = getchar();
	while (c >= '0' && c <= '9') x = x * 10 + c - '0', c = getchar();
	return x;
}

const int N = 1e5 + 10;
const int Mod = 1e9 + 7;

int Begin[N], Next[N << 1], to[N << 1], e = 3;

void add(int u, int v) {
	to[++e] = v, Next[e] = Begin[u], Begin[u] = e;
}

int n, q;
int cnt[N << 1], sz[N], w[N], fa[N];
int ans;

void DFS_init(int o) {
	sz[o] = 1;
	for (int i = Begin[o]; i; i = Next[i]) {
		int u = to[i];
		if (u == fa[o]) continue;
		DFS_init(u);
		ans = (ans + 1ll * sz[u] * (n - sz[u]) % Mod * w[u] % Mod * w[u]) % Mod;
		cnt[i] = sz[u], cnt[i ^ 1] = n - sz[u];
		sz[o] += sz[u];
	}
}

bool vis[N];
int minsz, nowsz, cen;
int calc_cnt;

void DFS_Centroid(int o, int f) {
	int mx = 0;
	sz[o] = 1;
	for (int i = Begin[o]; i; i = Next[i]) {
		int u = to[i];
		if (vis[u] || u == f) continue;
		DFS_Centroid(u, o);
		sz[o] += sz[u];
		mx = max(mx, sz[u]);
	}
	mx = max(mx, nowsz - sz[o]);
	if (mx < minsz) minsz = mx, cen = o;
}

int sub[N][22], sum[N];
int c[N], g[N][22], bel[N][22], coe[N][22];

void DFS_calc(int o, int f, int d, int id) {
	int u = f / 2;
	c[u] = d, g[u][d] = cen, bel[u][d] = id;
	sub[id][d] = (sub[id][d] + 1ll * cnt[f ^ 1] * w[u]) % Mod;
	coe[u][d] = cnt[f ^ 1];
	if (vis[o]) return;
	sz[o] = 1;
	for (int i = Begin[o]; i; i = Next[i]) {
		if (i == f) continue;
		DFS_calc(to[i], i ^ 1, d, id);
		if (!vis[to[i]]) sz[o] += sz[to[i]];
	}
}

void Divide_Conquer(int rt, int _n, int d) {
	nowsz = minsz = _n, cen = rt;
	DFS_Centroid(rt, 0);
	int o = cen;
	vis[o] = true;

	assert(sum[o] == 0);
	for (int i = Begin[o]; i; i = Next[i]) {
		int u = to[i], id = i / 2;
		DFS_calc(u, i ^ 1, d, id);
		ans = (ans + 2ll * sub[id][d] * sum[o]) % Mod;
		sum[o] = (sum[o] + sub[id][d]) % Mod;
	}

	for (int i = Begin[o]; i; i = Next[i]) {
		int u = to[i];
		if (vis[u]) continue;
		Divide_Conquer(u, sz[u], d + 1);
	}
}

int main() {

	Read();
	n = Read(), q = Read();
	For(i, 2, n) fa[i] = Read(), w[i] = Read(), add(i, fa[i]), add(fa[i], i); 

	DFS_init(1);
	Divide_Conquer(1, n, 1);
	printf("%d\n", ans);

	while (q--) {
		int x = Read(), cw = Read();
		For(i, 1, c[x]) {
			int o = g[x][i], id = bel[x][i];
			int delt = 1ll * coe[x][i] * cw % Mod;
			ans = (ans + 2ll * (Mod + sum[o] - sub[id][i]) * delt) % Mod;
			sub[id][i] = (sub[id][i] + delt) % Mod;
			sum[o] = (sum[o] + delt) % Mod;
		}
		ans = (ans + (2ll * w[x] + cw) * cw % Mod * cnt[x << 1 | 1] % Mod * cnt[x << 1]) % Mod;
		w[x] = (w[x] + cw) % Mod;
		printf("%d\n", ans);
	}

	return 0;
}
