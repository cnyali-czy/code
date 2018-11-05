#define DREP(i, s, e) for(register int i = s; i >= e ;i--)
#define  REP(i, s, e) for(register int i = s; i <= e ;i++)

#define DEBUG fprintf(stderr, "Passing [%s] in Line %d\n", __FUNCTION__, __LINE__)
#define chkmax(a, b) a = max(a, b)
#define chkmin(a, b) a = min(a, b)

#include <bits/stdc++.h>
#define double long double

using namespace std;
const int maxn = 1000 + 10;
const double eps = 1e-16, k = 0.97;

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
int x[maxn], y[maxn], w[maxn];

#define dis(x1, y1, x2, y2) sqrt((x1 - x2) * (x1 - x2) + (y1 - y2) * (y1 - y2))
double f(double tx, double ty)
{
	double res = 0;
	REP(i, 1, n) res += dis(tx, ty, x[i], y[i]) * w[i];
	return res;
}

double ansX, ansY, ans;
void SA()
{
	double X = ansX, Y = ansY;
	double T = 100;
	while (T > eps)
	{
		double tx = X + (rand() * 2 - RAND_MAX) * T, ty = Y + (rand() * 2 - RAND_MAX) * T, tans = f(tx, ty);
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
	freopen("1337.in", "r", stdin);
	freopen("1337.out", "w", stdout);
#endif
	double now = clock();
	n = read<int>();
	srand(time(0) ^ n);
	REP(i, 1, n) ansX += x[i] = read<int>(), ansY += y[i] = read<int>(), w[i] = read<int>();
	ansX /= n;ansY /= n;
	ans = f(ansX, ansY);

	while ((clock() - now) / CLOCKS_PER_SEC <= 0.8) SA();
	printf("%.3LF %.3LF\n", ansX, ansY);
	return 0;
}
