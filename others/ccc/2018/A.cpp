/*
	Problem:	A.cpp
	Time:		2021-02-18 08:11
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
const int maxn = 100 + 5, inf = 1e18;

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

int n;
int v[maxn];

signed main()
{
#ifdef CraZYali
	file("A");
#endif
	cin >> n;REP(i, 1, n) cin >> v[i];
	sort(v + 1, v + 1 + n);v[n + 1] = inf;v[0] = -inf;
	double ans = inf;
	REP(i, 1, n) ans = min(ans, (v[i + 1] - v[i - 1]) / 2.);
	printf("%.1lf\n", ans);
	return 0;
}
