#define DREP(i, s, e) for(register int i = s; i >= e ;i--)
#define  REP(i, s, e) for(register int i = s; i <= e ;i++)

#define DEBUG fprintf(stderr, "Passing [%s] in Line %d\n", __FUNCTION__, __LINE__)
#define chkmax(a, b) a = max(a, b)
#define chkmin(a, b) a = min(a, b)

#include <bits/stdc++.h>

using namespace std;
const int maxn = 1e5 + 10;

template <typename T> inline T read()
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

template <typename T> void write(T x)
{
	if (x < 0) putchar('-'), write(-x);
	else if (x / 10) write(x / 10);
	putchar(x % 10 + '0');
}

int m, n, k;
int a[maxn], Max[maxn][30], grand[maxn][30];

int main()
{
#ifdef CraZYali
	freopen("3865.in", "r", stdin);
	freopen("3865.out", "w", stdout);
#endif
	cin >> n >> m;
	REP(i, 1, n) a[i] = read<int>();
	REP(i, 1, n) Max[i][0] = a[i + 1];
	REP(j, 1, 30)
		REP(i, 1, n)
			if (i + (1 << j-1) <= n) Max[i][j] = max(Max[i][j-1], Max[i + (1 << j-1)][j-1]);
	while (m --> 0)
	{
		register int l = read<int>(), r = read<int>();
		int _Max = a[l];
		DREP(i, 30, 0)
			if (l + (1 << i) <= r)
			{
				chkmax(_Max, Max[l][i]);
				l += 1 << i;
			}
		printf("%d\n", _Max);
	}

	return 0;
}
