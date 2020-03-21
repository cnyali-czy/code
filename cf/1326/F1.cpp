/*
	Problem:	F1.cpp
	Time:		2020-03-20 11:35
	Author:		CraZYali
	E-Mail:		yms-chenziyang@outlook.com 
*/

#define REP(i, s, e) for (register int i(s), end_##i(e); i <= end_##i; i++)
#define DEP(i, s, e) for (register int i(s), end_##i(e); i >= end_##i; i--)
#define DEBUG fprintf(stderr, "Passing [%s] in Line %d\n", __FUNCTION__, __LINE__)

#define chkmax(a, b) (a < (b) ? a = (b) : a)
#define chkmin(a, b) (a > (b) ? a = (b) : a)

#include <vector>
#include <iostream>
#include <cstdio>
#define i64 long long
using namespace std;
const int maxn = 20, maxS = (1 << 14) + 5;
template <typename T>
inline T read()
{
	T ans = 0, flag = 1;
	char c = getchar();
	while (!isdigit(c))
	{
		if (c == '-') flag = -1;
		c = getchar();
	}
	while (isdigit(c))
	{
		ans = ans * 10 + c - 48;
		c = getchar();
	}
	return ans * flag;
}

#define file(FILE_NAME) freopen(FILE_NAME".in", "r", stdin), freopen(FILE_NAME".out", "w", stdout)

int n;
vector<int> f[maxS][maxn];
char s[114];
int a[maxn][maxn], siz[maxS];

signed main()
{
#ifdef CraZYali
	file("F1");
#endif
	n = read<int>();
	REP(i, 0, n - 1)
		REP(j, 0, n - 1) scanf("%1d", a[i] + j);
	REP(i, 0, (1 << n) - 1)
	{
		siz[i] = siz[i >> 1] + (i & 1);
		REP(j, 0, n - 1) if (i >> j & 1)
			f[i][j].resize(1 << siz[i] - 1);
	}
	REP(i, 1, (1 << n) - 1)
	{
		if (siz[i] == 1) REP(j, 0, n - 1) if (i >> j & 1) f[i][j][0] = 1;
		REP(j, 0, n - 1) if(i >> j & 1)
			REP(l, 0, n - 1) if (!(i >> l & 1))
			REP(k, 0, (1 << siz[i] - 1) - 1) f[i | (1 << l)][l][k | (a[j][l] << siz[i] - 1)] += f[i][j][k];
	}
	REP(j, 0, (1 << n - 1) - 1)
	{
		i64 ans = 0;
		REP(i, 0, n - 1) ans += f[(1 << n) - 1][i][j];
		cout << ans << ' ';
	}
	return 0;
}
