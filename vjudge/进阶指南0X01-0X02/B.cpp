#define  REP(i, s, e) for (int i = s; i <= e; i++)
#define DREP(i, s, e) for (int i = s; i >= e; i--)
#define DEBUG fprintf(stderr, "Passing [%s] in Line %d\n", __FUNCTION__, __LINE__)

#define chkmax(a, b) a = max(a, b)
#define chkmin(a, b) a = min(a, b)

#include <bits/stdc++.h>
#define int long long

using namespace std;
const int maxn = 1e6 + 10;

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

int to[][10] = 
{
	{1, 3, -1, -1, 1, -1},
	{0, 2, 4, 5, 0, 4}
};
bool cur;
int dp[6][2], ans[maxn];
int MOD, L;
char c[] = {'f', 'm'};

signed main()
{
#ifdef CraZYali
	freopen("B.in", "r", stdin);
	freopen("B.out", "w", stdout);
#endif
	REP(i, 0, 5) dp[i][cur] = 1;
	ans[3] = 6;
	L = 1e6;
	int mod = 2329089562800ll;
	REP(i, 4, L)
	{
		cur ^= 1;
		REP(j, 0, 5) dp[j][cur] = 0;
		REP(j, 0, 5)
			if (dp[j][cur ^ 1] > 0)
				REP(k, 0, 1)
					if (to[k][j] != -1) (dp[to[k][j]][cur] += dp[j][cur ^ 1]) %= mod;
		REP(j, 0, 5) (ans[i] += dp[j][cur]) %= mod;
	}
	while (scanf("%lld%lld", &L, &MOD) != EOF)
	{
		if (!L) printf("0\n");
		else if (L == 1) printf("%d\n", 2 % MOD);
		else if (L == 2) printf("%d\n", 4 % MOD);
		else printf("%lld\n", ans[L] % MOD);
	}
	return 0;
}
