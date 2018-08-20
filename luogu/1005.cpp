#define DREP(i, s, e) for(register int i = s; i >= e ;i--)
#define  REP(i, s, e) for(register int i = s; i <= e ;i++)

#define DEBUG fprintf(stderr, "Passing [%s] in Line %d\n", __FUNCTION__, __LINE__)
#define chkmax(a, b) a = max(a, b)
#define chkmin(a, b) a = min(a, b)

#include <iostream>
#include <cstdio>
#include <cstring>

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
const int maxn = 100;

int m, n, k;

typedef __int128 BigInt;

BigInt a[maxn], dp[maxn][maxn];

BigInt power_pow(BigInt x)
{
	BigInt ans = 1;
	ans <<= x;
	return ans;
}

BigInt dfs(BigInt now, BigInt l, BigInt r)
{
	if (dp[l][r] != -1) return dp[l][r];
	if (r - l + 1 >= 2) return dp[l][r] = max(a[l] * power_pow(now) + dfs(now + 1, l + 1, r), a[r] * power_pow(now) + dfs(now + 1, l, r - 1));
	else return dp[l][r] = a[l] * power_pow(now);
}

int main()
{
#ifdef CraZYali
	freopen("1005.in", "r", stdin);
	freopen("1005.out", "w", stdout);
#endif
	register BigInt ans = 0;
	cin >> m >> n;
	while (m --> 0)
	{
		REP(i, 1, n)
		{
			a[i] = read<BigInt>();
			REP(j, 1, n) dp[i][j] = -1;
		}
		ans += dfs(1, 1, n);
	}
	write(ans);
	
	return 0;
}
