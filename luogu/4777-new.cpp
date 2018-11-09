#define  REP(i, s, e) for (register int i = s; i <= e; i++)
#define DREP(i, s, e) for (register int i = s; i >= e; i--)
#define DEBUG fprintf(stderr, "Passing [%s] in Line %d\n", __FUNCTION__, __LINE__)

#define chkmax(a, b) a = max(a, b)
#define chkmin(a, b) a = min(a, b)

#include <bits/stdc++.h>
#define int long long

using namespace std;
const int maxn = 1e5 + 10;

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
int exgcd(int a, int b, int &x, int &y)
{
	if (!b)
	{
		x = 1;
		y = 0;
		return a;
	}
	int g = exgcd(b, a % b, y, x);
	y -= a / b * x;
	return g;
}
int n, A, M;

int mul(int a, int b, int MOD)
{
	a = (a % MOD + MOD) % MOD;b = (b % MOD + MOD) % MOD;
	int l = a * (b >> 25ll) % MOD * (1ll << 25);
	int r = a * (b & ((1ll << 25ll) - 1)) % MOD;
	return (l + r) % MOD;
}

signed main()
{
#ifdef CraZYali
	freopen("4777-new.in", "r", stdin);
	freopen("4777-new.out", "w", stdout);
#endif
	n = read<int>();
	M = read<int>();A = read<int>();
	while (--n)
	{
		int g, x, y, m = read<int>(), a = read<int>();
		g = exgcd(M, m, x, y);
		x = mul((a - A) / g, x, m / g);
		A += M * x;
		M = M / g * m;
		A %= M;
	}

	cout << (A + M) % M;
	return 0;
}
