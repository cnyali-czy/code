/*
	Problem:	5309.cpp
	Time:		2021-04-30 09:14
	Author:		CraZYali
	E-Mail:		yms-chenziyang@outlook.com 
*/

#define REP(i, s, e) for (register int i(s), end_##i(e); i <= end_##i; i++)
#define DEP(i, s, e) for (register int i(s), end_##i(e); i >= end_##i; i--)
#define DEBUG fprintf(stderr, "Passing [%s] in Line %d\n", __FUNCTION__, __LINE__)

#define chkmax(a, b) (a < (b) ? a = (b) : a)
#define chkmin(a, b) (a > (b) ? a = (b) : a)

#include <cmath>
#include <iostream>
#include <cstdio>
#define i64 long long
#define u64 unsigned i64

using namespace std;
const int maxn = 2e5 + 10, MOD = 1e9 + 7;

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

int n, m;

inline void reduce(int &x) {x += x >> 31 & MOD;}

namespace SUM
{
	int blg[maxn], L[maxn], s1[maxn], s2[maxn];
	void init()
	{
		const int B = sqrt(n);
		REP(i, 1, n) blg[i] = (i - 1) / B + 1;
		DEP(i, n, 1) L[blg[i]] = i;
	}
	inline void add(int x, int y)
	{
		reduce(s1[x] += y - MOD);
		reduce(s2[blg[x]] += y - MOD);
	}
	inline int query(int x)
	{
		if (!x) return 0;
		i64 res = 0;
		REP(i, 1, blg[x] - 1)	res += s2[i];
		REP(i, L[blg[x]], x)	res += s1[i];
		return res % MOD;
	}
}
int s[450][450], fklty[maxn], all;
inline int sum(int x, int y, const int B)
{
	i64 res = SUM :: query(y) + MOD - SUM :: query(x);
	if (y <= B)
	{
		REP(i, x + 1, y) res += fklty[i];
		return res % MOD;
	}
	if (x <= B)
	{
		REP(i, 1, x) res += MOD - fklty[i];
		REP(k, 1, B) REP(b, 1, k) if (s[k][b])
			(res += 1ll * (y - b) / k * s[k][b]) %= MOD;
		res += all;
	}
	else
	{
		REP(k, 1, B) REP(b, 1, k) if (s[k][b])
			(res += 1ll * ((y - b) / k - (x - b) / k + MOD) * s[k][b]) %= MOD;
	}
	return res % MOD;
}

int main()
{
#ifdef CraZYali
	file("5309");
#endif
	n = read<int>();m = read<int>();
	SUM :: init();
	REP(i, 1, n) SUM :: add(i, read<int>());
	const int B = max(5., pow(n, 1. / 3));//sqrt(n);
	while (m--)
	{
		int opt = read<int>();
		if (opt == 2)
		{
			int l = read<int>(), r = read<int>();
			printf("%d\n", sum(l - 1, r, B));
		}
		else
		{
			int x = read<int>(), y = read<int>(), z = read<int>();
			if (x >= B)
				for (int i = y; i <= n; i += x) SUM :: add(i, z);
			else
			{
				z -= MOD;
				reduce(s[x][y] += z);
				reduce(all += z);
				for (int i = y; i <= B; i += x) reduce(fklty[i] += z);
			}
		}
	}
	return 0;
}
