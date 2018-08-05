#define  REP(i, s, e) for(register int i = s; i <= e ;i++)
#define DREP(i, s, e) for(register int i = s; i >= e ;i--)

#define DEBUG fprintf(stderr, "Passing [%s] in LINE %d\n", __FUNCTION__, __LINE__)
#define chkmin(a, b) a = min(a, b)
#define chkmax(a, b) a = max(a, b)

#include <bits/stdc++.h>

using namespace std;
const int maxn = 3000;

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

int x[maxn << 1], y[maxn << 1];

#define dist(x1, y1, x2, y2) sqrt((x1 - x2) * (x1 - x2) + (y1 - y2) * (y1 - y2))

bool pick[maxn << 1];

double ans = -1e20;

namespace bf
{
	inline void calc()
	{
		double res = 0;
		REP(i, 1, n * 2)
			if (pick[i])
				REP(j, i + 1, n * 2)
					if (pick[j])
						res += dist(x[i], y[i], x[j], y[j]);
		REP(i, 1, n * 2)
			if (!pick[i])
				REP(j, i + 1, n * 2)
					if (!pick[j])
						res -= dist(x[i], y[i], x[j], y[j]);
		chkmax(ans, res);
	}

	void dfs(int x, int tt)
	{
		if (n + tt < x) return;
		if (tt > n) return;
		if (tt == n)
		{
			calc();
			return;
		}
		x++;
		pick[x] = 1;
		dfs(x, tt + 1);
		pick[x] = 0;
		dfs(x, tt);
	}
}

int main()
{
	freopen("by.in", "r", stdin);
	freopen("by.out", "w", stdout);
	cin >> n;
	REP(i, 1, n * 2)
		x[i] = read<int>(), y[i] = read<int>();
	if (n <= 5) bf::dfs(0, 0);
//	else yiszero::work();
	printf("%.0lf", ans);
	return 0;
}
