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
const int maxn = 40;

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

unsigned long long f[maxn][maxn];

int main()
{
#ifdef CraZYali
	freopen("11077.in", "r", stdin);
	freopen("11077.out", "w", stdout);
#endif
	f[1][0] = 1;
	REP(i, 2, 21)
		REP(j, 0, i - 1)
		{
			f[i][j] = f[i - 1][j];
			if (j) f[i][j] += f[i-1][j-1] * (i - 1);
		}
	while (1)
	{
		n = read<int>();
		k = read<int>();
		if (n) printf("%llu\n", f[n][k]);
		else break;
	}

	
	return 0;
}
