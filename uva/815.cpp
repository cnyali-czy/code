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
const int maxn = 30 + 5, maxm = 30 + 5, inf = (((1 << 30) - 1) << 1) + 1;

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
int m, n, k, region;

int a[maxn * maxm];

int main()
{
#ifdef CraZYali
	freopen("815.in", "r", stdin);
	freopen("815.out", "w", stdout);
#endif
	while (1)
	{
		n = read<int>();
		m = read<int>();
		if (!n && !m) return 0;
		printf("Region %d\n", ++region);
		REP(i, 1, n * m) a[i] = read<int>();
		sort(a + 1, a + 1 + n * m);
		a[n * m + 1] = inf;
		k = read<int>();

		register int sum(k), last(1);
		register double ans;
		REP(i, 1, n * m)
		{
			register double temp = (sum + a[i] * 100) * 1.0 / (i * 100);
			if (temp <= a[i + 1])
			{
				ans = temp;
				last = i;
				break;
			}
			else sum += a[i] * 100;
		}
		printf("Water level is %.2lf meters.\n%.2lf percent of the region is under water.\n\n", ans * 1.0, last * 100.0 / n / m );
	}
}
