#define  REP(i, s, e) for(register int i = s; i <= e ;i++)
#define DREP(i, s, e) for(register int i = s; i >= e ;i--)

#define DEBUG fprintf(stderr, "Passing [%s] in LINE %d\n", __FUNCTION__, __LINE__)
#define chkmin(a, b) a = min(a, b)
#define chkmax(a, b) a = max(a, b)

#include <bits/stdc++.h>

using namespace std;
const int maxn = 1e5 + 10;
const long long MOD = 1e9 + 7, inv = 333333336;

template <typename Te> Te read()
{
	register Te T(0);
	int p(1);
	register char c = getchar_unlocked();
	while (!isdigit(c))
	{
		if (c == '-') p = -1;
		c = getchar_unlocked();
	}
	while (isdigit(c))
	{
		T = T * 10 + c - 48;
		c = getchar_unlocked();
	}
	return T * p;
}

long long a[maxn];
int n, m;

int main()
{
	freopen("math.in", "r", stdin);
	freopen("math.out", "w", stdout);
	n = read<int>();
	m = read<int>();

	long long start = 2;

	REP(i, 1, n - 2) start = start * 3 % MOD;
	start = (start + MOD) % MOD;
	REP(i, 1, n) a[i] = read<long long>();
	while (m --> 0)
	{
		register long long x, y;
		x = read<long long>();
		y = read<long long>();
		a[x] = y;
		register long long tot = 0, A = start, B = 1;
		REP(i, 1, n - 1)
		{
			B = B * a[i] % MOD;
			tot = (tot + A * B) % MOD;
			A = (A * inv) % MOD;
		}
		B *= a[n];
		tot = (tot + B) % MOD;
		printf("%lld\n", (tot + MOD) % MOD);
	}

	return 0;
}
