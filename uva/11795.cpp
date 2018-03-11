#define  REP(i, s, e) for(register int i = s; i <= e ;i++)
#define DREP(i, s, e) for(register int i = s; i >= e ;i--)

#define DEBUG fprintf(stderr, "Passing [%s] in LINE %d\n", __FUNCTION__, __LINE__)
#define chkmin(a, b) a = min(a, b)
#define chkmax(a, b) a = max(a, b)

#include <bits/stdc++.h>

using namespace std;
const int maxn = 20;

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

int m, n, k;

char s[maxn];
int weapon[maxn], Kill[1 << maxn];
long long dp[1 << maxn];

int main()
{
#ifdef CraZYali
	freopen("11795.in", "r", stdin);
	freopen("11795.out", "w", stdout);
#endif
	register int T = read<int>();
	REP(Case, 1, T)
	{
		n = read<int>();
		memset(weapon, 0, sizeof(weapon));
		memset(dp, 0, sizeof(dp));
		REP(i, 0, n)
		{
			scanf("%s", s + 1);
			REP(j, 1, n)
				if (s[j] == '1') weapon[i] |= (1 << j);
		}
		int AK = (1 << (n + 1)) - 1;
		REP(i, 0, AK)
			REP(j, 0, n)
				if (i & (1 << j))
					Kill[i] |= weapon[j];
		dp[1] = 1;
		REP(i, 0, AK - 1)
			REP(j, 1, n)
				if ((Kill[i] & (1 << j)) && !(i & (1 << j)))
					dp[i | (1 << j)] += dp[i];
		printf("Case %d: %lld\n", Case, dp[AK]);
	}


	return 0;
}
