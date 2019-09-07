/*
 * File Name:	1101.cpp
 * Author	:	CraZYali
 * Year		:	2019.09.07 23:09
 * Email	:	yms-chenziyang@outlook.com
 */

#define DREP(i, s, e) for (int i(s), end_##i(e); i >= end_##i; i--)
#define  REP(i, s, e) for (int i(s), end_##i(e); i <= end_##i; i++)
#define DEBUG fprintf(stderr, "Passing [%s] in Line %d\n", __FUNCTION__, __LINE__)

#define chkmax(a, b) a = max(a, (b))
#define chkmin(a, b) a = min(a, (b))

#include <algorithm>
#include <iostream>
#include <cstdio>
using namespace std;

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

const int N = 50000, maxn = N + 10;

int p[maxn], mu[maxn], smu[maxn];
bool notp[maxn];
inline void init()
{
	mu[1] = 1;
	REP(i, 2, N)
	{
		if (!notp[i]) mu[p[++p[0]] = i] = -1;
		REP(j, 1, p[0])
		{
			if (i * p[j] > N) break;
			notp[i * p[j]] = 1;
			if (i % p[j] == 0) {mu[i * p[j]] = 0;break;}
			else mu[i * p[j]] = -mu[i];
		}
	}
	REP(i, 1, N) smu[i] = smu[i-1] + mu[i];
}

signed main()
{
#ifdef CraZYali
	file("1101");
#endif
	init();
	REP(hhakioi, 1, read<int>())
	{
		int a(read<int>()), b(read<int>()), d(read<int>());
		long long ans(0);
		a /= d;b /= d;
		if (a > b) swap(a, b);
		for (int d(1), lst(0); d <= a; d = lst + 1)
		{
			lst = min(a / (a / d), b / (b / d));
			ans += 1ll * (smu[lst] - smu[d-1]) * (a / d) * (b / d);
		}
		printf("%lld\n", ans);
	}
	return 0;
}
