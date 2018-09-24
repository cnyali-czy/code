#define DREP(i, s, e) for(register int i = s; i >= e ;i--)
#define  REP(i, s, e) for(register int i = s; i <= e ;i++)

#define DEBUG fprintf(stderr, "Passing [%s] in Line %d\n", __FUNCTION__, __LINE__)
#define chkmax(a, b) a = max(a, b)
#define chkmin(a, b) a = min(a, b)

#include <bits/stdc++.h>

using namespace std;
const int maxn = 200 + 5;

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

int a[maxn];

int dp[maxn][maxn];

int main()
{
#ifdef CraZYali
	freopen("5E09.in", "r", stdin);
	freopen("5E09.out", "w", stdout);
#endif
	cin >> n;
	REP(i, 1, n)
	{
		scanf("%d", a + i);
		a[i + n] = a[i];
	}

	REP(j, 2, n * 2)
		DREP(i, j - 1, max(1, j - n + 1))
			REP(k, i, j - 1)
				chkmax(dp[i][j], dp[i][k] + dp[k+1][j] + a[i] * a[k+1] * a[j+1]);
	register int ans = -1;
	REP(i, 1, n * 2)
		REP(j, i + 1, n * 2) chkmax(ans, dp[i][j]);
	cout << ans;
	return 0;
}
