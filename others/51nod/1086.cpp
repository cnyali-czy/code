#define DREP(i, s, e) for(register int i = s; i >= e ;i--)
#define  REP(i, s, e) for(register int i = s; i <= e ;i++)

#define DEBUG fprintf(stderr, "Passing [%s] in Line %d\n", __FUNCTION__, __LINE__)
#define chkmax(a, b) a = max(a, b)
#define chkmin(a, b) a = min(a, b)

#include <bits/stdc++.h>

using namespace std;
const int maxn = 50000 + 5, maxm = 50000 + 10;

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

int c[maxn], w[maxn], v[maxn];

int q[maxm], dp[maxm];

int calc(int i, int u, int k) {return dp[u + k * v[i]] - k * w[i];}

int main()
{
#ifdef CraZYali
	freopen("1086.in", "r", stdin);
	freopen("1086.out", "w", stdout);
#endif
	cin >> n >> m;
	memset(dp, 0xcf, sizeof(dp));
	dp[0] = 0;
	REP(i, 1, n)
	{
		scanf("%d%d%d", v + i, w + i, c + i);

		for (register int u = 0 ; u < v[i] ;u++)
		{
			register int l = 1, r = 0;
			register int maxp = (m - u) / v[i];
			DREP(k, maxp - 1, max(maxp - c[i], 0))
			{
				while (l <= r && calc(i, u, q[r]) <= calc(i, u, k)) r--;
				q[++r] = k;
			}
			DREP(p, maxp, 0)
			{
				while (l <= r && q[l] > p - 1) l++;
				if (l <= r) chkmax(dp[u + p * v[i]], calc(i, u, q[l]) + p * w[i]);
				if (p - c[i] - 1 >= 0)
				{
					while (l <= r && calc(i, u, q[r]) <= calc(i, u, p - c[i] - 1)) r--;
					q[++r] = p - c[i] - 1;
				}
			}
		}
	}

	register int ans = 0;
	REP(i, 1, m) chkmax(ans, dp[i]);
	cout << ans;

	return 0;
}
