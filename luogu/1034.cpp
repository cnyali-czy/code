#define DREP(i, s, e) for(register int i = s; i >= e ;i--)
#define  REP(i, s, e) for(register int i = s; i <= e ;i++)

#define DEBUG fprintf(stderr, "Passing [%s] in Line %d\n", __FUNCTION__, __LINE__)

#include <algorithm>
#include <iostream>
#include <cstdlib>
#include <cstring>
#include <cstdio>
#include <bitset>
#include <vector>
#include <cmath>
#include <queue>
#include <map>
#include <set>

using namespace std;
const int maxn = 50 + 5, maxk = 5, inf = (((1 << 30) - 1) << 1) + 1;

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
int belong[maxn];

struct area
{
	int x1, x2, y1, y2;
	inline void init() {x1 = y1 = inf;x2 = y2 = -inf;}
}a[maxk];

inline bool judge()
{
	REP(i, 1, n)
		REP(j, 1, n)
			if (i ^ j && a[i].x2 >= a[j].x1 && a[i].x1 <= a[j].x2 && (a[i].y1 >= a[j].y1 && a[i].y1 <= a[j].y2) || (a[j].y1 >= a[i].y1 && a[j].y1 <= a[i].y2)) return 0;
	return 1;
}

int ans = inf;
int xxx[maxn], y[maxn];

void dfs(int x)
{
	if (x == n)
	{
		REP(i, 1, k) a[i].init();
		REP(i, 1, n)
		{
			a[belong[i]].x1 = min(a[belong[i]].x1, xxx[i]);
			a[belong[i]].x2 = max(a[belong[i]].x2, xxx[i]);
			a[belong[i]].y1 = min(a[belong[i]].y1, y[i]);
			a[belong[i]].y2 = max(a[belong[i]].y2, y[i]);
		}
		if (!judge()) return;
		int res = 0;
		REP(i, 1, k)
			res += (a[i].x1 - a[i].x2) * (a[i].y1 - a[i].y2);
		ans = min(ans, res);
	}
	else
	{
		x++;
		REP(i, 1, k)
		{
			belong[x] = i;
			dfs(x);
		}
	}
}

int main()
{
#ifdef CraZYali
	freopen("1034.in", "r", stdin);
	freopen("1034.out", "w", stdout);
#endif
	n = read<int>();
	k = read<int>();
	REP(i, 1, n)
	{
		xxx[i] = read<int>();
		y[i] = read<int>();
	}
	dfs(0);
	cout << ans;
	return 0;
}
