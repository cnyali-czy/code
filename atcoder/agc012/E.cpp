/*
	Problem:	E.cpp
	Time:		2021-06-01 21:08
	Author:		CraZYali
	E-Mail:		yms-chenziyang@outlook.com 
*/

#define REP(i, s, e) for (register int i(s), end_##i(e); i <= end_##i; i++)
#define DEP(i, s, e) for (register int i(s), end_##i(e); i >= end_##i; i--)
#define DEBUG fprintf(stderr, "Passing [%s] in Line %d\n", __FUNCTION__, __LINE__)

#define chkmax(a, b) (a < (b) ? a = (b) : a)
#define chkmin(a, b) (a > (b) ? a = (b) : a)

#include <algorithm>
#include <vector>
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

int n, v, a[maxn];

int L[21][1 << 20], R[21][1 << 20], m, k, frL[1 << 20], frR[1 << 20];
bool ans[maxn];
void output()
{
	REP(i, 1, n) puts(ans[i] ? "Possible" : "Impossible");
	exit(0);
}
#define fi first
#define se second

signed main()
{
#ifdef CraZYali
	file("E");
#endif
	n = read<int>();v = read<int>();
	a[0] = -inf;a[n + 1] = inf;
	REP(i, 1, n) a[i] = read<int>();
	for (int x = v; ; x >>= 1, m++)
	{
		R[m][n + 1] = n + 1;
		REP(i, 1, n) L[m][i] = (a[i] - a[i - 1] <= x ? L[m][i - 1] : i);
		DEP(i, n, 1) R[m][i] = (a[i + 1] - a[i] <= x ? R[m][i + 1] : i);
		if (!x) {m++;break;}
	}
	vector <pair <int, int> > v;
	REP(i, 1, n) v.emplace_back(L[0][i], R[0][i]);
	v.resize(unique(v.begin(), v.end()) - v.begin());
	if (v.size() > m) output();
	REP(i, 0, (1 << m) - 1) frR[i] = n + 1;
	for (int i = 0; i < (1 << m); i += 2) REP(j, 0, m - 1) if (i >> j & 1)
	{
		frL[i] = max(frL[i], R[j][frL[i ^ (1 << j)] + 1]);
		frR[i] = min(frR[i], L[j][frR[i ^ (1 << j)] - 1]);
	}
	for (auto i : v) for (int s = 0; s < (1 << m); s += 2)
		if (i.fi - 1 <= frL[s] && frR[(1 << m) - 1 - s - 1] <= i.se + 1)
		{
			REP(l, i.fi, i.se) ans[l] = 1;
			break;
		}
	output();
	return 0;
}
