/*
	Problem:	F.cpp
	Time:		2020-11-20 11:27
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
#include <map>
#include <set>
#include <iostream>
#include <cstdio>

using namespace std;
const int maxn = 1e5 + 10, maxq = 3e5 + 10, inf = 1e9;

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
		ans = ans * 10 + (c - 48);
		c = getchar();
	}
	return ans * flag;
}

#define file(FILE_NAME) freopen(FILE_NAME".in", "r", stdin), freopen(FILE_NAME".out", "w", stdout)

int n, q, a[maxn];

#define fi first
#define se second
vector <pair <int, int> > v[maxn];
int ans[maxq];

set <int> s;
map <int, int> lst;
int nxt(int x)
{
	auto it = s.lower_bound(x);
	if (it == s.end()) return -1;
	return *it;
}
int pre(int x)
{
	auto it = s.upper_bound(x);
	if (it == s.begin()) return -1;
	return *(--it);
}
namespace SMT
{
	int s[maxn];
	void init()
	{
		REP(i, 1, n) s[i] = inf;
	}
	void add(int x, int y)
	{
		while (x > 0) s[x] = min(s[x], y), x &= (x - 1);
	}
	int query(int x)
	{
		int y = inf;
		while (x <= n) y = min(s[x], y), x += x & -x;
		return y;
	}
}

int main()
{
#ifdef CraZYali
	file("F");
#endif
	n = read<int>();SMT :: init();
	REP(i, 1, n) a[i] = read<int>();
	q = read<int>();
	REP(i, 1, q)
	{
		int l = read<int>(), r = read<int>();
		v[r].emplace_back(l, i);
	}
	REP(i, 1, n)
	{
		int x = a[i], y, z;
		y = pre(x);
		if ((y = pre(x)) != -1)
			SMT :: add(lst[y], x - y);
		if ((y = nxt(x)) != -1)
			SMT :: add(lst[y], y - x);
		lst[x] = i;
		s.emplace(x);
		for (auto j : v[i])
			ans[j.se] = SMT :: query(j.fi);
	}
	REP(i, 1, q) printf("%d\n", ans[i]);
	return 0;
}
