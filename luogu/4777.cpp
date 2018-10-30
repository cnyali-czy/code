#define DREP(i, s, e) for(register int i = s; i >= e ;i--)
#define  REP(i, s, e) for(register int i = s; i <= e ;i++)

#define DEBUG fprintf(stderr, "Passing [%s] in Line %d\n", __FUNCTION__, __LINE__)
#define chkmax(a, b) a = max(a, b)
#define chkmin(a, b) a = min(a, b)

#include <bits/stdc++.h>
#define int long long

using namespace std;
const int maxn = 1e5 + 10;

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

int mul(int a, int b, int MOD)
{
	a = (a % MOD + MOD) % MOD;b = (b % MOD + MOD) % MOD;
	int l = a * (b >> 25) % MOD * (1ll << 25) % MOD;
	int r = a * (b & ((1ll << 25) - 1)) % MOD;
	return (l + r) % MOD;
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

int m[maxn], a[maxn], n;

signed main()
{
#ifdef CraZYali
	freopen("4777.in", "r", stdin);
	freopen("4777.out", "w", stdout);
#endif
	cin >> n;
	REP(i, 1, n) m[i] = read<int>(), a[i] = read<int>();
	int A = a[1], M = m[1];
	REP(i, 2, n)
	{
		register int g, x, y;
		g = exgcd(M, m[i], x, y);
		x = mul((a[i] - A) / g, x, m[i] / g);
		A += M * x;
		M = M / g * m[i];
		A %= M;
	}
	cout << (A + M) % M;
	return 0;
}
