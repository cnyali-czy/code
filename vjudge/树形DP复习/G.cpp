#define DREP(i, s, e) for(register int i = s; i >= e ;i--)
#define  REP(i, s, e) for(register int i = s; i <= e ;i++)

#define DEBUG fprintf(stderr, "Passing [%s] in Line %d\n", __FUNCTION__, __LINE__)
#define chkmax(a, b) a = max(a, b)
#define chkmin(a, b) a = min(a, b)

#include <bits/stdc++.h>

using namespace std;
const int maxn = 100 + 5, maxm = maxn;

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

int dp[maxm], temp[maxm];

int main()
{
#ifdef CraZYali
	freopen("G.in", "r", stdin);
	freopen("G.out", "w", stdout);
#endif
	while (scanf("%d%d", &n, &m) != EOF)
	{
		REP(i, 0, m) dp[i] = temp[i] = 0;
		REP(i, 1, n)
		{
			register int l = read<int>(), r = read<int>();
			if (i == 1) REP(j, l, r) dp[j] = 1;
			else
			{
				REP(j, 0, m)
				{
					REP(k, l, r)
						if (j + k <= m) temp[j + k] += dp[j];
						else break;
				}
				REP(j, 0, m)
				{
					dp[j] = temp[j];
					temp[j] = 0;
				}
			}
		}
		printf("%d\n", dp[m]);
	}
	return 0;
}
