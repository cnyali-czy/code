/*
	Problem:	E.cpp
	Time:		2021-05-31 20:10
	Author:		CraZYali
	E-Mail:		yms-chenziyang@outlook.com 
*/

#define REP(i, s, e) for (register int i(s), end_##i(e); i <= end_##i; i++)
#define DEP(i, s, e) for (register int i(s), end_##i(e); i >= end_##i; i--)
#define DEBUG fprintf(stderr, "Passing [%s] in Line %d\n", __FUNCTION__, __LINE__)

#define chkmax(a, b) (a < (b) ? a = (b) : a)
#define chkmin(a, b) (a > (b) ? a = (b) : a)

#include <map>
#include <algorithm>
#include <vector>
#include <iostream>
#include <cstdio>
#define int long long

using namespace std;
const int maxn = 140000;

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
int ls[maxn], rs[maxn], lw[maxn], rw[maxn];
inline void add(int fa, int x, int w)
{
	if (!ls[fa]) ls[fa] = x, lw[fa] = w;
	else rs[fa] = x, rw[fa] = w;
}

int lim;
vector <pair <int, int> > v[maxn];
#define fi first
#define se second
void dfs(int x)
{
	v[x].clear();
	if (!ls[x])
	{
		v[x].emplace_back(0, 0);
		return;
	}
	dfs(ls[x]);dfs(rs[x]);
	for (auto &i : v[ls[x]]) i.fi += lw[x], i.se += lw[x];
	for (auto &i : v[rs[x]]) i.fi += rw[x], i.se += rw[x];
/*
	for (auto i : v[ls[x]]) for (auto j : v[rs[x]])
		if (i.se + j.fi <= lim) v[x].emplace_back(i.fi, j.se);
	for (auto i : v[rs[x]]) for (auto j : v[ls[x]])
		if (i.se + j.fi <= lim) v[x].emplace_back(i.fi, j.se);
	map <int, int> orz;
	for (auto i : v[x]) orz[i.fi] = i.se;
	for (auto i : v[x]) orz[i.fi] = min(orz[i.fi], i.se);
	v[x].clear();
	for (auto i : orz) v[x].emplace_back(i);
	return;*/
	vector <pair <int, int> > t;

	int j = -1;
	for (auto i : v[ls[x]])
	{
		while (j + 1 < v[rs[x]].size() && i.se + v[rs[x]][j + 1].fi <= lim) j++;
		if (~j) t.emplace_back(i.fi, v[rs[x]][j].se);
	}
	j = -1;
	for (auto i : v[rs[x]])
	{
		while (j + 1 < v[ls[x]].size() && i.se + v[ls[x]][j + 1].fi <= lim) j++;
		if (~j) t.emplace_back(i.fi, v[ls[x]][j].se);
	}
	sort(t.begin(), t.end());t.resize(unique(t.begin(), t.end()) - t.begin());
	int lst = 1e18;
	for (auto i : t) if (i.se < lst) v[x].emplace_back(i), lst = i.se;
}

signed main()
{
#ifdef CraZYali
	file("E");
#endif
	n = read<int>();
	REP(i, 2, n)
	{
		int fa = read<int>(), w = read<int>();
		add(fa, i, w);
	}
	int l = 0, r = maxn * maxn , ans = r;
	while (l <= r)
	{
		lim = l + r >> 1;
		dfs(1);
		if (v[1].size())
		{
			ans = lim;
			r = lim - 1;
		}
		else l = lim + 1;
	}
	cout << ans << endl;
	return 0;
}
