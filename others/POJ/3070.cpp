#define DREP(i, s, e) for(register int i = s; i >= e ;i--)
#define  REP(i, s, e) for(register int i = s; i <= e ;i++)

#define DEBUG fprintf(stderr, "Passing [%s] in Line %d\n", __FUNCTION__, __LINE__)
#define chkmax(a, b) a = max(a, b)
#define chkmin(a, b) a = min(a, b)

#include <iostream>
#include <cstring>
#include <cstdio>
#include <cstdlib>

using namespace std;
const int MOD = 10000;

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

void mul(int a[3][3], int b[3][3], int n, int m, int p)
{
	int c[3][3];
	memset(c, 0, sizeof(c));
	REP(i, 1, n)
		REP(j, 1, p)
			REP(k, 1, m)
				c[i][j] += a[i][k] * b[k][j] % MOD, c[i][j] %= MOD;
	memcpy(a, c, sizeof(c));
}

int m, n, k;

int ans[3][3], base[3][3];

signed main()
{
#ifdef CraZYali
	freopen("3070.in", "r", stdin);
	freopen("3070.out", "w", stdout);
#endif
	/*
	   f[i-1] f[i]
	   0 1
	   1 1
	   */
	while ((n = read<int>()) != -1)
	{
		ans[1][1] = 0;ans[1][2] = 1;
		base[1][1] = 0;
		base[1][2] = 1;
		base[2][1] = 1;
		base[2][2] = 1;
		while (n)
		{
			if (n & 1) mul(ans, base, 1, 2, 2);
			mul(base, base, 2, 2, 2);
			n >>= 1;
		}
		write((ans[1][1] + MOD) % MOD);putchar(10);
	}

	return 0;
}
