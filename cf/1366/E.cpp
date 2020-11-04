/*
	Problem:	E.cpp
	Time:		2020-10-31 22:00
	Author:		CraZYali
	E-Mail:		yms-chenziyang@outlook.com 
*/

#define REP(i, s, e) for (register int i(s), end_##i(e); i <= end_##i; i++)
#define DEP(i, s, e) for (register int i(s), end_##i(e); i >= end_##i; i--)
#define DEBUG fprintf(stderr, "Passing [%s] in Line %d\n", __FUNCTION__, __LINE__)

#define chkmax(a, b) (a < (b) ? a = (b) : a)
#define chkmin(a, b) (a > (b) ? a = (b) : a)

#include <algorithm>
#include <iostream>
#include <cstdio>
#define int long long

using namespace std;
const int maxn = 2e5 + 10, MOD = 998244353;

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

int cnt, p[60], n, m, a[maxn], bin[maxn];
void ins(int x)
{
	DEP(i, m, 0) if (x >> i & 1)
		if (!p[i]) {p[i] = x;cnt++;break;}
		else x ^= p[i];
}
int ans[60];

signed main()
{
#ifdef CraZYali
	file("E");
#endif
	n = read<int>();m = read<int>();
	REP(i, 1, n) ins(a[i] = read<int>());
	bin[0] = 1;
	REP(i, 1, n) bin[i] = 2 * bin[i - 1] % MOD;
	for (int lim = (1ll << m + 1) - 1, s = lim; ; s = (s - 1) & lim)
	{
		unsigned int qaq = 0;
		REP(i, 0, m) if (s >> i & 1)
			if (p[i]) qaq ^= p[i];
			else goto gg;
		ans[__builtin_popcountll(qaq)]++;
gg:;
		if (!s) break;
	}
	int lbh = bin[n - cnt];
	REP(i, 0, m) printf("%lld%c", ans[i] * lbh % MOD, i == end_i ? '\n' : ' ');
	return 0;
}
