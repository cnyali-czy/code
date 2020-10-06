/*
	Problem:	bf.cpp
	Time:		2020-06-11 08:04
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
const int maxn = 1e5, MOD = 998244353;
int n, m, a[maxn], bin[maxn];

int main()
{
#ifdef CraZYali
	freopen("A.in", "r", stdin);
	freopen("bf.out", "w", stdout);
#endif
	n = read<int>();m = read<int>();
	REP(i, 1, n) a[i] = read<int>();
	while (m--)
	{
		int l(read<int>()), r(read<int>()), x(read<int>());
		bin[0] = 1;
		REP(i, 1, r - l + 2) bin[i] = 1ll * bin[i-1] * x % MOD;
		long long ans = 0;
		REP(S, 0, (1 << r - l + 1) - 1)
		{
			int g = 0, t = 0;
			REP(j, l, r) if (S >> (j - l) & 1)
				g ^= a[j], t++;
			g %= MOD;
			(ans += 1ll * bin[t] * g) %= MOD;
		}
		printf("%lld\n", ans);
	}
	return 0;
}
