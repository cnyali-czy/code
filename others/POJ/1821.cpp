#define DREP(i, s, e) for(register int i = s; i >= e ;i--)
#define  REP(i, s, e) for(register int i = s; i <= e ;i++)

#define DEBUG fprintf(stderr, "Passing [%s] in Line %d\n", __FUNCTION__, __LINE__)
#define chkmax(a, b) a = max(a, b)
#define chkmin(a, b) a = min(a, b)

#include <algorithm>
#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cstring>

using namespace std;
const int maxn = 100 + 5, maxm = 16000 + 10;

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

struct Worker
{
	int l, p, s;
	bool operator < (Worker B) const {return s < B.s;}
}w[maxn];

int dp[maxn][maxm], q[maxm];

int calc(int i, int k) {return dp[i-1][k] - w[i].p * k;}

int main()
{
#ifdef CraZYali
	freopen("1821.in", "r", stdin);
	freopen("1821.out", "w", stdout);
#endif
	cin >> m >> n;
	REP(i, 1, n)
		scanf("%d%d%d", &w[i].l, &w[i].p, &w[i].s);
	sort(w + 1, w + 1 + n);
	REP(i, 1, n)
	{
		register int l = 1, r = 0;
		for (register int k = max(0, w[i].s - w[i].l) ; k <= w[i].s - 1; k++)
		{
			while (l <= r && calc(i, q[r]) <= calc(i, k)) r--;
			q[++r] = k;
		}
		REP(j, 1, m)
		{
			dp[i][j] = max(dp[i][j-1], dp[i-1][j]);
			if (j >= w[i].s)
			{
				while (l <= r && q[l] < j - w[i].l) l++;
				if (l <= r) chkmax(dp[i][j], calc(i, q[l]) + w[i].p * j);
			}
		}
	}
	cout << dp[n][m];

	return 0;
}
