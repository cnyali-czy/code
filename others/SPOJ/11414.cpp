/*
	Problem:	11414.cpp
	Time:		2020-03-22 09:55
	Author:		CraZYali
	E-Mail:		yms-chenziyang@outlook.com 
*/

#define REP(i, s, e) for (register int i(s), end_##i(e); i <= end_##i; i++)
#define DEP(i, s, e) for (register int i(s), end_##i(e); i >= end_##i; i--)
#define DEBUG fprintf(stderr, "Passing [%s] in Line %d\n", __FUNCTION__, __LINE__)

#define chkmax(a, b) (a < (b) ? a = (b) : a)
#define chkmin(a, b) (a > (b) ? a = (b) : a)

#include <vector>
#include <algorithm>
#include <iostream>
#include <cstdio>

using namespace std;
const int maxn = 1e5 + 10;

int bg[maxn], ne[maxn << 1], to[maxn << 1], e;
inline void add(int x, int y)
{
	e++;
	to[e] = y;
	ne[e] = bg[x];
	bg[x] = e;
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

int n;
bool c[maxn];

int sg[maxn];
vector <int> ans;

const int maxN = 2e7;
int ch[maxN][2], tag[maxN], cur, rt[maxn];
bool flag[maxN];

int newtrie(int val, int dep)
{
	int p = ++cur;
	if (dep == -1)
	{
		flag[p] = 1;
		return p;
	}
	ch[p][val >> dep & 1] = newtrie(val, dep - 1);
	return p;
}
void pushdown(int p, int dep)
{
	if (tag[p] >> dep & 1) swap(ch[p][0], ch[p][1]);
	if (ch[p][0]) tag[ch[p][0]] ^= tag[p];
	if (ch[p][1]) tag[ch[p][1]] ^= tag[p];
	tag[p] = 0;
}
void pushup(int p)
{
	flag[p] |= (flag[ch[p][0]] & flag[ch[p][1]]);
}
int merge(int u, int v, int dep)
{
	if (!u || !v) return u + v;
	if (dep == -1) return u;
	if (tag[u]) pushdown(u, dep);
	if (tag[v]) pushdown(v, dep);
	ch[u][0] = merge(ch[u][0], ch[v][0], dep - 1);
	ch[u][1] = merge(ch[u][1], ch[v][1], dep - 1);
	pushup(u);
	return u;
}
int search_mex(int p, int dep)
{
	if (dep == -1) return 0;
	if (tag[p]) pushdown(p, dep);
	if (flag[ch[p][0]]) return search_mex(ch[p][1], dep - 1) | (1 << dep);
	else return search_mex(ch[p][0], dep - 1);
}
int s[maxn];
void dfs1(int x, int fa = 0)
{
	for (int i = bg[x]; i; i = ne[i]) if (to[i] ^ fa)
	{
		dfs1(to[i], x);
		s[x] ^= sg[to[i]];
	}
	if (!c[x]) rt[x] = newtrie(s[x], 18);
	for (int i = bg[x]; i; i = ne[i]) if (to[i] ^ fa)
	{
		tag[rt[to[i]]] ^= (s[x] ^ sg[to[i]]);
		rt[x] = merge(rt[x], rt[to[i]], 18);
	}
	sg[x] = search_mex(rt[x], 18);
}
void dfs2(int x, int fa = 0, int k = 0)
{
	k ^= s[x];
	if (!k && !c[x]) ans.emplace_back(x);
	for (int i = bg[x]; i; i = ne[i]) if (to[i] ^ fa)
		dfs2(to[i], x, k ^ sg[to[i]]);
}

int main()
{
#ifdef CraZYali
	file("11414");
#endif
	n = read<int>();
	REP(i, 1, n) c[i] = read<int>();
	REP(i, 2, n)
	{
		int x(read<int>()), y(read<int>());
		add(x, y);add(y, x);
	}
	dfs1(1);
	if (!sg[1]) puts("-1");
	else
	{
		dfs2(1);
		sort(ans.begin(), ans.end());
		for (auto i : ans) cout << i << '\n';
	}
	return 0;
}
