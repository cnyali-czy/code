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

int a[maxn], b[maxn], c[maxn];
inline double S(int i, double x) {return a[i] * x * x + b[i] * x + c[i];}
inline double F(double x)
{
	double ans = S(1, x);
	REP(i, 2, n) chkmax(ans, S(i, x));
	return ans;
}


int main()
{
#ifdef CraZYali
	freopen("5009.in", "r", stdin);
	freopen("5009.out", "w", stdout);
#endif
	register int T = read<int>();
	while (T--)
	{
		n = read<int>();
		REP(i, 1, n) a[i] = read<int>(), b[i] = read<int>(), c[i] = read<int>();
		double l = 0.0, r = 1000.0;
		register int Times = 100;
		while (Times--)
		{
			double m1 = l + (r - l) / 3;
			double m2 = r - (r - l) / 3;
			if (F(m1) >= F(m2)) l = m1;
			else r = m2;
		}
		printf("%.4lf\n", F(l));
	}

	return 0;
}

