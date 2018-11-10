#define DREP(i, s, e) for(register int i = s; i >= e ;i--)
#define  REP(i, s, e) for(register int i = s; i <= e ;i++)

#define DEBUG fprintf(stderr, "Passing [%s] in Line %d\n", __FUNCTION__, __LINE__)
#define chkmax(a, b) a = max(a, b)
#define chkmin(a, b) a = min(a, b)

#include <bits/stdc++.h>

using namespace std;
const int maxn = 1000 + 10;
const double eps = 1e-6;

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
	else
	{
		if (x / 10) write(x / 10);
		putchar(x % 10 + '0');
	}
}

int m, n, k;

int a[maxn], b[maxn];
double c[maxn];
bool cmp(double A, double B) {return A > B;}

bool check(double mid)
{
	REP(i, 1, n) c[i] = -mid * b[i] + a[i];
	sort(c + 1, c + 1 + n, cmp);
	double res = 0;
	REP(i, 1, n - m) res += c[i];
	return res >= 0;
}

int main()
{
#ifdef CraZYali
	freopen("2976-new.in", "r", stdin);
	freopen("2976-new.out", "w", stdout);
#endif
	while (scanf("%d%d", &n, &m) * n * m)
	{
		REP(i, 1, n) a[i] = read<int>();
		REP(i, 1, n) b[i] = read<int>();
		register double l = 0, r = 1e20;
		while (r - l > eps)
		{
			double mid = (l + r) / 2;
			if (check(mid)) l = mid;
			else r = mid;
		}
		printf("%.0lf\n", l * 100);
	}

	return 0;
}
