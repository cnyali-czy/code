/*
	Problem:	2005.cpp
	Time:		2021-04-27 16:17
	Author:		CraZYali
	E-Mail:		yms-chenziyang@outlook.com 
*/

#define REP(i, s, e) for (register int i(s), end_##i(e); i <= end_##i; i++)
#define DEP(i, s, e) for (register int i(s), end_##i(e); i >= end_##i; i--)
#define DEBUG fprintf(stderr, "Passing [%s] in Line %d\n", __FUNCTION__, __LINE__)

#define chkmax(a, b) (a < (b) ? a = (b) : a)
#define chkmin(a, b) (a > (b) ? a = (b) : a)

#include <algorithm>
#include <iostream>
#include <cstdio>
#define int long long

using namespace std;
const int maxn = 1e5 + 10;

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

int n, q, a[maxn], m;
int xs[maxn], ans[maxn];

void work(int le, int x, int R)
{
	if (le <= a[1])
	{
		ans[le] += x;
		return;
	}
	if (!le || R < 1) return;
	int pos = upper_bound(a + 1, a + 1 + R, le) - a - 1;
	xs[pos] += le / a[pos] * x;
	work(le % a[pos], x, pos - 1);
}

signed main()
{
#ifdef CraZYali
	file("2005");
#endif
	n = read<int>();q = read<int>();
	a[m = 1] = n;
	while (q--)
	{
		int x = read<int>();
		while (m && x <= a[m]) m--;
		a[++m] = x;
	}
	xs[m] = 1;
	DEP(i, m, 2)
	{
		xs[i - 1] += a[i] / a[i - 1] * xs[i];
		work(a[i] % a[i - 1], xs[i], i - 1);
	}
	DEP(i, n, 1) ans[i] += ans[i + 1];
	REP(i, 1, a[1]) ans[i] += xs[1];
	REP(i, 1, n) printf("%lld\n", ans[i]);
	return 0;
}
