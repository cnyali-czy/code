/*
	Problem:	A.cpp
	Time:		2020-08-08 21:32
	Author:		CraZYali
	E-Mail:		yms-chenziyang@outlook.com 
*/
#pragma GCC optimize(3)
#define REP(i, s, e) for (register int i(s), end_##i(e); i <= end_##i; i++)
#define DEP(i, s, e) for (register int i(s), end_##i(e); i >= end_##i; i--)
#define DEBUG fprintf(stderr, "Passing [%s] in Line %d\n", __FUNCTION__, __LINE__)

#define chkmax(a, b) (a < (b) ? a = (b) : a)
#define chkmin(a, b) (a > (b) ? a = (b) : a)

#include <ctime>
#include <algorithm>
#include <queue>
#include <iostream>
#include <cstdio>
#include <set>
#include <map>

#define i64 long long
using namespace std;
const int maxn = 1e5 + 10, MOD = 998244353;

namespace fastpow
{
	const int w = 32000;
	int pre1[w + 5], pre2[w + 5];
	i64 power_pow(int b) {return 1ll * pre1[b % w] * pre2[b / w] % MOD;}
}
using fastpow :: pre1;
using fastpow :: pre2;
using fastpow :: power_pow;

int bg[maxn], ne[maxn], to[maxn], e;

i64 w[maxn];

inline void add(int x, int y, i64 z)
{
	e++;
	to[e] = y;
	ne[e] = bg[x];
	bg[x] = e;
	w[e] = z;
}

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

int n, fa[maxn];

set <i64> dp[maxn], Max[maxn];
map <i64, int> need;

void merge(set <i64> &x, set <i64> &y)
{
	if (!y.size()) return;
	if (x.size() < y.size()) swap(x, y);
	need.clear();
	for (auto i : y) need[i]++;
	while (need.size())
	{
		auto it = need.begin();
		if (it -> second > 1) need[it -> first + 1]++;
		else if (x.find(it -> first) == x.end()) x.emplace(it -> first);
		else
		{
			x.erase(it -> first);
			need[it -> first + 1]++;
		}
		need.erase(it);
	}
}
i64 vx[maxn], vy[maxn];
int n1, n2;
inline bool operator < (set <i64> &x, set <i64> &y)
{
	if (!y.size()) return 0;
	if (!x.size()) return 1;
	if (x == y) return 0;
	int Min = min(x.size(), y.size()), cnt;
	auto it = x.begin();
	for (cnt = 0, it = --x.end(); cnt < Min; cnt++, it--) vx[cnt] = *it;
	for (cnt = 0, it = --y.end(); cnt < Min; cnt++, it--)
	{
		int yyy = *it;
		if (vx[cnt] < yyy) return 1;
		if (vx[cnt] > yyy) return 0;
	}
	return x.size() == Min;
}

void dfs(int x)
{
	static int dfn = 0;
	++dfn;
	if (dfn % 1000 == 0) fprintf(stderr, "Done %d / %d = %.2lf\n", dfn, n, dfn * 1. / n);
	for (int i = bg[x]; i; i = ne[i])
	{
		dfs(to[i]);
		set <i64> qaq;qaq.emplace(w[i]);
		merge(dp[to[i]], qaq);
		if (Max[x] < dp[to[i]]) Max[x] = dp[to[i]];
		merge(dp[x], dp[to[i]]);
	}
	merge(dp[x], Max[x]);
}

int main()
{
#ifdef CraZYali
	file("A");
#endif
	pre1[0] = 1;
	REP(i, 1, fastpow :: w) pre1[i] = 2ll * pre1[i - 1] % MOD;
	pre2[0] = 1;
	REP(i, 1, fastpow :: w) pre2[i] = 1ll * pre2[i - 1] * pre1[fastpow :: w] % MOD;
	n = read<int>();
	REP(i, 2, n)
	{
		fa[i] = read<int>();
		add(fa[i], i, read<i64>());
	}
	dfs(1);
	i64 ans = 0;
	for (auto i : dp[1]) ans += power_pow(i % (MOD - 1));
	cout << ans % MOD << endl;
	cerr << clock() * 1. / CLOCKS_PER_SEC << endl;
	return 0;
}
