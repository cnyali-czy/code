#define DREP(i, s, e) for(register int i = s; i >= e ;i--)
#define  REP(i, s, e) for(register int i = s; i <= e ;i++)

#define DEBUG fprintf(stderr, "Passing [%s] in Line %d\n", __FUNCTION__, __LINE__)
#define chkmax(a, b) a = max(a, b)
#define chkmin(a, b) a = min(a, b)

#include <bits/stdc++.h>

using namespace std;
const int maxn = 100000 + 10, maxm = 1000 + 10;

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

double dp[maxn];
pair <int, int> A[maxm];

bool cmp(pair <int, int> AAA, pair <int, int> BBB) {return AAA.first < BBB.first;}

int main()
{
#ifdef CraZYali
	freopen("B.in", "r", stdin);
	freopen("B.out", "w", stdout);
#endif
	A[0].first = -1;
	while (scanf("%d%d", &n, &m) * (n + m))
	{
		REP(i, 1, m)
			scanf("%d%d", &A[i].first, &A[i].second);
		sort(A + 1, A + 1 + m, cmp);

		register int now = m;
		REP(i, 0, n + 5) dp[i] = 0 ;

		DREP(i, n-1, 0)
			if (A[now].first == i)
			{
				dp[i] = dp[A[now].second];
				now--;
			}
			else
			{
				REP(j, 1, 6)
					if (i + j >= n) break;
					else dp[i] += dp[i + j] * 1.0 / 6;
				dp[i] += 1;
			}
		printf("%.4lf\n", dp[0]);
	}
	
	return 0;
}
