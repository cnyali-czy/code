#define DREP(i, s, e) for(register int i = s; i >= e ;i--)
#define  REP(i, s, e) for(register int i = s; i <= e ;i++)

#define DEBUG fprintf(stderr, "Passing [%s] in Line %d\n", __FUNCTION__, __LINE__)
#define chkmax(a, b) a = max(a, b)
#define chkmin(a, b) a = min(a, b)

#include <algorithm>
#include <iostream>
#include <cstdio>
#include <cmath>

using namespace std;
const int maxn = 1000 + 10;

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

const double eps = 1e-6;

int m, n, k;

int a[maxn], b[maxn];
double t[maxn];

bool cmp(double A, double B) {return A > B;}

bool check(double mid)
{
	REP(i, 1, n) t[i] = -mid * b[i] + a[i];
//	REP(i, 1, n) printf("%d - %d * %.2lf = %.2lf\n", a[i], b[i], mid, t[i]);
	sort(t + 1, t + 1 + n, cmp);
	register double res = 0;
	REP(i, 1, n - m) res += t[i];//, printf("%.2lf ",t[i]);
//	printf("\n%s\n", res >= 0 ? "Yes" : "No");
//	puts("-----------------");
	return res >= 0;
}

int main()
{
#ifdef CraZYali
	freopen("2976.in", "r", stdin);
	freopen("2976.out", "w", stdout);
#endif
	while (scanf("%d%d", &n, &m) * (n + m) )
	{
		REP(i, 1, n) scanf("%d", a + i);
		REP(i, 1, n) scanf("%d", b + i);

		register double l = 0, r = 1;
		while (r - l >= eps)
		{
			register double mid = (l + r) / 2;
			if (check(mid)) l = mid;
			else r = mid;
		}
		printf("%.0lf\n", l * 100);
	}
	
	return 0;
}
