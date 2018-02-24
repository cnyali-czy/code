#define  REP(i, s, e) for(register int i = s; i <= e ;i++)
#define DREP(i, s, e) for(register int i = s; i >= e ;i--)

#define DEBUG fprintf(stderr, "Passing [%s] in LINE %d\n", __FUNCTION__, __LINE__)
#define chkmin(a, b) a = min(a, b)
#define chkmax(a, b) a = max(a, b)

#include <bits/stdc++.h>

using namespace std;
const int maxn = 1e3 + 10;

template <typename T> T read()
{
	T ans(0), p(1);
	char c = getchar();
	while (!isdigit(c))
	{
		if (c == '-') p = -1;
		c = getchar();
	}
	while (isdigit(c))
	{
		ans = ans * 10 + c - 48;
		c = getchar();
	}
	return ans * p;
}

int m, n, k;

int after[5][5] = {{1, 9, 2, 6}, {0, 0, 2, 3}, {0, 0, 2, 4}, {0, 0, 4, 3}, {0, 0, 4, 4}};
/*
1 : White
2 : Green
3 : Red
4 : Yellow
*/

int a[maxn][maxn], ans[5];

namespace CHEAT
{
	const int maxnn = 1e5 + 10;
	int c[maxnn];
}
inline void cheat()
{
	using namespace CHEAT;
	REP(i, 1, n) c[i] = 1;
	while (m--)
	{
		read<int>();
		int pos(read<int>()), color(read<int>() + 2);
		c[pos] = after[c[pos]][color];
	}
	REP(i, 1, n) ans[c[i]] += n;
}

int main()
{
	freopen("c.in", "r", stdin);
	freopen("bf.out", "w", stdout);
	n = read<int>();
	m = read<int>();
	cheat();
	printf("%d %d %d %d", ans[1], ans[2], ans[3], ans[4]);	
	return 0;
}
