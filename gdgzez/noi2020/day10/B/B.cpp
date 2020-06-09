/*
	Problem:	B.cpp
	Time:		2020-06-09 08:27
	Author:		CraZYali
	E-Mail:		yms-chenziyang@outlook.com 
*/

#define REP(i, s, e) for (register int i(s), end_##i(e); i <= end_##i; i++)
#define DEP(i, s, e) for (register int i(s), end_##i(e); i >= end_##i; i--)
#define DEBUG fprintf(stderr, "Passing [%s] in Line %d\n", __FUNCTION__, __LINE__)

#define chkmax(a, b) (a < (b) ? a = (b) : a)
#define chkmin(a, b) (a > (b) ? a = (b) : a)

#include <cstring>
#include <cassert>
#include <iostream>
#include <cstdio>
#include <set>

using namespace std;
const int maxn = 1e6 + 10;

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

int n, a[maxn];

struct fenwick
{
	int c[maxn];
	fenwick() {memset(c, 0, sizeof c);}
	void add(int x, int y)
	{
		while (x < maxn)
		{
			c[x] += y;
			x += x & -x;
		}
	}
	int sum(int x)
	{
		int y = 0;
		while (x > 0)
		{
			y += c[x];
			x &= (x - 1);
		}
		return y;
	}
	int sum(int l, int r)
	{
		int y = 0;
		l--;
		while (r > l) y += c[r], r &= (r - 1);
		while (l > r) y -= c[l], l &= (l - 1);
		return y;
	}
}f1, f2;

namespace shit
{
	int fa[maxn];
	int find(int x) {return fa[x] == x ? fa[x] : fa[x] = find(fa[x]);}
	const int inf = 5e5 + 5;
	int main()
	{
		REP(i, 1, maxn - 1) fa[i] = i;
		int Min = a[1];
		REP(i, 2, n) chkmin(Min, a[i]);
		REP(i, 1, n)
		{
			int x = a[i];
			if (x < inf) f2.add(x, 1);
			x = find(x);
			if (x)
			{
				fa[x] = fa[x - 1];
				f1.add(x, 1);
			}
			int l = Min, r = inf, res = 0;
			while (l < r)
			{
				int mid = l + r + 1 >> 1;
				if (f2.sum(mid) + mid > inf) r = mid - 1;
				else l = mid;
			}
			while (f2.sum(l) < inf - l) l++;
			while (f2.sum(l) > inf - l) l--;
			printf("%d\n", f1.sum(l + 1, maxn - 1) + l - inf);
		}
		return 0;
	}
}
multiset <int> S;

int main()
{
#ifdef CraZYali
	file("B");
#endif
	n = read<int>();
	REP(i, 1, n) a[i] = read<int>() + shit :: inf;
	return shit :: main();
	REP(i, 1, n)
	{
		S.emplace(a[i]);
		int res = 0;
		for (auto j : S)
			if (res < j) res++;
			else if (res > j) res--;
		printf("%d\n", res);
	}
	return 0;
}
