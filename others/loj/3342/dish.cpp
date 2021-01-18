/*
	Problem:	dish.cpp
	Time:		2021-01-15 21:01
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
#include <queue>
#include <iostream>
#include <cstdio>
#define fi first
#define se second
using namespace std;
const int maxn = 500 + 5;

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

int n, m, k;

namespace any
{
	void work()
	{
		set <pair <int, int> > ssr;
		int SHIT = m - (n - 1);
		REP(i, 1, n)
		{
			int x = read<int>();
			while (x >= k && SHIT)
			{
				SHIT--;
				printf("%d %d\n", i, k);
				x -= k;
			}
			if (!x) continue;
			ssr.emplace(x, i);
		}
		while (ssr.size())
		{
			auto f = *ssr.begin();ssr.erase(f);
			if (f.first >= k)
			{
				printf("%d %d\n", f.se, k);
				f.fi -= k;if (f.fi) ssr.emplace(f);
			}
			else
			{
				auto g = *ssr.rbegin();ssr.erase(g);
				int need = k - f.fi;
				printf("%d %d %d %d\n", f.se, f.fi, g.se, need);
				g.fi -= need;if (g.fi) ssr.emplace(g);
			}
		}
	}
}

int main()
{
	file("dish");
	register int T = read<int>();
	while (T--)
	{
		 n = read<int>(), m = read<int>(), k = read<int>();
		 if (m >= n - 1) any :: work();
		 else return 0 * puts("GG");
	}
	return 0;
}
