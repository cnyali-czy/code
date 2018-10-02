#define  REP(i, s, e) for(register long long i = s; i <= e ;i++)
#define DREP(i, s, e) for(register long long i = s; i >= e ;i--)

#define DEBUG fprintf(stderr, "Passing [%s] in LINE %lld\n", __FUNCTION__, __LINE__)
#define chkmin(a, b) a = min(a, b)
#define chkmax(a, b) a = max(a, b)

#include <iostream>
#include <cstdio>
#include <cstring>

using namespace std;
const long long maxn = 1e6 + 10;

template <typename T> T read()
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

long long n;
long long m[maxn], a[maxn];

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

long long lcm(long long a, long long b)
{
	register long long x, y;
	return a * b / exgcd(a, b, x, y);
}

int main()
{
#ifdef CraZYali
	freopen("2891.in", "r", stdin);
	freopen("2891.out", "w", stdout);
#endif
	while (scanf("%lld", &n) != EOF)
	{
		REP(i, 1, n)
			m[i] = read<long long>(), a[i] = read<long long>();
		register long long ans = 0 , M = m[1], A = a[1];
		REP(i, 2, n)
		{
			register long long x, y, g;
			if ((a[i] - A) % (g = exgcd(M, m[i], x, y)))
			{
				printf("-1\n");
				goto next;
			}
			x = (a[i] - A) / g * x % (m[i] / g);
			A += x * M;
			M = M / g * m[i];
			A %= M;
		}
		printf("%lld\n", (A + M) % M);
next:;
	}


	return 0;
}
