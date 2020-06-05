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
#define i64 long long
i64 n;
i64 Randint(i64 l, i64 r) {return 1ll * rand() * rand() % (r - l + 1) + l;}

int totst[] = {2, 3, 13, 17, 19, 23};

inline i64 mul(i64 a, i64 b, const i64 p)
{
	i64 res = (a * b - (i64)((long double)a / p * b) * p) % p;
	if (res < 0) res += p;
	return res;
}
i64 power_pow(i64 base, i64 b, i64 p)
{
	i64 ans = 1;
	while (b)
	{
		if (b & 1) ans = mul(ans, base, p);
		base = mul(base, base, p);
		b >>= 1;
	}
	return ans;
}

i64 miller_rabin(i64 n)
{
	if (n < 3) return n == 2;
	if (n % 2 == 0) return 0;
	i64 a = n - 1, b = 0;
	while (!(a & 1)) a >>= 1, b++;
	for (i64 x : totst)
	{
		if (x == n) return 1;
		i64 v = power_pow(x, a, n);
		if (v == 1 || v == n - 1) continue;
		for (int j = 0; j <= b; j++)
		{
			if (v == n - 1) break;
			if (j == b) return 0;
			v = mul(v, v, n);
		}
	}
	return 1;
}

int main()
{
#ifdef CraZYali
	file("143-new");
#endif
	while (scanf("%lld", &n) != EOF) puts(miller_rabin(n) ? "Y" : "N");
	return 0;
}
