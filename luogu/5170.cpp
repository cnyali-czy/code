/*
 * File Name:	5170.cpp
 * Author	:	CraZYali
 * Time		:	2020.02.05 09:13
 * Email	:	yms-chenziyang@outlook.com
 */

#define DEP(i, s, e) for (register int i(s), end_##i(e); i >= end_##i; i--)
#define REP(i, s, e) for (register int i(s), end_##i(e); i <= end_##i; i++)
#define DEBUG fprintf(stderr, "Passing [%s] in Line %d\n", __FUNCTION__, __LINE__)

#define chkmax(a, b) (a < (b) ? a = (b) : a) 
#define chkmin(a, b) (a > (b) ? a = (b) : a) 

#include <iostream>
#include <cstdio>
using namespace std;
const int MOD = 998244353, inv2 = MOD + 1 >> 1, inv3 = (MOD + 1) / 3, inv6 = 1ll * inv2 * inv3 % MOD;

int add() {return 0;}
template <typename ...T>
int add(int x, T... y)
{
	int res = x + add(y...);
	if (res >= MOD) res -= MOD;
	return res;
}
inline void inc(int &x, int y)
{
	x += y;
	if (x >= MOD) x -= MOD;
}
inline void dec(int &x, int y)
{
	x -= y;
	if (x < 0) x += MOD;
}
int sub(int x, int y)
{
	int res = x - y;
	if (res < 0) res += MOD;
	return res;
}
int mul() {return 1;}
template <typename ...T>
int mul(long long x, T... y)
{
	if (x >= MOD) x %= MOD;
	long long res = (long long)x * mul(y...);
	if (res >= MOD) res %= MOD;
	return res;
}

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

struct Ans
{
	int f, g, h;
	Ans(int _f = 0, int _g = 0, int _h = 0)
	{
		if (_f >= MOD) _f -= MOD;f = _f;
		if (_g >= MOD) _g -= MOD;g = _g;
		if (_h >= MOD) _h -= MOD;h = _h;
	}
};
Ans eu(int a, int b, int c, long long n)
{
	if (!n) return Ans(b / c, 0, mul(b / c, b / c));
	else if (!a) return Ans(mul(b / c, n + 1), mul(b / c, n, n + 1, inv2), mul(b / c, b / c, n + 1));
	else if (a >= c || b >= c)
	{
		Ans tmp = eu(a % c, b % c, c, n);
		inc(tmp.h, add(mul(2, add(mul(b / c, tmp.f), mul(a / c, tmp.g))), mul(b / c, b / c, n + 1), mul(a / c, a / c, n, n + 1, n + n + 1, inv6), mul(a / c, b / c, n, n + 1)));
		inc(tmp.f, add(mul(n + 1, b / c), mul(a / c, n, n + 1, inv2)));
		inc(tmp.g, add(mul(n, n + 1, inv2, b / c), mul(n, n + 1, n + n + 1, inv6, a / c)));
		return tmp;
	}
	else
	{
		int F, G, H;
		long long m = (a * n + b) / c;
		Ans tmp = eu(c, c - b - 1, a, m - 1);
		F = sub(mul(n, m), tmp.f);
		G = mul(inv2, sub(mul(n, m, n + 1), add(tmp.f, tmp.h)));
		H = sub(mul(n, m, m + 1), add(F, mul(2, add(tmp.g, tmp.f))));
		return Ans(F, G, H);
	}
}

signed main()
{
#ifdef CraZYali
	file("5170");
#endif
	register int T = read<int>();
	while (T--)
	{
		int n(read<int>()), a(read<int>()), b(read<int>()), c(read<int>());
		Ans ans = eu(a, b, c, n);
		printf("%lld %lld %lld\n", ans.f, ans.h, ans.g);
	}
	return 0;
}
