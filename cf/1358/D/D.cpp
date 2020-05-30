/*
	Problem:	D.cpp
	Time:		2020-05-26 23:20
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
#define int long long
const int maxn = 2e5 + 10;

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

int n, x, d[maxn << 1], s[maxn << 1], s2[maxn << 1];
int sum(int l, int r) {return (l + r) * (r - l + 1) / 2;}
signed main()
{
#ifdef CraZYali
	file("D");
#endif
	n = read<int>();x = read<int>();
	REP(i, 1, n) d[i] = read<int>(), d[i + n] = d[i];
	REP(i, 1, n + n) s[i] = s[i - 1] + d[i], s2[i] = s2[i - 1] + d[i] * (d[i] + 1) / 2;
	int ans = 0;
	REP(i, n + 1, n + n)
	{
		int l = 1, r = i, gd = i;
		while (l <= r)
		{
			int mid = l + r >> 1;
			if (s[i] - s[mid] <= x) gd = mid, r = mid - 1;
			else l = mid + 1;
		}
		int tx = x - (s[i] - s[gd]);
		int res = s2[i] - s2[gd];
		if (tx) res += sum(d[gd] - tx + 1, d[gd]);
		chkmax(ans, res);
	}
	cout << ans << endl;
	return 0;
}
