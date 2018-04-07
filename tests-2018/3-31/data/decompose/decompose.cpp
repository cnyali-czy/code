#include <bits/stdc++.h>

#define For(i, j, k) for (int i = j; i <= k; i++)

using namespace std;

typedef long long LL;

const int LEN = 4;
const int N = 1e5 + 10;
const LL oo = 1ll << 60;

int n, q, L;

struct Matrix {
	
	LL A[LEN][LEN];

	Matrix(int id = 0) {
		For(i, 0, L - 1) For(j, 0, L - 1) A[i][j] = -oo;
		if (id == 1) For(i, 0, L - 1) A[i][i] = 0;
	}

	LL* operator [] (int idx) { return A[idx]; }

	Matrix operator * (Matrix& B) {
		Matrix ret;
		For(i, 0, L - 1) For(j, 0, L - 1) For(k, 0, L - 1)
			ret[i][k] = max(ret[i][k], A[i][j] + B[j][k]);
		return ret;
	}

};

struct Segment_Tree {

	const static int NODE = N << 2;

	int lc[NODE], rc[NODE], sz[NODE], node;
	Matrix Info[NODE];

	#define M ((l + r) >> 1)

	void modify(int &o, int l, int r, int x, Matrix w) {
		if (!o) o = ++node;
		++sz[o];
		if (l == r) Info[o] = w;
		else {
			x <= M ? modify(lc[o], l, M, x, w) : modify(rc[o], M + 1, r, x, w);
			if (sz[o] >= r - l + 1) Info[o] = Info[rc[o]] * Info[lc[o]];
		}
	}

	#undef M

}T;

int Begin[N], Next[N], to[N], e;

void add(int u, int v) {
	to[++e] = v, Next[e] = Begin[u], Begin[u] = e;
}

int fa[N], son[N], sz[N], w[N][LEN];

void DFS_init(int o) {
	sz[o] = 1;
	for (int i = Begin[o]; i; i = Next[i]) {
		int u = to[i];
		DFS_init(u);
		sz[o] += sz[u];
		if (sz[u] > sz[son[o]]) son[o] = u;
	}
}

int top[N], bot[N], rt[N], len[N], id[N];
LL dp[N][LEN], sumv[N], f[N];

typedef multiset<LL, greater<LL>> Set;
typedef Set::iterator it;

Set S[N][LEN - 1];
it p[N][LEN - 1];

void calc_info(int o) {
	int g = top[o];
	Matrix A;
	if (son[o]) {
		For(j, 0, L - 2) A[j][j + 1] = w[o][j + 1] + sumv[o];
		For(i, 0, L - 1) For(j, 0, L - 1)
			A[i][j] = max(A[i][j], (j ? *S[o][j - 1].begin() : 0) + sumv[o] + w[o][j]);
	} else {
		A = Matrix(1);
	}
	T.modify(rt[g], 1, len[g], id[o], A);
}

void calc_dp(int o) {
	assert(o == top[o]);
	int u = bot[o];
	Matrix A = T.Info[rt[o]];
	f[o] = -oo;
	For(i, 0, L - 1) dp[o][i] = w[u][0] + A[0][i], f[o] = max(f[o], dp[o][i]);
}

void DFS_decompose(int o) {
	if (son[fa[o]] == o) {
		top[o] = top[fa[o]];
		id[o] = id[fa[o]] + 1;
	} else {
		top[o] = o;
		id[o] = 1;
	}
	int g = top[o];
	bot[g] = o, ++len[g];

	sumv[o] = 0;
	For(i, 0, L - 2) S[o][i].insert(-oo);
	for (int i = Begin[o]; i; i = Next[i]) {
		int u = to[i];
		if (u == son[o]) continue;
		DFS_decompose(u);
		sumv[o] += f[u];
		For(j, 0, L - 2) p[u][j] = S[o][j].insert(dp[u][j] - f[u]);
	}

	if (son[o]) DFS_decompose(son[o]);
	calc_info(o);

	if (o == g) calc_dp(o);
}

int main() {

	scanf("%d%d%d", &n, &q, &L);
	For(i, 2, n) scanf("%d", &fa[i]), add(fa[i], i);
	For(i, 1, n) For(j, 0, L - 1) scanf("%d", &w[i][j]);
	
	DFS_init(1);
	DFS_decompose(1);

	while (q--) {
		
		int o;
		scanf("%d", &o);
		For(i, 0, L - 1) scanf("%d", &w[o][i]);

		while (o) {
			calc_info(o);
			o = top[o];

			if (fa[o]) {
				sumv[fa[o]] -= f[o];
				For(i, 0, L - 2) S[fa[o]][i].erase(p[o][i]);
			}
			calc_dp(o);
			if (fa[o]) {
				sumv[fa[o]] += f[o];
				For(i, 0, L - 2) p[o][i] = S[fa[o]][i].insert(dp[o][i] - f[o]);
			}

			o = fa[o];
		}
		printf("%lld\n", f[1]);

	}

	return 0;
}
