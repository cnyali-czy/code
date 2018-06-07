#define DREP(i, s, e) for(register int i = s; i >= e ;i--)
#define  REP(i, s, e) for(register int i = s; i <= e ;i++)

#define DEBUG fprintf(stderr, "Passing [%s] in Line %d\n", __FUNCTION__, __LINE__)
#define chkmax(a, b) a = max(a, b)
#define chkmin(a, b) a = min(a, b)

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
const int maxn = 10000 + 10;

template <typename T> T read()
{
	T ans(0), p(1);
	char c = getchar();
	while (!isdigit(c)) {
		if (c == '-') p = -1;
		c = getchar();
	}
	while (isdigit(c)) {
		ans = ans * 10 + c - 48;
		c = getchar();
	}
	return ans * p;
}
int m, n, k;
double l[maxn], s;

inline int count(double x)
{
	int res = 0;
	REP(i, 1, n) res += (int)(l[i] / x);
	return res;
}

int main()
{
#ifdef CraZYali
	freopen("CableMaster.in", "r", stdin);
	freopen("CableMaster.out", "w", stdout);
#endif
	while (scanf("%d%d", &n, &m) * n * m)
	{
		s = 0.0;
		REP(i, 1, n) {scanf("%lf", l + i);s += l[i];}
		double l(0), r(s / m);
		while (r - l > 1e-9)
		{
			register double mid = (l + r) / 2.0;
			if (count(mid) >= m) l = mid;
			else r = mid;
		}
		printf("%.2f\n", (int)(r * 100) / 100.0);
	}
	return 0;
}
