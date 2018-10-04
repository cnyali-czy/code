#define DREP(i, s, e) for(register long long i = s; i >= e ;i--)
#define  REP(i, s, e) for(register long long i = s; i <= e ;i++)

#define DEBUG fprintf(stderr, "Passing [%s] in Line %d\n", __FUNCTION__, __LINE__)
#define chkmax(a, b) a = max(a, b)
#define chkmin(a, b) a = min(a, b)

#include <iostream>
#include <cstdio>

using namespace std;

template <typename T> inline T read()
{
	T ans(0), p(1);
	char c = getchar();
	while (!isdigit(c))
	{
		if (c == '-') p = -1;
		c = getchar();
	}
	while (isdigit(c))
	{
		ans = ans * 10 + c - 48;
		c = getchar();
	}
	return ans * p;
}

template <typename T> void write(T x)
{
	if (x < 0) putchar('-'), write(-x);
	else if (x / 10) write(x / 10);
	putchar(x % 10 + '0');
}

long long exgcd(long long a, long long b, long long &x, long long &y)
{
	if (!b)
	{
		x = 1;
		y = 0;
		return a;
	}
	register long long g = exgcd(b, a % b, y, x);
	y -= a / b * x;
	return g;
}

long long a, b, c, d, MOD;

signed main()
{
#ifdef CraZYali
	freopen("1061.in", "r", stdin);
	freopen("1061.out", "w", stdout);
#endif
	while (scanf("%lld%lld%lld%lld%lld", &a, &b, &c, &d, &MOD) != EOF)
	{
		register long long A, B;
		register long long g = exgcd(d - c, MOD, A, B);
		if ((a - b) % g) printf("Impossible\n");
		else
		{
			A *= (a - b) / g;
			MOD /= g;
			printf("%lld\n", (A % MOD + MOD) % MOD);
		}
	}
	return 0;
}
