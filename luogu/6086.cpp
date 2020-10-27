/*
	Problem:	6086.cpp
	Time:		2020-10-27 15:56
	Author:		CraZYali
	E-Mail:		yms-chenziyang@outlook.com 
*/

#define REP(i, s, e) for (register int i(s), end_##i(e); i <= end_##i; i++)
#define DEP(i, s, e) for (register int i(s), end_##i(e); i >= end_##i; i--)
#define DEBUG fprintf(stderr, "Passing [%s] in Line %d\n", __FUNCTION__, __LINE__)

#define chkmax(a, b) (a < (b) ? a = (b) : a)
#define chkmin(a, b) (a > (b) ? a = (b) : a)

#include <iostream>
#include <cstdio>
#define i64 long long

using namespace std;
const int maxn = 5e6 + 10;

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

int n, m;
int f[maxn], deg[maxn], p[maxn];

namespace build_prufer
{
	void work()
	{
		REP(i, 1, n - 1)
		{
			f[i] = read<int>();
			deg[f[i]]++;
		}
		for (int i = 1, j = 1; i <= n - 2; i++, j++)
		{
			while (deg[j]) j++;
			p[i] = f[j];
			while (i <= n - 2 && !(--deg[p[i]]) && p[i] < j) p[i + 1] = f[p[i]], i++;
		}
		i64 ans = 0;
		REP(i, 1, n - 2) ans ^= (1ll * i * p[i]);
		cout << ans << endl;
	}
}
namespace build_tree
{
	void work()
	{
		REP(i, 1, n - 2)
		{
			p[i] = read<int>();
			deg[p[i]]++;
		}
		p[n - 1] = n;
		for (int i = 1, j = 1; i < n; i++, j++)
		{
			while (deg[j]) j++;
			f[j] = p[i];
			while (i < n && !(--deg[p[i]]) && p[i] < j) f[p[i]] = p[i + 1], i++;
		}
		i64 ans = 0;
		REP(i, 1, n - 1) ans ^= (1ll * i * f[i]);
		cout << ans << endl;
	}
}

int main()
{
#ifdef CraZYali
	file("6086");
#endif
	n = read<int>();m = read<int>();
	if (m == 1) build_prufer :: work();
	else build_tree :: work();
	return 0;
}
