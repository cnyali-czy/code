/*
	Problem:	C.cpp
	Time:		2021-03-07 10:55
	Author:		CraZYali
	E-Mail:		yms-chenziyang@outlook.com 
*/

#define REP(i, s, e) for (register int i(s), end_##i(e); i <= end_##i; i++)
#define DEP(i, s, e) for (register int i(s), end_##i(e); i >= end_##i; i--)
#define DEBUG fprintf(stderr, "Passing [%s] in Line %d\n", __FUNCTION__, __LINE__)

#define chkmax(a, b) (a < (b) ? a = (b) : a)
#define chkmin(a, b) (a > (b) ? a = (b) : a)

#include <cassert>
#include <vector>
#include <cstring>
#include <algorithm>
#include <iostream>
#include <cstdio>
#define i64 long long
#define u64 unsigned i64

using namespace std;
const int maxn = 2500 + 10, MOD = 998244353;

int bg[maxn], ne[maxn << 1], to[maxn << 1], e;
string w[maxn << 1];
inline void add(int x, int y, string z)
{
	e++;
	to[e] = y;
	ne[e] = bg[x];
	bg[x] = e;
	w[e] = z;
}

	template <typename T>
inline T read()
{
	T ans = 0, flag = 1;
	char c = getchar();
	while (!isdigit(c))
	{
		if (c == '-') flag = -1;
		c = getchar();
	}
	while (isdigit(c))
	{
		ans = ans * 10 + c - 48;
		c = getchar();
	}
	return ans * flag;
}

#define file(FILE_NAME) freopen(FILE_NAME".in", "r", stdin), freopen(FILE_NAME".out", "w", stdout)

int n, m, q;

int ch[233][26], fail[233], End[233], cur = 1;
void ins(string s, int id)
{
	int p = 1;
	REP(i, 0, (int)s.size() - 1)
	{
		int c = s[i] - 'a';
		if (!ch[p][c]) ch[p][c] = ++cur;
		p = ch[p][c];
	}
	End[p] = 1;
}
void build()
{
	static int que[233];int head, tail;
	que[head = tail = 0] = 1;
	REP(i, 0, 25) ch[0][i] = 1;
	while (head <= tail)
	{
		int x = que[head++];
		REP(i, 0, 25)
			if (ch[x][i])
			{
				fail[ch[x][i]] = ch[fail[x]][i];
				que[++tail] = ch[x][i];
			}
			else ch[x][i] = ch[fail[x]][i];
	}
	++cur;
	REP(i, 0, 25) ch[cur][i] = cur;
	REP(i, 1, cur - 1)
	{
		REP(j, 0, 25)
		{
			bool flg = 0;
			for (int x = ch[i][j]; x; x = fail[x]) if (End[x]) {flg = 1;break;}
			if (flg) ch[i][j] = cur;
		}
	}
}
int fa[maxn], ifa[maxn], T;
bool flg = 0;
void dfs(int x)
{
	if (x == T) flg = 1;
	if (flg) return;
	for (int i = bg[x]; i; i = ne[i]) if (to[i] ^ fa[x])
	{
		fa[to[i]] = x;
		ifa[to[i]] = i;
		dfs(to[i]);
	}
}

const u64 LIM = 18e18 / 26 / 45;

struct Matrix
{
	int n, m;
	int a[43][43];
	Matrix() {}
	Matrix(int n, int m) : n(n), m(m)
	{
		REP(i, 1, n) REP(j, 1, m) a[i][j] = 0;
	}
};
Matrix operator * (Matrix A, Matrix B)
{
	Matrix res(A.n, B.m);
	assert(A.m == B.n);
	REP(i, 1, A.n) REP(k, 1, A.m) if (A.a[i][k])
		REP(j, 1, B.m) if (B.a[k][j]) res.a[i][j] = (res.a[i][j] + 1ll * A.a[i][k] * B.a[k][j]) % MOD;
	return res;
}
Matrix jjs(string s)
{
	Matrix res(cur, cur);
	REP(i, 1, cur) for (register auto c : s) res.a[i][ch[i][c - 'a']]++;
	return res;
}

