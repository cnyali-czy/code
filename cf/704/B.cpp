/*
	Problem:	B.cpp
	Time:		2020-10-23 16:55
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
const int maxn = 5000 + 10;
const int inf = 1e15;

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

int n, s, e;
int x[maxn], a[maxn], b[maxn], c[maxn], d[maxn];

int f(int i, int j)
{
	if (i > j) return x[i] - x[j] + c[i] + b[j];
	if (i < j) return x[j] - x[i] + d[i] + a[j];
}
int to[maxn];

signed main()
{
#ifdef CraZYali
	file("B");
#endif
	n = read<int>();s = read<int>();e = read<int>();
	REP(i, 1, n) x[i] = read<int>();
	REP(i, 1, n) a[i] = read<int>();
	REP(i, 1, n) b[i] = read<int>();
	REP(i, 1, n) c[i] = read<int>();
	REP(i, 1, n) d[i] = read<int>();
	to[s] = e;
	int ans = f(s, e);
	REP(i, 1, n) if (i ^ s && i ^ e)
	{
		pair <int, int> pick(inf, 0);
		for (int x = s; x != e; x = to[x])
		{
			pair <int, int> here(f(x, i) + f(i, to[x]) - f(x, to[x]), x);
			pick = min(pick, here);
		}
		ans += pick.first;
		to[i] = to[pick.second];
		to[pick.second] = i;
	}
	cout << ans << endl;
	return 0;
}
