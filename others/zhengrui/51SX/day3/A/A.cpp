/*
	Problem:	A.cpp
	Time:		2020-06-10 15:32
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
const int maxn = 5e5 + 10, MOD = 998244353;
#define i64 long long

inline void inc(int &x, int y) {x += y;if (x >= MOD) x -= MOD;}
inline void dec(int &x, int y) {x -= y;if (x <    0) x += MOD;}

i64 power_pow(i64 base, int b)
{
	chkmax(b, 0);
	i64 ans = 1;
	while (b)
	{
		if (b & 1) (ans *= base) %= MOD;
		(base *= base) %= MOD;
		b >>= 1;
	}
	return ans;
}
#define inv(x) power_pow(x, MOD - 2)

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

int n, p[maxn];

int cnt[maxn];
long long f[maxn];
bool vis[maxn];

int main()
{
#ifdef CraZYali
	file("A");
#endif
	register int T = read<int>();
	while (T--)
	{
		n = read<int>();
		REP(i, 1, n) p[i] = read<int>();
		REP(i, 1, n) vis[i] = cnt[i] = f[i] = 0;
		REP(i, 1, n) if (!vis[i])
		{
			int k = 0;
			for (int x = i; !vis[x]; vis[x] = 1, x = p[x], k++);
			cnt[k]++;
		}
		REP(i, 1, n)
		{
			int tmp = 1ll * cnt[i] * i % MOD;
			for (int j = i + i; j <= n; j += i) f[j] += tmp;
		}
		REP(i, 1, n) if (f[i] >= MOD) f[i] %= MOD;
		long long ans = 0;
		if (cnt[1])
		{
			ans = power_pow(f[1] + cnt[1], cnt[1] - 2);
			REP(i, 2, n) if (cnt[i])
				(ans *= power_pow((f[i] + 1ll * i * cnt[i]) % MOD, cnt[i] - 1) * f[i] % MOD) %= MOD;
		}
		else if (cnt[2])
		{
			ans = power_pow(cnt[2] + cnt[2], cnt[2] - 1);
			REP(i, 3, n) if (cnt[i])
				(ans *= power_pow((f[i] + 1ll * i * cnt[i]) % MOD, cnt[i] - 1) * f[i] % MOD) %= MOD;
		}
		printf("%lld\n", ans);
	}
	return 0;
}
