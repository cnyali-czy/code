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
int A, B, C;

int main()
{
#ifdef CraZYali
	freopen("10755.in", "r", stdin);
	freopen("10755.out", "w", stdout);
#endif
	register int T = read<int>();
	register bool first = 1;
	while (T --> 0)
	{
		if (!first) putchar(10);
		else first = 0;
		A = read<int>();
		B = read<int>();
		C = read<int>();
		REP(i, 1, A)
			REP(j, 1, B)
				REP(k, 1, c)
					a[i][j][k] = read<int>();

	}

	return 0;
}
