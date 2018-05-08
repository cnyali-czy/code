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
const int maxn = 1000 + 10, maxm = 1000 + 10;

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
double f[maxn], p[maxn];


int main()
{
#ifdef CraZYali
	freopen("11021.in", "r", stdin);
	freopen("11021.out", "w", stdout);
#endif
	register int T = read<int>(), Case = 0;
	while (T --> 0)
	{
		n = read<int>();
		k = read<int>();
		m = read<int>();
		REP(i, 1, n) scanf("%lf", p + i);
		f[1] = p[1];
		REP(i, 2, m)
		{
			f[i] = 0;
			REP(j, 1, n) f[i] += p[j] * pow(f[i - 1], j - 1);
		}
		printf("Case #%d: %.7lf\n", ++Case, pow(f[m], k));
	}
	
	return 0;
}
