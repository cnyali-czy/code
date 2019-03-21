#define  REP(i, s, e) for (int i = s; i <= e; i++)
#define DREP(i, s, e) for (int i = s; i >= e; i--)
#define DEBUG fprintf(stderr, "Passing [%s] in Line %d\n", __FUNCTION__, __LINE__)

#define chkmax(a, b) a = max(a, b)
#define chkmin(a, b) a = min(a, b)

#include <iostream>
#include <cstdio>
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

int n, q[maxn], w[maxn];

signed main()
{
#ifdef CraZYali
	freopen("B.in", "r", stdin);
	freopen("B.out", "w", stdout);
#endif
	while (scanf("%lld", &n) * n)
	{
		q[0] = -1;
		int ans(0), top(0);
		REP(i, 1, n + 1)
		{
			int h = (i == n + 1 ? 0 : read<int>());
			if (h > q[top]) q[++top] = h, w[top] = 1;
			else
			{
				int cnt = 0;
				while (h <= q[top])
				{
					chkmax(ans, (w[top] + cnt) * q[top]);
					cnt += w[top--];
				}
				q[++top] = h;
				w[top] = cnt + 1;
			}
		}
		printf("%lld\n", ans);
	}
	return 0;
}
