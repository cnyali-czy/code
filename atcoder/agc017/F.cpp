#define DREP(i, s, e) for(register int i = s; i >= e ;i--)
#define  REP(i, s, e) for(register int i = s; i <= e ;i++)

#define DEBUG fprintf(stderr, "Passing [%s] in Line %d\n", __FUNCTION__, __LINE__)
#define chkmax(a, b) a = max(a, b)
#define chkmin(a, b) a = min(a, b)

#include <bits/stdc++.h>

using namespace std;
const int maxn = 20 + 5, MOD = 1e9 + 7, maxt = (1 << 21) + 10;

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

int n, m, k, ret, tmp, lim;
int nxt[maxt][maxn], a[maxn][maxn], dp[2][maxn][maxt];

int main()
{
#ifdef CraZYali
	freopen("F.in", "r", stdin);
	freopen("F.out", "w", stdout);
#endif
	n = read<int>() - 1, m = read<int>(), k = read<int>(), lim = (1 << n) - 1;
	REP(i, 0, lim)
	{
		ret = -1;
		DREP(j, n - 1, 0)
		{
			if (i & (1 << j)) ret = j;
			nxt[i][j] = ret;
		}
	}
	memset(a, -1, sizeof(a));
	while (k --> 0)
	{
		register int x(read<int>()), y(read<int>()), z(read<int>());
		a[x][y-1] = z;
	}
	dp[0][n][0] = 1;
	int cur = 1;
	REP(i, 1, m)
	{
		REP(s, 0, lim) dp[cur][0][s] = dp[cur ^ 1][n][s];
		REP(j, 0, n)
			REP(s, 0, lim)
			dp[cur ^ 1][j][s] = 0;
		REP(j, 0, n - 1)
			REP(s, 0, lim)
			if (dp[cur][j][s])
			{
				REP(k, 0, 1)
				{
					if (a[i][j] != -1 && a[i][j] != k) continue;
					ret = (s & (1 << j));
					if (ret) ret = 1;
					if (k == 0 && ret == 1) continue;
					if (k == ret) (dp[cur][j+1][s] += dp[cur][j][s]) %= MOD;
					else
					{
						tmp = nxt[s][j];
						if (tmp == -1) (dp[cur][j+1][s + (1 << j)] += dp[cur][j][s]) %= MOD;
						else (dp[cur][j+1][s + (1 << j) - (1 << tmp)] += dp[cur][j][s]) %= MOD;
					}
				}
			}
		cur ^= 1;
	}
	cur ^= 1;
	int ans = 0;
	REP(s, 0, lim) (ans += dp[cur][n][s]) %= MOD;
	cout << (ans + MOD) % MOD << endl;
	return 0;
}
