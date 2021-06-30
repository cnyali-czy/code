/*
	Problem:	B.cpp
	Time:		2021-06-27 08:59
	Author:		CraZYali
	E-Mail:		yms-chenziyang@outlook.com 
*/

#define REP(i, s, e) for (register int i(s), end_##i(e); i <= end_##i; i++)
#define DEP(i, s, e) for (register int i(s), end_##i(e); i >= end_##i; i--)
#define DEBUG fprintf(stderr, "Passing [%s] in Line %d\n", __FUNCTION__, __LINE__)

#define chkmax(a, b) (a < (b) ? a = (b) : a)
#define chkmin(a, b) (a > (b) ? a = (b) : a)

#include <cassert>
#include <ctime>
#include <iostream>
#include <cstdio>
#define i64 long long
#define u64 unsigned i64
using namespace std;
const int maxn = 1e7 + 10, MOD = 1e9 + 7;

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

int n, k;
const u64 LIM = 18e18;
inline int f(int x) {static const int MOD = k;return (x + MOD - 1) / MOD;}
/*
int calc(int x)
{
	if (x % k == 1) return f(x);
	return calc(x - f(x));
}*/
int dep[maxn], y[maxn], c[maxn];
int main()
{
#ifdef CraZYali
	file("B");
#endif
	n = read<int>();k = read<int>();

	const int one = 1 % k;
	REP(i, 1, n)
	{
		int fi = f(i);
		if (i % k == one) dep[i] = 1, c[i] = fi;
		else dep[i] = dep[i - fi] + 1, c[i] = c[i - fi];
	}

	int z = n;
	REP(i, 1, n)
	{
		int fz = f(z);
		y[i] = y[i - 1] + fz;
		z -= fz;
	}
	/*
	REP(i, 1, n)
	{
		int x = i, y = n, z = 0;
		while (x)
		{
			if (x % k == 1)
			{
				b[i] = z + f(x);
				assert(z == ::y[dep[i] - 1]);
				assert(f(x) == calc(i));
				break;
			}
			x -= f(x);
			z += f(y);y -= f(y);
		}
	}*/
	u64 b3 = 1, ans = 0;
	REP(i, 1, n)
	{
		int b = y[dep[i] - 1] + c[i];

		ans += b3 * b;
		(b3 *= 3) %= MOD;
		if (ans >= LIM) ans %= MOD;
	}
	cout << ans % MOD << endl;
	return 0;
}
