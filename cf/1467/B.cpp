/*
	Problem:	B.cpp
	Time:		2021-01-09 08:15
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

using namespace std;
const int maxn = 3e5 + 10, inf = 1e9 + 10;

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

int n, a[maxn], ans, tot;
int calc(int x)
{
	if (x <= 1 || x >= n) return 0;
	if (min(a[x - 1], a[x + 1]) > a[x]) return 1;
	if (max(a[x - 1], a[x + 1]) < a[x]) return 1;
	return 0;
}
void Try(int x, int v)
{
	int tmp = a[x];
	int res = tot;
	res -= calc(x - 1) + calc(x) + calc(x + 1);
	a[x] = v;
	res += calc(x - 1) + calc(x) + calc(x + 1);
	ans = min(ans, res);
	a[x] = tmp;
}

int main()
{
#ifdef CraZYali
	file("B");
#endif
	register int T = read<int>();
	while (T--)
	{
		n = read<int>();
		REP(i, 1, n) a[i] = read<int>();
		tot = 0;
		REP(i, 1, n) tot += calc(i);
		ans = tot;
		REP(i, 1, n)
		{
			if (i > 1) Try(i, a[i - 1]);			
			if (i < n) Try(i, a[i + 1]);
			Try(i, inf);Try(i, -inf);
		}
		printf("%d\n", ans);
	}
	return 0;
}
