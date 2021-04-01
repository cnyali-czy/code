#define REP(i, s, e) for (register int i(s), end_##i(e); i <= end_##i; i++)
#define DEP(i, s, e) for (register int i(s), end_##i(e); i >= end_##i; i--)
#define DEBUG fprintf(stderr, "Passing [%s] in Line %d\n", __FUNCTION__, __LINE__)

#include <algorithm>
#include <iostream>
#include <cstdio>
#define int long long
using namespace std;
const int maxn = 262250 + 10, MOD = 998244353;

int bg[maxn], ne[maxn << 1], to[maxn << 1], Fr[maxn << 1], To[maxn << 1], e = 1;
inline void add(int x, int y, int s, int t)
{
	e++;
	to[e] = y;
	ne[e] = bg[x];
	bg[x] = e;
	Fr[e] = s;
	To[e] = t;
}
int n, r[maxn], q;

int read()
{
	char c = getchar();int res = 0;
	while (!isdigit(c)) c = getchar();
	while ( isdigit(c)) res = res * 10 + (c - 48), c = getchar();
	return res;
}

inline int blg(int x) {return lower_bound(r + 1, r + 1 + n, x) - r;}

const int maxN = 1e6 + 10;
int F[maxN];
void init(int n)
{
	F[0] = F[1] = F[2] = 1;
	REP(i, 3, n)
		F[i] = (1 + (i - 2ll) * F[i - 1]) % MOD;
}
inline int f(int n)
{
	return F[n];
}
int X, Y, S, T;
int stk[maxn], top, ans, flg, rrs;
void dfs(int x)
{
	if (x == T)
	{
		ans = 1;
		REP(i, 1, top - 1)
		{
			int E = stk[i];
			if (Fr[stk[i + 1]] != To[E]) (ans *= f(r[to[E]] - r[to[E] - 1])) %= MOD;
		}
		rrs = ans;
		if (Fr[stk[1]]		!= X) (ans *= f(r[S] - r[S - 1])) %= MOD;
		if (To[stk[top]]	!= Y) (ans *= f(r[T] - r[T - 1])) %= MOD;
		flg = 1;
		return;
	}
	if (flg) return;
	for (int i = bg[x]; i; i = ne[i]) if (i ^ stk[top] ^ 1)
	{
		stk[++top] = i;
		dfs(to[i]);
		if (flg) return;
		top--;
	}
}

namespace Tree
{
	/*
	int siz[maxn], hvy[maxn], top[maxn], fa[maxn], dep[maxn];
	void dfs1(int x)
	{
		siz[x] = 1;
		for (int i = bg[x]; i; i = ne[i]) if (to[i] ^ fa[x])
		{
			fa[to[i]] = x;
			dep[to[i]] = dep[x] + 1;
			dfs1(to[i]);
			siz[x] += siz[to[i]];
			if (siz[to[i]] > siz[hvy[x]]) hvy[x] = to[i];
		}
	}
	int dfn[maxn], dfs_clock, back[maxn];
	void dfs2(int x, int y)
	{
		back[dfn[x] = ++dfs_clock] = x;
		top[x] = y;
		if (!hvy[x]) return ;
		dfs2(hvy[x], y);
		for (int i = bg[x]; i; i = ne[i]) if (to[i] ^ fa[x] && to[i] ^ hvy[x])
			dfs2(to[i], to[i]);
	}
	*/

