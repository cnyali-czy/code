#define DREP(i, s, e) for(int i = s; i >= e ;i--)
#define  REP(i, s, e) for(int i = s; i <= e ;i++)

#define DEBUG fprintf(stderr, "Passing [%s] in Line %d\n", __FUNCTION__, __LINE__)
#define chkmax(a, b) a = max(a, b)
#define chkmin(a, b) a = min(a, b)

#include <iostream>
#include <cstdio>
#include <cmath>

#define dis(x1, y1, x2, y2) sqrt((x1 - x2) * (x1 - x2) + (y1 - y2) * (y1 - y2))
#define ll long long

using namespace std;

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

int n;
ll h, o;
void calc(int n, ll id, ll &x, ll &y)
{
	if (n == 1)
	{
		if (id == 1) x = 1, y = 1;
		else if (id == 2) x = 1, y = 2;
		else if (id == 3) x = 2, y = 2;
		else x = 2, y = 1;
	}
	else
	{
		ll _id = (1ll << n - 1) * (1ll << n - 1);
		if (id <= _id) calc(n - 1, id, y, x);
		else if (id <= _id * 2)
		{
			calc(n - 1, id - _id, x, y);
			y += 1ll << n - 1;
		}
		else if (id <= _id * 3)
		{
			calc(n - 1, id - 2 * _id, x, y);
			x += 1ll << n - 1;
			y += 1ll << n - 1;
		}
		else
		{
			calc(n - 1, id - 3 * _id, y, x);
			x = (1ll << n) + 1 - x;
			y = (1ll << n - 1) + 1 - y;
		}
	}
}

signed main()
{
#ifdef CraZYali
	freopen("B.in", "r", stdin);
	freopen("B.out", "w", stdout);
#endif
	int T = read<int>();
	while (T --> 0)
	{
		n = read<int>();h = read<ll>();o = read<ll>();
		ll sx, sy, ex, ey;
		calc(n, h, sx, sy);
		calc(n, o, ex, ey);
		printf("%.0f\n", dis(sx, sy, ex, ey) * 10);
		fflush(stdout);
	}
	return 0;
}
