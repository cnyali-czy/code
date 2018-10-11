#define  REP(i, s, e) for(register int i = s; i <= e ;i++)
#define DREP(i, s, e) for(register int i = s; i >= e ;i--)

#define DEBUG fprintf(stderr, "Passing [%s] in LINE %d\n", __FUNCTION__, __LINE__)
#define chkmin(a, b) a = min(a, b)
#define chkmax(a, b) a = max(a, b)

#include <bits/stdc++.h>

using namespace std;
const int maxn = 3000 + 10;

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
int a[maxn], b[maxn];

int dp[maxn];

int main()
{
#ifdef CraZYali
	freopen("5101.in", "r", stdin);
	freopen("5101.out", "w", stdout);
#endif
	cin >> n;
	REP(i, 1, n) scanf("%d", a + i);
	REP(i, 1, n) scanf("%d", b + i);

	REP(i, 1, n)
	{
		k = 0;
		REP(j, 1, n)
		{
			if (a[i] == b[j]) chkmax(dp[j], dp[k] + 1);
			if (a[i] > b[j]) if (dp[k] < dp[j]) k = j;
		}
	}
	register int ans = 1;
	REP(i, 1, n) chkmax(ans, dp[i]);
	cout << ans;
	return 0;
}
