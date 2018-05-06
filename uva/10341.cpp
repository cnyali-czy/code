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
const double eps = 1e-9;

int m, n, k;

int p, q, r, s, t, u;
inline double F(double x) {return p * exp(-x) + q * sin(x) + r * cos(x) + s * tan(x) + t * x * x + u;}

int main()
{
#ifdef CraZYali
	freopen("10341.in", "r", stdin);
	freopen("10341.out", "w", stdout);
#endif
	while (scanf("%d%d%d%d%d%d", &p, &q, &r, &s, &t, &u) != EOF)
	{
		double F0(F(0)), F1(F(1));
		if (F0 < -eps || F1 > eps) printf("No solution\n");
		else
		{
			register double l, r, mid, ll, rr;
			l = 0;r = 1;
			do
			{
				ll = l;rr = r;
				mid = (l + r) / 2;
				if (F(mid) > 0) l = mid;
				else r = mid;
			}while (l <= r && (ll != l || rr != r));
			printf("%.4lf\n", mid);
		}
	}

	return 0;
}