	struct Node
	{
		//edge upon node
		int s, t, ans;
		Node() {}
		Node(int s, int t, int ans) : s(s), t(t), ans(ans) {}
	};
	inline Node operator + (Node A, Node B)
	{
		int s = A.s, t = B.t, ans = A.ans * B.ans % MOD;
		if (To[A.t] != Fr[B.s]) (ans *= f(r[to[A.t]] - r[to[A.t] - 1])) %= MOD;
		return Node(s, t, ans);
	}
	const int L = 22;
	int anc[maxn][L + 1], dep[maxn], wfa[maxn];
	void dfs1(int x)
	{
		dep[x] = dep[anc[x][0]] + 1;
		for (int i = bg[x]; i; i = ne[i]) if (to[i] ^ anc[x][0])
		{
			wfa[to[i]] = i;
			anc[to[i]][0] = x;
			dfs1(to[i]);
		}
	}
	Node up[maxn][L + 1], dw[maxn][L + 1];
	void init()
	{
		dfs1(1);
		REP(i, 2, n)
		{
			up[i][0] = Node(wfa[i] ^ 1, wfa[i] ^ 1, 1);
			dw[i][0] = Node(wfa[i], wfa[i], 1);
		}
		REP(j, 1, L)
			REP(x, 1, n)
			{
				anc[x][j] = anc[anc[x][j - 1]][j - 1];
				up[x][j] = up[x][j - 1] + up[anc[x][j - 1]][j - 1];
				dw[x][j] = dw[anc[x][j - 1]][j - 1] + dw[x][j - 1];
			}
	//	dfs1(1);dfs2(1, 1);
	}
	int lca(int x, int y)
	{
		if (dep[x] < dep[y]) swap(x, y);
		DEP(i, L, 0) if (dep[anc[x][i]] >= dep[y]) x = anc[x][i];
		if (x == y) return x;
		DEP(i, L, 0) if (anc[x][i] ^ anc[y][i]) x = anc[x][i], y = anc[y][i];
		return anc[x][0];
	}
	int kthanc(int x, int k)
	{
		DEP(i, L, 0) if (k >> i & 1) x = anc[x][i];
		return x;
	}
	int Lca;
	int query(int x, int y)
	{
		static Node fk[2333];
		int T = 0, l = lca(x, y);
		Lca = l;
		bool flg = 0;
		DEP(i, L, 0)
			if (dep[anc[x][i]] >= dep[l])
			{
				if (!T) fk[++T] = up[x][i];
				else fk[1] = fk[1] + up[x][i];
				flg = 1;
				x = anc[x][i];
			}
		DEP(i, L, 0)
			if (dep[anc[y][i]] >= dep[l])
			{
				fk[++T] = dw[y][i];
				y = anc[y][i];
			}
		if (flg)
		{
			DEP(i, T, 2) fk[1] = fk[1] + fk[i];
			return fk[1].ans;
		}
		else
		{
			DEP(i, T - 1, 1) fk[T] = fk[T] + fk[i];
			return fk[T].ans;
		}
	}
}
using Tree :: dep ;

signed main()
{
#ifndef ONLINE_JUDGE
	freopen("d.in", "r", stdin);
	freopen("d.out", "w", stdout);
#endif
	n = read();
	REP(i, 1, n) r[i] = read();
	init(maxN - 10);
	REP(i, 1, n - 1)
	{
		int x = read(), y = read();
		add(blg(x), blg(y), x, y);
		add(blg(y), blg(x), y, x);
	}
	Tree :: init();
	q = read();
	REP(Case, 1, q)
	{
		int x = read(), y = read(), bx = blg(x), by = blg(y);
		if (x == y) puts("1");
		else if (bx == by) printf("%lld\n", f(r[bx] - r[bx - 1]));
		else
		{
			X = x;Y = y;S = blg(x);T = blg(y);
			top = ans = flg = 0;
			if (0 && n * q <= 16 * 262244) dfs(S);
			else
			{
				ans = Tree :: query(S, T);
				int l = Tree :: Lca;
				int es = 0, et = 0;
				if (S != l) es = Tree :: wfa[S] ^ 1;
				else
				{
					int z = Tree :: kthanc(T, dep[T] - dep[S] - 1);
					es = Tree :: wfa[z];
				}
				if (T != l) et = Tree :: wfa[T];
				else
				{
					int z = Tree :: kthanc(S, dep[S] - dep[T] - 1);
					et = Tree :: wfa[z] ^ 1;
				}
				if (Fr[es]	!= X) (ans *= f(r[S] - r[S - 1])) %= MOD;
				if (To[et]	!= Y) (ans *= f(r[T] - r[T - 1])) %= MOD;
			}
			printf("%lld\n", ans);
		}
	}
	return 0;
}
