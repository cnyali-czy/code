#define DREP(i, s, e) for(register int i = s; i >= e ;i--)
#define  REP(i, s, e) for(register int i = s; i <= e ;i++)

#define DEBUG fprintf(stderr, "Passing [%s] in Line %d\n", __FUNCTION__, __LINE__)
#define chkmax(a, b) a = max(a, b)
#define chkmin(a, b) a = min(a, b)

#include <bits/stdc++.h>
#define double long double

using namespace std;
const double eps = 1e-16, k = 0.987;
const int maxn = 1e4 + 10;

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

int m, n;

double x[maxn], y[maxn], ansX, ansY, ans;
#define dis(x1, y1, x2, y2) sqrt((x1 - x2) * (x1 - x2) + (y1 - y2) * (y1 - y2))
double calc(double tx, double ty)
{
	double res = 0;
	REP(i, 1, n) res += dis(tx, ty, x[i], y[i]);
	return res;
}

void work()
{
	double X = ansX, Y = ansY;
	register double T = 233;
	while (T > eps)
	{
		double tx = X + (rand() * 2 - RAND_MAX) * T, ty = Y + (rand() * 2 - RAND_MAX) * T, tans = calc(tx, ty);
		double delta = tans - ans;
		if (delta < eps || exp(-delta / T) * RAND_MAX > rand())
		{
			X = tx;Y = ty;
			if (delta < eps)
			{
				ans = tans;
				ansX = X;ansY = Y;
			}
		}
		T *= k;
	}
}

int main()
{
#ifdef CraZYali
	freopen("10228.in", "r", stdin);
	freopen("10228.out", "w", stdout);
#endif
	srand(time(0));
	register int T = read<int>();
	double divide = 2.8 / T;
	bool first = 1;
	while (T --> 0)
	{
		double now = clock();
		if (first) first = 0;
		else putchar(10);
		n = read<int>();
		ansX = ansY = 0;
		REP(i, 1, n) ansX += (x[i] = read<int>()), ansY += (y[i] = read<int>());
		ans = calc(ansX, ansY);
		while ((clock() - now) / CLOCKS_PER_SEC <= divide) work();
		printf("%.0Lf\n", ans);
	}
	
	return 0;
}
