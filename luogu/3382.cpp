#define  REP(i, s, e) for (register int i = s; i <= e; i++)
#define DREP(i, s, e) for (register int i = s; i >= e; i--)
#define DEBUG fprintf(stderr, "Passing [%s] in Line %d\n", __FUNCTION__, __LINE__)

#define chkmax(a, b) a = max(a, b)
#define chkmin(a, b) a = min(a, b)

#include <bits/stdc++.h>

using namespace std;
const int maxn = 20;
const double eps = 1e-7;

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

int N;
double a[maxn], l, r;
double f(double x)
{
	register double F = 0;
	DREP(i, N, 0) F = F * x + a[i];
	return F;
}

int main()
{
#ifdef CraZYali
	freopen("3382.in", "r", stdin);
	freopen("3382.out", "w", stdout);
#endif
	cin >> N >> l >> r;
	DREP(i, N, 0) scanf("%lf", a + i);
	while (r - l > eps)
	{
		double mid1 = l + (r - l) / 3;
		double mid2 = r - (r - l) / 3;
		if (f(mid1) < f(mid2)) l = mid1;
		else r = mid2;
	}
	printf("%.5lf", (l + r) / 2);
	return 0;
}
