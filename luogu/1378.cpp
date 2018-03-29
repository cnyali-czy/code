#define  REP(i, s, e) for(register int i = s; i <= e ;i++)
#define DREP(i, s, e) for(register int i = s; i >= e ;i--)

#define DEBUG fprintf(stderr, "Passing [%s] in LINE %d\n", __FUNCTION__, __LINE__)
#define chkmin(a, b) a = min(a, b)
#define chkmax(a, b) a = max(a, b)

#define dist(x1, y1, x2, y2) sqrt((x1 - x2) * (x1 - x2) + (y1 - y2) * (y1 - y2))

#include <bits/stdc++.h>

using namespace std;
const int maxn = 10;
const double pi = acos(-1.0);

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

#define point pair<int, int> 
#define x first
#define y second

point p[maxn];
inline void read(point &P)
{
	P.x = read<int>();
	P.y = read<int>();
}

double ans;

struct circle
{
	int x, y;
	double r;
}c[maxn];

bool vis[maxn];int A[maxn];

inline void calc()
{
	double res = 0;
	REP(i, 1, n)
	{
		double chose = 1e9;
		int t = A[i];
		REP(j, 1, i - 1)
			chkmin(chose, dist(p[t].x, p[t].y, c[j].x, c[j].y) - c[j].r);
		chkmin(chose, 1.0 * min(abs(p[t].x - p[0].x), abs(p[t].x - p[n + 1].x)));
		chkmin(chose, 1.0 * min(abs(p[t].y - p[0].y), abs(p[t].y - p[n + 1].y)));
		chkmax(chose, 0.0);
		c[i].r = chose;
		c[i].x = p[t].x;
		c[i].y = p[t].y;
		res += pi * c[i].r * c[i].r;
	}
	chkmax(ans, res);
}

void dfs(int x)
{
	if (x == n)
	{
		calc();
		return;
	}
	x++;
	REP(i, 1, n)
		if (!vis[i])
		{
			vis[A[x] = i] = 1;
			dfs(x);
			vis[i] = 0;
		}
}

int main()
{
#ifdef CraZYali
	freopen("1378.in", "r", stdin);
	freopen("1378.out", "w", stdout);
#endif
	n = read<int>();	
	read(p[0]);
	read(p[n + 1]);
	REP(i, 1, n) read(p[i]);
	dfs(0);
	printf("%.0lf", abs((p[0].x - p[n + 1].x) * (p[0].y - p[n + 1].y)) - ans);
	return 0;
}
