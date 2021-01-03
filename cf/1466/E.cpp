/*
	Problem:	E.cpp
	Time:		2020-12-31 00:06
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
#define int long long
using namespace std;
const int maxn = 5e5 + 10, MOD = 1e9 + 7;

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

int n, a[maxn], s[maxn];
int cnt[70], bin[70];
signed main()
{
#ifdef CraZYali
	file("E");
#endif
	register int T = read<int>();
	bin[0] = 1;REP(i, 1, 65) bin[i] = bin[i - 1] * 2 % MOD;
	while (T--)
	{
		n = read<int>();
		REP(i, 0, 60) cnt[i] = 0;
		REP(i, 1, n)
		{
			a[i] = read<int>();
			REP(j, 0, 60) cnt[j] += (a[i] >> j & 1);
		}

		REP(i, 1, n) s[i] = 0;
		REP(i, 1, n)
		{
			int res = 0;
			REP(b, 0, 60)
			{
				if (a[i] >> b & 1)
					(res += n * bin[b]) %= MOD;
				else
					(res += cnt[b] * bin[b]) %= MOD;
			}
			s[i] = res;
		}

		int ans = 0;
		REP(b, 0, 60)
		{
			int res = 0;
			int cnt = 0;
			REP(i, 1, n) if (a[i] >> b & 1) cnt++, res += s[i];
			res = res % MOD * cnt % MOD;
			(ans += res * bin[b]) %= MOD;
		}
		printf("%lld\n", ans);
	}
	return 0;
}
