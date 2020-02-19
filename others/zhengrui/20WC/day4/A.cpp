/*
	Problem:	A.cpp
	Time:		2020-02-18 20:57
	Author:		CraZYali
	E-Mail:		yms-chenziyang@outlook.com 
*/

#define REP(i, s, e) for (register int i(s), end_##i(e); i <= end_##i; i++)
#define DEP(i, s, e) for (register int i(s), end_##i(e); i >= end_##i; i--)
#define DEBUG fprintf(stderr, "Passing [%s] in Line %d\n", __FUNCTION__, __LINE__)

#define chkmax(a, b) (a < (b) ? a = (b) : a)
#define chkmin(a, b) (a > (b) ? a = (b) : a)

#include <set>
#include <vector>
#include <iostream>
#include <cstdio>
using namespace std;
const int maxn = 1e5 + 10, maxq = 1e5 + 10, maxN = 1e7;

int bg[maxn], ne[maxn], to[maxn], e;
void add(int x, int y)
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

int n, q, fa[maxn], w[maxn];

int dfn[maxn], siz[maxn], dfs_clock;
void dfs(int x)
{
	dfn[x] = ++dfs_clock;
	siz[x] = 1;
	for (int i = bg[x]; i; i = ne[i])
	{
		dfs(to[i]);
		siz[x] += siz[to[i]];
	}
}

int ch[maxN][2], cur;
set <int> s1[maxN], s2[maxN];

void insert(int &p, int dep, int val, int time, int delta)
{
	if (!p) p = ++cur;
	if (delta > 0) s1[p].emplace(time);
	else s2[p].emplace(time);
	if (dep == -1) return;
	int flag = ((val >> dep) & 1);
	insert(ch[p][flag], dep - 1, val, time, delta);
}

vector <pair <int, int> > Add[maxn];
vector <pair <int, int> > Del[maxn];
vector <pair <int, pair <int, int> > > Qry[maxn];

int typ[maxq], x[maxq], y[maxq], ans[maxq];

signed main()
{
#ifdef CraZYali
	file("A");
#endif
	n = read<int>();q = read<int>();
	REP(i, 1, n) w[i] = read<int>();
	REP(i, 2, n) add(fa[i] = read<int>(), i);
	dfs(1);
	int Time = 0;
	REP(i, 1, n)
	{
		Add[dfn[i]].emplace_back(0, w[i]);
		Del[dfn[i] + siz[i]].emplace_back(0, w[i]);
	}
	int Cnt = 0;
	REP(i, 1, q)
	{
		int typ = read<int>(), x = read<int>();
		if (!typ)
		{
			Del[x].emplace_back(i, w[x]);
			Add[dfn[x] + siz[x]].emplace_back(i, w[x]);
			w[x] = read<int>();
			Add[x].emplace_back(i, w[x]);
			Del[dfn[x] + siz[x]].emplace_back(i, w[x]);
		}
		else Qry[x].emplace_back(i, make_pair(++Cnt, w[x]));
	}
	/*
	while (q--)
	{
		register int typ = read<int>(), x(read<int>());
		if (!typ)
		{
//			REP(j, dfn[x], dfn[x] + siz[x] - 1) insert(rt[j], 30, w[x], -1);
			add(dfn[x], w[x], -1);
			add(dfn[x] + siz[x], w[x], 1);
			w[x] = read<int>();
			add(dfn[x], w[x], 1);
			add(dfn[x] + siz[x], w[x], -1);
//			REP(j, dfn[x], dfn[x] + siz[x] - 1) insert(rt[j], 30, w[x], 1);
		}
		else
		{
			top = 0;
//			stack[top = 1] = rt[dfn[x]];
			for (int y = dfn[x]; y > 0; y &= (y - 1)) stack[++top] = rt[y];
			int val = w[x], ans = 0;
			DEP(dep, 30, 0)
			{
				int flag = !((val >> dep) & 1), here = 0;
				REP(i, 1, top) here += s[ch[stack[i]][flag]];
				if (here > 0)
				{
					ans |= (1 << dep);
					REP(i, 1, top) stack[i] = ch[stack[i]][flag];
				}
				else 
					REP(i, 1, top) stack[i] = ch[stack[i]][!flag];
			}
			cout << ans << '\n';
		}
	}
	*/
	int rt = 0;
	REP(i, 1, n)
	{
		for (auto j : Add[i]) insert(rt, 30, j.second, j.first, 1);
		for (auto j : Del[i]) insert(rt, 30, j.second, j.first, -1);
		for (auto j : Qry[i])
		{
			int &res = ans[j.second.first];res = 0;
			int val = j.second.second;
			int u = rt;
			DEP(dep, 30, 0)
			{
				int flag = !((val >> dep) & 1);
				if (!ch[u][flag])
				{
					u = ch[u][!flag];
					continue;
				}
				auto it1 = s1[ch[u][flag]].upper_bound(j.first);
				auto it2 = s2[ch[u][flag]].upper_bound(j.first);
//				if (it != s[ch[u][flag]].begin())
//				{
//					res |= (1 << dep);
//					u = ch[u][flag];
//				}
//				else u = ch[u][!flag];
			}
		}
	}
	REP(i, 1, Cnt) printf("%d\n", ans[i]);
	return 0;
}
