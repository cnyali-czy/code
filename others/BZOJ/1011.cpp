#define DREP(i, s, e) for(int i = s; i >= e ;i--)
#define  REP(i, s, e) for(int i = s; i <= e ;i++)

#define DEBUG fprintf(stderr, "Passing [%s] in Line %d\n", __FUNCTION__, __LINE__)
#define chkmax(a, b) a = max(a, b)
#define chkmin(a, b) a = min(a, b)

#include <bits/stdc++.h>

using namespace std;
const int maxn = 1e5 + 10;

int n;
double m[maxn], Sum[maxn];
double a;

int main()
{
#ifdef CraZYali
	freopen("1011.in", "r", stdin);
	freopen("1011.out", "w", stdout);
#endif
	cin >> n >> a;
	REP(i, 1, n) scanf("%lf", m + i), Sum[i] = Sum[i-1] + m[i];
	REP(cur, 1, n)
	{
		int lim = cur * a + 1e-8;
		if (cur <= 1000)
		{
			double ans = 0;
			REP(i, 1, lim) ans += m[i] * m[cur] / (cur - i);
			printf("%lf\n", ans);
		}
		else printf("%lf\n", Sum[lim] * m[cur] / (cur - lim / 2));
	}
	return 0;
}
