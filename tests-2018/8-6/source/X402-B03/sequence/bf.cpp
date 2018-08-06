#define  REP(i, s, e) for(register int i = s; i <= e ;i++)
#define DREP(i, s, e) for(register int i = s; i >= e ;i--)

#define DEBUG fprintf(stderr, "Passing [%s] in LINE %d\n", __FUNCTION__, __LINE__)
#define chkmin(a, b) a = min(a, b)
#define chkmax(a, b) a = max(a, b)

#include <bits/stdc++.h>

using namespace std;

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

const int maxn = 1e6 + 10, maxk = 100 + 10, MOD = 1e9 + 7;

int m, n, k, ans;

int a[maxn], dp[maxn], mark[maxk];

int Mark[maxk];

void calc()
{
	REP(i, 1, k) Mark[i] = mark[i];
	REP(i, n + 1, n + m)
	{
		if (!Mark[a[i]]) dp[i] = (dp[i - 1] * 2 + 1) % MOD;
		else dp[i] = (dp[i - 1] * 2 - dp[Mark[a[i]] - 1]) % MOD;
		dp[i] = (dp[i] + MOD) % MOD;
		Mark[a[i]] = i;
	}
	chkmax(ans, dp[n + m]);
}

void dfs(int x)
{
	if (x == m) calc();
	else
	{
		x++;
		REP(i, 1, k)
		{
			a[n + x] = i;
			dfs(x);
		}
	}
}

int main()
{
	freopen("sequence.in", "r", stdin);
	freopen("sequence.out", "w", stdout);
	cin >> n >> m >> k;
	REP(i, 1, n) scanf("%d", a + i);	
	REP(i, 1, n)
	{
		if (!mark[a[i]]) dp[i] = (dp[i - 1] * 2 + 1) % MOD;
		else dp[i] = (dp[i - 1] * 2 - dp[mark[a[i]] - 1]) % MOD;
		dp[i] = (dp[i] + MOD) % MOD;
		mark[a[i]] = i;
	}
	ans = dp[n];
	dfs(0);
	cout << ans;
	return 0;
}
