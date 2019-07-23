#define REP(i, s, e) for (int i = s; i <= e ; i++)
#define DEBUG 
#define chkmax(a, b) a = max(a, b)

#include <bits/stdc++.h>
using namespace std;
const int maxn = 5e5 + 10;

int bg[maxn], ne[maxn], to[maxn], w[maxn], e;
void add(int x, int y, int z)
{
	e++;
	to[e] = y;
	ne[e] = bg[x];
	bg[x] = e;
	w[e] = z;
}

char s[maxn];
int n, fa[maxn], depth[maxn], siz[maxn], hvy[maxn], dfn[maxn], dfs_clock, back[maxn], ans[maxn];
int Xor[maxn], f[1 << 22];
void dfs1(int x)
{
	back[dfn[x] = ++dfs_clock] = x;
	siz[x] = 1;
	for (int i = bg[x]; i ; i = ne[i])
	{
		depth[to[i]] = depth[x] + 1;
		Xor[to[i]] = Xor[x] ^ w[i];
		dfs1(to[i]);
		siz[x] += siz[to[i]];
		if (siz[to[i]] > siz[hvy[x]]) hvy[x] = to[i];
	}
}
void dfs2(int x, bool keep)
{
	for (int i = bg[x]; i ; i = ne[i])
		if (to[i] ^ hvy[x])
		{
			dfs2(to[i], 0);
			chkmax(ans[x], ans[to[i]]);
		}
	if (hvy[x])
	{
		dfs2(hvy[x], 1);
		chkmax(ans[x], ans[hvy[x]]);
	}
	chkmax(f[Xor[x]], depth[x]);
	chkmax(ans[x], f[Xor[x]] - depth[x]);
	REP(i, 0, 21) chkmax(ans[x], f[Xor[x] ^ (1 << i)] - depth[x]);
	for (int i = bg[x]; i ; i = ne[i])
		if (to[i] ^ hvy[x])
		{
			REP(j, dfn[to[i]], dfn[to[i]] + siz[to[i]] - 1)
			{
				if (f[Xor[back[j]]])
					chkmax(ans[x], f[Xor[back[j]]] + depth[back[j]] - (depth[x] << 1));
				REP(k, 0, 21)
					if (f[Xor[back[j]]^(1<<k)]) chkmax(ans[x], f[Xor[back[j]]^(1<<k)] + depth[back[j]] - (depth[x] << 1));
			}
			REP(j, dfn[to[i]], dfn[to[i]] + siz[to[i]] - 1)
				chkmax(f[Xor[back[j]]], depth[back[j]]);
		}
	if (!keep) REP(i, dfn[x], dfn[x] + siz[x] - 1) f[Xor[back[i]]] = 0;
}

int main()
{
#ifndef ONLINE_JUDGE
	freopen("CF741D.in", "r", stdin);
	freopen("CF741D.out", "w", stdout);
#endif
	cin >> n;
	REP(i, 2, n)
	{
		scanf("%d %c\n", fa + i, s + i);
		add(fa[i], i, 1 << s[i] - 'a');
	}
	DEBUG;
	depth[1] = 1;
	dfs1(1);
	DEBUG;
	dfs2(1, 0);
	DEBUG;
	REP(i, 1, n) printf("%d%c", ans[i], i == n ? '\n' : ' ');
	return 0;
}
