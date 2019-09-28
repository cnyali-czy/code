/*
 * File Name:	lp.cpp
 * Author	:	CraZYali
 * Year		:	2019.09.28 21:28
 * Email	:	yms-chenziyang@outlook.com
 */

#define DREP(i, s, e) for (register int i(s), end_##i(e); i >= end_##i; i--)
#define  REP(i, s, e) for (register int i(s), end_##i(e); i <= end_##i; i++)
#define DEBUG fprintf(stderr, "Passing [%s] in Line %d\n", __FUNCTION__, __LINE__)

#define chkmax(a, b) a = max(a, (b))
#define chkmin(a, b) a = min(a, (b))

#include <iostream>
#include <cstring>
#include <cstdio>
#define int long long

using namespace std;
const int maxn = 10000 + 10, inf = 0x3f3f3f3f3f3f3f3fll;

template <typename T> inline T read()
{
	T ans(0), flag(1);
	char c(getchar());
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

#define file(FILE_NAME) freopen(FILE_NAME".in", "r", stdin), freopen(FILE_NAME".out", "w", stdout);

int a[maxn], b[maxn], c[maxn], dp[2][maxn], q[maxn], n, P;

signed main()
{
#ifdef CraZYali
	file("lp");
#endif
	int T = read<int>();
	while (T--)
	{
		n = read<int>();
		P = read<int>();
		REP(i, 1, n) a[i] = read<int>();
		REP(i, 1, n) b[i] = read<int>();
		REP(i, 1, n) c[i] = read<int>();
		memset(dp, inf, sizeof dp);
		dp[0][0] = 0;
		int cur = 0;
		REP(i, 1, n)
		{
			cur ^= 1;
			int head = 1, tail = 0;
			REP(j, 0, P)
			{
				dp[cur][j] = dp[!cur][j];
				while (head <= tail && q[head] < j - b[i]) ++head;
				if (j >= a[i])
				{
					while (head <= tail && dp[!cur][q[tail]] > dp[!cur][j - a[i]]) --tail;
					q[++tail] = j - a[i];
				}
				if (head <= tail) chkmin(dp[cur][j], dp[!cur][q[head]] + c[i]);
			}
		}
		if (dp[cur][P] == inf) puts("IMPOSSIBLE!!!");
		else printf("%lld\n", dp[cur][P]);
	}
	return 0;
}
