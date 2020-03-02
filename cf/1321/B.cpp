/*
	Problem:	B.cpp
	Time:		2020-03-01 21:27
	Author:		CraZYali
	E-Mail:		yms-chenziyang@outlook.com 
*/

#define REP(i, s, e) for (register int i(s), end_##i(e); i <= end_##i; i++)
#define DEP(i, s, e) for (register int i(s), end_##i(e); i >= end_##i; i--)
#define DEBUG fprintf(stderr, "Passing [%s] in Line %d\n", __FUNCTION__, __LINE__)

#define chkmax(a, b) (a < (b) ? a = (b) : a)
#define chkmin(a, b) (a > (b) ? a = (b) : a)

#include <unordered_map>
#include <iostream>
#include <cstdio>
#define int long long
using namespace std;
const int maxn = 2e5 + 10, inf = 1e18;

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

int n, b[maxn], f[maxn];
unordered_map <int, int> Max;

signed main()
{
#ifdef CraZYali
	file("B");
#endif
	n = read<int>();
	REP(i, 1, n)
	{
		b[i] = read<int>();
		Max[b[i] - i] = -inf;
	}
	f[1] = b[1];
	Max[b[1] - 1] = b[1];
	REP(i, 2, n)
	{
		f[i] = b[i];
		int good = Max[b[i] - i];
		if (good > -inf) f[i] += good;
		Max[b[i] - i] = f[i];
	}
	int ans = f[1];
	REP(i, 2, n) chkmax(ans, f[i]);
	cout << ans << endl;
	return 0;
}
