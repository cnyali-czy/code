#define DREP(i, s, e) for(register int i = s; i >= e ;i--)
#define  REP(i, s, e) for(register int i = s; i <= e ;i++)

#define DEBUG fprintf(stderr, "Passing [%s] in Line %d\n", __FUNCTION__, __LINE__)
#define chkmax(a, b) a = max(a, b)
#define chkmin(a, b) a = min(a, b)

#include <bits/stdc++.h>

#define int long long
using namespace std;
const int maxn = 100 + 5, maxm = 10000 + 10;

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

int m, n, k;

int dp[maxm] = {1};

signed main()
{
#ifdef CraZYali
	freopen("5201.in", "r", stdin);
	freopen("5201.out", "w", stdout);
#endif
	cin >> n >> m;
	while (n --> 0)
	{
		register int res = read<int>();
		DREP(i, m, res)
			dp[i] += dp[i - res];
	}

	cout << dp[m];
	return 0;
}
