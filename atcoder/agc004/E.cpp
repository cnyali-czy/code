/*
	Problem:	2045.cpp
	Time:		2021-04-28 09:07
	Author:		CraZYali
	E-Mail:		yms-chenziyang@outlook.com 
*/

#define REP(i, s, e) for (register int i(s), end_##i(e); i <= end_##i; i++)
#define DEP(i, s, e) for (register int i(s), end_##i(e); i >= end_##i; i--)
#define DEBUG fprintf(stderr, "Passing [%s] in Line %d\n", __FUNCTION__, __LINE__)

#define chkmax(a, b) (a < (b) ? a = (b) : a)
#define chkmin(a, b) (a > (b) ? a = (b) : a)

#include <iostream>
#include <cstdio>

using namespace std;
const int maxn = 100 + 5;

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
		ans = ans * 10 + (c - 48);
		c = getchar();
	}
	return ans * flag;
}

#define file(FILE_NAME) freopen(FILE_NAME".in", "r", stdin), freopen(FILE_NAME".out", "w", stdout)

int n, m, sx, sy;
short v[2][maxn][maxn];
short f[maxn][maxn][maxn][maxn];

int main()
{
#ifdef CraZYali
	file("2045");
#endif
	n = read<int>();m = read<int>();
	REP(i, 1, n) REP(j, 1, m)
	{
		char c = getchar();
		while (c ^ 'E' && c ^ 'o' && c ^ '.') c = getchar();
		if (c == 'E') sx = i, sy = j;
		else
		{
			v[0][i][j] = v[0][i - 1][j] + (c == 'o');
			v[1][i][j] = v[1][i][j - 1] + (c == 'o');
		}
	}
	short ans = 0;
	REP(l, 0, sy - 1)
		REP(r, 0, m - sy)
		REP(u, 0, sx - 1)
		REP(d, 0, n - sx)
		{
			ans = max(ans, f[l][r][u][d]);
			if(l + r < sy - 1) f[l + 1][r][u][d] = max((int)f[l + 1][r][u][d] , (int)f[l][r][u][d] + v[0][min(sx + d , n - u)][sy - l - 1] - v[0][max(sx - u - 1 , d)][sy - l - 1]);
			if(l + r < m - sy) f[l][r + 1][u][d] = max((int)f[l][r + 1][u][d] , (int)f[l][r][u][d] + v[0][min(sx + d , n - u)][sy + r + 1] - v[0][max(sx - u - 1 , d)][sy + r + 1]);
			if(u + d < sx - 1) f[l][r][u + 1][d] = max((int)f[l][r][u + 1][d] , (int)f[l][r][u][d] + v[1][sx - u - 1][min(sy + r , m - l)] - v[1][sx - u - 1][max(sy - l - 1 , r)]);
			if(u + d < n - sx) f[l][r][u][d + 1] = max((int)f[l][r][u][d + 1] , (int)f[l][r][u][d] + v[1][sx + d + 1][min(sy + r , m - l)] - v[1][sx + d + 1][max(sy - l - 1 , r)]);
		}
	cout << ans << endl;
	return 0;
}
