#define DREP(i, s, e) for(int i = s; i >= e ;i--)
#define  REP(i, s, e) for(int i = s; i <= e ;i++)

#define DEBUG fprintf(stderr, "Passing [%s] in Line %d\n", __FUNCTION__, __LINE__)
#define chkmax(a, b) a = max(a, b)
#define chkmin(a, b) a = min(a, b)

#include <bits/stdc++.h>

using namespace std;
const int maxsr = 20 + 5, maxsg = 20 + 5, maxsb = 20 + 5, maxm = 60 + 5, maxn = maxsr + maxsg + maxsb;


int sr, sb, sg, m, n, MOD, ans;
int cir[maxm][maxn];

int vis[maxn], size[maxn], dp[maxn][maxn][maxn];
int calc(int x)
{
	int cnt = 0;
	memset(vis, 0, sizeof(vis));
	memset(size, 0, sizeof(size));
	REP(i, 1, n)
		if (!vis[i])
		{
			int p = cir[x][i];
			++cnt;
			while (!vis[p]) size[cnt]++, vis[p] = 1, p = cir[x][p];
		}
	memset(dp, 0, sizeof(dp));
	dp[0][0][0] = 1;
	REP(i, 1, cnt)
		DREP(j, sr, 0)
		DREP(k, sb, 0)
		DREP(l, sg, 0)
		{
			if (j >= size[i]) (dp[j][k][l] += dp[j - size[i]][k][l]) %= MOD;
			if (k >= size[i]) (dp[j][k][l] += dp[j][k - size[i]][l]) %= MOD;
			if (l >= size[i]) (dp[j][k][l] += dp[j][k][l - size[i]]) %= MOD;
		}
	return dp[sr][sb][sg];
}

int power_pow(int a, int b)
{
	int ans = 1, base = a;
	while (b)
	{
		if (b & 1) (ans *= base) %= MOD;
		(base *= base) %= MOD;
		b >>= 1;
	}
	return (ans + MOD) % MOD;
}
#define inv(x) power_pow(x, MOD - 2)

int main()
{
#ifdef CraZYali
	freopen("1004.in", "r", stdin);
	freopen("1004.out", "w", stdout);
#endif
	cin >> sr >> sb >> sg >> m >> MOD;
	n = sr + sb + sg;
	REP(i, 1, m)
		REP(j, 1, n)
		scanf("%d", cir[i] + j);
	++m;
	REP(i, 1, n) cir[m][i] = i;
	REP(i, 1, m) (ans += calc(i)) %= MOD;
	cout << ans * inv(m) % MOD << endl;
	return 0;
}
