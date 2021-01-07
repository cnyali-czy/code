/*
	Problem:	A.cpp
	Time:		2021-01-07 10:55
	Author:		CraZYali
	E-Mail:		yms-chenziyang@outlook.com 
*/

#define REP(i, s, e) for (register int i(s), end_##i(e); i <= end_##i; i++)
#define DEP(i, s, e) for (register int i(s), end_##i(e); i >= end_##i; i--)
#define DEBUG fprintf(stderr, "Passing [%s] in Line %d\n", __FUNCTION__, __LINE__)

#define chkmax(a, b) (a < (b) ? a = (b) : a)
#define chkmin(a, b) (a > (b) ? a = (b) : a)

#include <vector>
#include <queue>
#include <algorithm>
#include <iostream>
#include <cstdio>
#define int long long

using namespace std;
const int maxn = 3e5 + 10;

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
int a[maxn], c[maxn];

signed main()
{
#ifdef CraZYali
	file("A");
#endif
	register int T = read<int>();
	while (T--)
	{
		n = read<int>();m = read<int>();
		REP(i, 1, n) a[i] = read<int>();
		REP(i, 1, m) c[i] = read<int>();
		sort(a + 1, a + 1 + n);
		priority_queue <int, vector <int>, greater <int> > q;
		int ans = 0;
		for (int i = 1, j = 1; i <= n; i++)
		{
			while (j <= a[i])
				q.emplace(c[j++]);
			q.emplace(c[a[i]]);
			ans += q.top();
			q.pop();
		}
		printf("%lld\n", ans);
	}
	return 0;
}
