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
const int maxn = 100010;

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

int main()
{
#ifdef CraZYali
	freopen("1984.in", "r", stdin);
	freopen("1984.out", "w", stdout);
#endif
	n = read<int>();
	double ans = 0, now = 4200.0 / n * 100;
	REP(i, 1, n)
	{
		ans += now;
		now *= (i * 2.0 - 1) * 1.0 /(i * 2.0);;
	}
	printf("%.2lf", ans);
	return 0;
}
