#define  REP(i, s, e) for(register int i = s; i <= e ;i++)
#define DREP(i, s, e) for(register int i = s; i >= e ;i--)

#define DEBUG fprintf(stderr, "Passing [%s] in LINE %d\n", __FUNCTION__, __LINE__)
#define chkmin(a, b) a = min(a, b)
#define chkmax(a, b) a = max(a, b)

#include <bits/stdc++.h>
#define int long long

using namespace std;
const int maxn = 1000 + 10, maxm = 200 + 10, MOD = 1e9 + 7;

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

int dp[maxm][maxm], s[maxm][maxm];

int m, n, k, l1, l2;
char a[maxn], b[maxn];

signed main()
{
#ifdef CraZYali
	freopen("2679.in", "r", stdin);
	freopen("2679.out", "w", stdout);
#endif
	dp[0][0] = 1;
	cin >> l1 >> l2 >> k;
	scanf("%s\n%s", a + 1, b + 1);
	REP(i, 1, l1)
		DREP(j, l2, 1)
		DREP(K, k, 1)
		dp[j][K] = (dp[j][K] + (s[j][K] = (a[i] == b[j]) * (s[j-1][K] + dp[j-1][K-1]))) % MOD;

	cout << dp[l2][k];
	return 0;
}