Matrix up[maxn][12], down[maxn][12];
int anc[maxn][12], dep[maxn];
void dfs0(int x)
{
	dep[x] = dep[anc[x][0]] + 1;
	REP(i, 1, 11)
	{
		anc[x][i] = anc[anc[x][i - 1]][i - 1];
		if (!anc[x][i]) break;
		up[x][i] = up[x][i - 1] * up[anc[x][i - 1]][i - 1];
		down[x][i] = down[anc[x][i - 1]][i - 1] * down[x][i - 1];
	}
	for (int i = bg[x]; i; i = ne[i]) if (to[i] ^ anc[x][0])
	{
		anc[to[i]][0] = x;
		down[to[i]][0] = up[to[i]][0] = jjs(w[i]);
		dfs0(to[i]);
	}
}
int lca(int u, int v)
{
	if (dep[u] < dep[v]) swap(u, v);
	DEP(i, 11, 0) if (dep[anc[u][i]] >= dep[v]) u = anc[u][i];
	if (u == v) return u;
	DEP(i, 11, 0) if (anc[u][i] ^ anc[v][i]) u = anc[u][i], v = anc[v][i];
	return anc[u][0];
}

int main()
{
#ifdef CraZYali
	file("C");
#endif
	cin >> n >> m >> q;
	REP(i, 2, n)
	{
		int x = read<int>(), y = read<int>();
		string z;cin >> z;
		sort(z.begin(), z.end());
		add(x, y, z);add(y, x, z);
	}
	REP(i, 1, m)
	{
		string z;
		cin >> z;
		ins(z, i);
	}
	build();
	dfs0(1);
	
	while (q--)
	{
		int u, v;cin >> u >> v;
		/*
//		T = u;flg = 0;dfs(v);
		static int que[maxn], head, tail;
		REP(i, 0, tail) fa[que[i]] = 0;
		que[head = tail = 0] = v;
		while (head <= tail)
		{
			int x = que[head++];
			for (int i = bg[x]; i; i = ne[i]) if (to[i] ^ fa[x])
			{
				fa[to[i]] = x;
				ifa[to[i]] = i;
				que[++tail] = to[i];
				if (to[i] == u) goto gg;
			}
		}
gg:;
		REP(i, 1, n) fa[i] = 0;
		flg = 0;T = u;dfs(v);

		static u64 f[43], g[43];
		REP(i, 1, cur) f[i] = 0;
		f[1] = 1;
		for (int x = u; x != v; x = fa[x])
		{
			REP(i, 1, cur)
			{
				if (f[i] >= LIM) f[i] %= MOD;
				g[i] = f[i];f[i] = 0;
			}
			REP(i, 1, cur) if (g[i])
				for (register auto c : w[ifa[x]]) f[ch[i][c - 'a']] += g[i];
		}
		cout << f[cur] % MOD << '\n';
		*/
		int l = lca(u, v);
		Matrix ans(1, cur);ans.a[1][1] = 1;
		int x = u;
		DEP(i, 11, 0) if (dep[anc[x][i]] >= dep[l])
		{
			ans = ans * up[x][i];
			x = anc[x][i];
		}
//		for (int x = u; x != l; x = anc[x][0]) ans = ans * up[x][0];
		static Matrix fk[maxn];int m = 0;
		x = v;
		DEP(i, 11, 0) if (dep[anc[x][i]] >= dep[l])
		{
			fk[++m] = down[x][i];
			x = anc[x][i];
		}
//		for (int x = v; x != l; x = anc[x][0]) fk[++m] = x;
		DEP(i, m, 1) ans = ans * fk[i];
		cout << ans.a[1][cur] << endl;	
	}
	return 0;
}
