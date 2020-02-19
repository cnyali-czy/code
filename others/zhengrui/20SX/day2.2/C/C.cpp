/*
	Problem:	C.cpp
	Time:		2020-02-19 21:25
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
#define int long long
using namespace std;
const int maxn = 5e5 + 10, MOD = 998244353, inv2 = MOD + 1 >> 1;

inline int add(int x, int y) {register int res = x + y;return res >= MOD ? res - MOD : res;}
inline int sub(int x, int y) {register int res = x - y;return res <    0 ? res + MOD : res;}
inline i64 mul(i64 x, int y) {register i64 res = x * y;return res >= MOD ? res % MOD : res;}
inline void inc(i64 &x, int y) {x += y; if (x >= MOD) x -= MOD;}

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

int prime[maxn], mu[maxn], p_cnt;
bool notp[maxn];

struct __init__
{
	__init__(const int n = maxn - 10)
	{
		mu[1] = 1;
		REP(i, 2, n)
		{
			if (!notp[i]) mu[prime[++p_cnt] = i] = - 1;
			REP(j, 1, p_cnt)
			{
				int tmp = i * prime[j];if (tmp > n) break;
				notp[tmp] = 1;
				if (i % prime[j]) mu[tmp] = - mu[i];
				else break;
			}
		}
	}
}__INIT__;
int n, m, k;

signed main()
{
#ifdef CraZYali
	file("C");
#endif
	n = read<int>();
	m = read<int>();
	k = read<int>();
	if (n > m) swap(n, m);
	i64 ans = 0;
	REP(d, 1, n) REP(k, 1, n / d)
	{
		int z = d * k, x = n / z, y = m / z;
		int t = 1ll * mu[k] * x * y % MOD;
		t = 1ll * t * ((d * (::k / d) << 3) % MOD + (d - 1 << 2) + (n+z-2ll)*(m+z-2ll)%MOD) % MOD;
		inc(ans, (t + MOD) % MOD);
	}
	cout << mul(ans, mul(inv2, mul(inv2, inv2))) << endl;
	return 0;
}
