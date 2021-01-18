/*
	Problem:	B.cpp
	Time:		2021-01-10 09:58
	Author:		CraZYali
	E-Mail:		yms-chenziyang@outlook.com 
*/

#define REP(i, s, e) for (register int i(s), end_##i(e); i <= end_##i; i++)
#define DEP(i, s, e) for (register int i(s), end_##i(e); i >= end_##i; i--)
#define DEBUG fprintf(stderr, "Passing [%s] in Line %d\n", __FUNCTION__, __LINE__)

#define chkmax(a, b) (a < (b) ? a = (b) : a)
#define chkmin(a, b) (a > (b) ? a = (b) : a)

#include <cassert>
#include <iostream>
#include <cstdio>
#define i64 long long

using namespace std;
const int maxn = 1e6 + 10, MOD = 998244353;

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

int ty, n, k, ans[maxn];

int fac[maxn], invs[maxn], Inv[maxn];

void init(int n)
{
	fac[0] = invs[0] = Inv[0] = 1;
	fac[1] = invs[1] = Inv[1] = 1;
	REP(i, 2, n)
	{
		fac[i] = 1ll * i * fac[i - 1] % MOD;
		invs[i] = 1ll * (MOD - MOD / i) * invs[MOD % i] % MOD;
		Inv[i] = 1ll * invs[i] * Inv[i - 1] % MOD;
	}
}
i64 C(int n, int m) {return n < m || m < 0 ? 0 : 1ll * fac[n] * Inv[m] % MOD * Inv[n - m] % MOD;}

i64 calc1(int n, int s, int mi)
{
	if (mi > 1 || mi > s) return 0;
	if (mi == 1) return calc1(n - 1, s - 1, 0);
	assert((n + s) % 2 == 0);
	return (C(n, n + s >> 1) - C(n, (n + s - 2 * (mi - 1)) / 2) + MOD) % MOD;
}
i64 calc(int n, int s, int mi)
{
	return (calc1(n, s, mi) - calc1(n, s, mi + 1) + MOD) % MOD;
}

int main()
{
#ifdef CraZYali
	file("B");
#endif
	cin >> ty >> n;
	if (ty == 1) cin >> k;
	init(n);
	if (n == 1)
	{
		if (ty == 1) cout << (k == 0) * 2 << endl;
		else cout << 2 << endl;
		return 0;
	}
	static int times[maxn];
	REP(s, -n, n) if ((n + s) % 2 == 0)
	{
		int qaq = n - s >> 1;
		int aqa = n + s >> 1;
		int L = qaq + (s - n >> 1), R = qaq + min(-1, s);
		L = max(0, L);R = min(n, R);
		if (L <= R)
		{
			times[L]++;
			times[R + 1]--;
		}
		/*
		REP(T, L, R)
//		REP(T, qaq + (s - n >> 1), qaq + min(-1, s))
//		REP(mi, (s - n >> 1), min(-1, s))
		{
			//T = mi + qaq
			//mi = T - qaq
			assert(0 <= T && T <= n);
			(ans[T] += C(n, T) - C(n, T - 1)) %= MOD;
			//				(ans[tot] -= C(n, (n + s - 2 * (mi - 1)) / 2)) %= MOD;
			//				(ans[tot] += C(n, (n + s - 2 * mi) / 2)) %= MOD;
			//				(ans[tot] -= C(n, (n + s - 2 * (mi - 1)) / 2)) %= MOD;
			//				(ans[tot] += C(n, (n + s - 2 * mi) / 2)) %= MOD;
			//				(ans[tot] += calc1(n, s, mi)) %= MOD;
			//				(ans[tot] += MOD - calc1(n, s, mi + 1)) %= MOD;
		}
		*/
		REP(mi, min(-1, s) + 1, min(0, s))
		{
			int tot = qaq + mi;
			if (0 <= tot && tot <= n)
			{
				(ans[tot] += calc1(n, s, mi)) %= MOD;
				(ans[tot] += MOD - calc1(n, s, mi + 1)) %= MOD;
			}
		}
		if (1 <= s)
		{
			int mi = 1;
			int tot = n - s + 2 * min(0, mi);
			if (0 <= tot && tot <= n)
			{
				(ans[tot >> 1] += calc1(n, s, mi)) %= MOD;
				(ans[tot >> 1] += MOD - calc1(n, s, mi + 1)) %= MOD;
			}
		}
	}
	REP(i, 1, n) times[i] += times[i - 1];
	REP(i, 0, n)
	{
		ans[i] = (ans[i] + 1ll * times[i] * (C(n, i) - C(n, i - 1))) % MOD;
		ans[i] = (ans[i] + MOD) % MOD;
	}
	REP(i, 0, n / 2) printf("%d%c", ans[i], i == end_i ? '\n' : ' ');
	if (ty == 1) cout << ans[k] << endl;
	else
	{
		i64 bin = 1, Ans = 0;
		REP(i, 0, n / 2)
		{
			(Ans += bin * ans[i]) %= MOD;
			(bin *= 233) %= MOD;
		}
		cout << Ans << endl;
	}
	return 0;
}
