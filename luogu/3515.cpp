#define  REP(i, s, e) for (int i(s); i <= e; i++)
#define DREP(i, s, e) for (int i(s); i >= e; i--)
#define DEBUG fprintf(stderr, "Passing [%s] in Line %d\n", __FUNCTION__, __LINE__)

#define chkmax(a, b) a = max(a, b)
#define chkmin(a, b) a = min(a, b)

#include <iostream>
#include <cstdio>
#include <cmath>

using namespace std;
const int maxn = 6000000 + 10;

double f1[maxn], f2[maxn];
int n, a[maxn];
void solve1(int l, int r, int L, int R)
{
	if (L > R) return;
	int mid(L + R >> 1), g(0);
	double tmp(0);
	f1[mid] = a[mid];
	REP(i, l, min(r, mid)) if ((tmp = a[i] + sqrt(mid-i)) > f1[mid]) f1[mid] = tmp, g = i;
	if (!g) g = mid;
	f1[mid] -= a[mid];
	solve1(l, g, L, mid-1);
	solve1(g, r, mid+1, R);
}
void solve2(int l, int r, int L, int R)
{
	if (L > R) return;
	int mid(L + R >> 1), g(0);
	double tmp(0);
	f2[mid] = a[mid];
	DREP(i, r, max(l, mid)) if ((tmp = a[i] + sqrt(i-mid)) > f2[mid]) f2[mid] = tmp, g = i;
	if (!g) g = mid;
	f2[mid] -= a[mid];
	solve2(l, g, L, mid-1);
	solve2(g, r, mid+1, R);
}
int main()
{
#ifdef CraZYali
	freopen("3515.in", "r", stdin);
	freopen("3515.out", "w", stdout);
#endif
	cin >> n;
	REP(i, 1, n) scanf("%d", a + i);
	solve1(1, n, 1, n);
	solve2(1, n, 1, n);
	REP(i, 1, n)
		printf("%lld\n", (long long)ceil(max(f1[i], f2[i])));
	return 0;
}
