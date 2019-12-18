#define REP(i, s, e) for (register int i = (s), end_##i = (e); i <= end_##i; i++)
#define DEP(i, s, e) for (register int i = (s), end_##i = (e); i >= end_##i; i--)
#define DEBUG fprintf(stderr, "Passing [%s] in Line %d\n", __FUNCTION__, __LINE__)

#define chkmax(a, b) (a < (b) ? a = (b) : a)
#define chkmin(a, b) (a > (b) ? a = (b) : a)

#include <algorithm>
#include <iostream>
#include <cassert>
#include <cstring>
#include <cstdlib>
#include <cstdio>
#include <vector>
#include <cmath>

using namespace std;

inline long long add(long long x, long long y, long long MOD)
{
	long long res = x + y;
	if (res >= MOD) res -= MOD;
	return res;
}

inline long long mul(long long a, long long b, long long MOD)
{
	if (!a || !b) return 0;
	long long ans(0), base(a);
	while (b)
	{
		if (b & 1) ans = add(ans, base, MOD);
		base = add(base, base, MOD);
		b >>= 1;
	}
	return ans;
}

long long power_pow(long long base, long long b, const long long MOD)
{
	long long ans(1);
	while (b)
	{
		if (b & 1) ans = mul(ans, base, MOD);
		base = mul(base, base, MOD);
		b >>= 1;
	}
	return ans;
}

template <typename T> T read()
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

void file(string s)
{
	freopen((s + ".in").c_str(), "r", stdin);
	freopen((s + ".out").c_str(), "w", stdout);
}

int m, n, k;

int tst[] = {2, 3, 13, 17, 19, 23, 19260817}, times(sizeof (tst) / sizeof (int));
inline bool fake(long long a, long long p)
{
	long long u(p - 1), l(0);
	while (!(u & 1))
	{
		l++;
		u >>= 1;
	}
	long long x = power_pow(a, u, p);
	if (x == 1) return 0;
	REP(i, 1, l)
	{
		if (1 < x && x < p - 1 && mul(x, x, p) == 1) return 1;
		x = mul(x, x, p);
	}
	return x != 1;
}
inline bool check(long long p)
{
	if (p == 2) return 1;
	if (p < 2 || p % 2 == 0) return 0;
	REP(i, 0, times-1)
		if (p == tst[i]) return 1;
		else if (tst[i] < p && fake(tst[i], p)) return 0;
	return 1;
}

int main()
{
#ifdef CraZYali
	file("143");
#endif
	srand(time(0));
	long long n;
	while (scanf("%lld", &n) != EOF)
		printf("%c\n", check(n) ? 'Y' : 'N');
	return 0;
}
