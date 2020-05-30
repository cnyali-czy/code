/*
	Problem:	E.cpp
	Time:		2020-05-26 23:44
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
#define int long long
using namespace std;
const int maxn = 5e5 + 10;

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

int n, a[maxn], x, h, s[maxn], c[maxn];
int Min[maxn][25], LG[maxn];

int query(int l, int r)
{
	int k = LG[r - l + 1];
	return min(Min[l][k], Min[r - (1 << k) + 1][k]);
}

signed main()
{
#ifdef CraZYali
	file("E");
#endif
	n = read<int>();h = (n + 1) / 2;
	REP(i, 1, h) a[i] = read<int>();
	x = read<int>();
	REP(i, h + 1, n) a[i] = x;
	REP(i, 1, n) s[i] = s[i - 1] + a[i];
	REP(i, 1, n) c[i] = s[h] - s[i - 1] + x * (i - h - 1);
	REP(i, 2, n) LG[i] = LG[i >> 1] + 1;
	REP(i, 1, n) Min[i][0] = c[i];
	REP(j, 1, 24)
		REP(i, 1, n - (1 << j) + 1) Min[i][j] = min(Min[i][j - 1], Min[i + (1 << j - 1)][j - 1]);
	REP(k, h, n)
	{
		int ccc = query(1, n - k + 1) + x * k;
		if (ccc > 0)
		{
			cout << k << endl;
			return 0;
		}
	}
	cout << -1;
	return 0;
}
