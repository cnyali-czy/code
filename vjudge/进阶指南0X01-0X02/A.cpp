#define  REP(i, s, e) for (int i = s; i <= e; i++)
#define DREP(i, s, e) for (int i = s; i >= e; i--)
#define DEBUG fprintf(stderr, "Passing [%s] in Line %d\n", __FUNCTION__, __LINE__)

#define chkmax(a, b) a = max(a, b)
#define chkmin(a, b) a = min(a, b)

#include <bits/stdc++.h>
#define int unsigned long long

using namespace std;

template <typename T> T read()
{
	T ans = 0, p = 1;
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

int power_pow(int a, int b)
{
	int ans = 1, base = a;
	while (b)
	{
		if (b & 1) (ans *= base) %= 10;
		(base *= base) %= 10;
		b >>= 1;
	}
	return ans % 10;
}

signed main()
{
#ifdef CraZYali
	freopen("A.in", "r", stdin);
	freopen("A.out", "w", stdout);
#endif
	register int T = read<int>();
	while (T --> 0)
	{
		int n = read<int>();
		printf("%lld\n", power_pow(n % 10, n));
	}
	return 0;
}
