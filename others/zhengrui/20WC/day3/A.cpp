/*
	Problem:	A.cpp
	Time:		2020-02-24 12:04
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
#define i64 long long
using namespace std;

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

namespace run
{
	const int MOD = 998244353, inv2 = MOD + 1 >> 1;

	inline int add(int x, int y) {register int res = x + y;return res >= MOD ? res - MOD : res;}
	inline int sub(int x, int y) {register int res = x - y;return res <    0 ? res + MOD : res;}
	inline i64 mul(i64 x, int y) {register i64 res = x * y;return res >= MOD ? res % MOD : res;}
	inline void inc(int &x, int y) {x += y;if (x >= MOD) x -= MOD;}
	inline void dec(int &x, int y) {x -= y;if (x <    0) x += MOD;}

	int n, m, e[16], lg[1 << 16], cnt[1 << 16], f[1 << 16][2], g[1 << 16][2];

	struct __init__
	{
		__init__()
		{
			REP(i, 1, 15) lg[1 << i] = i;
			REP(i, 1, (1 << 16) - 1) cnt[i] = cnt[i >> 1] + (i & 1);
		}
	}__INIT__;

	int main()
	{
		n = read<int>();
		m = read<int>();
		while (m--)
		{
			int x(read<int>() - 1), y(read<int>() - 1);
			e[x] |= (1 << y);
			e[y] |= (1 << x);
		}
		const int lim = (1 << n) - 1;
		REP(i, 1, lim)
		{
			if (cnt[i] == 1)
			{
				g[i][0] = 1;
				continue;
			}
			int S = i;
			int x = lg[S & -S]; S ^= (1 << x);
			int y = lg[S & -S]; S ^= (1 << y);
			for (int j = S; ; j = (j - 1) & S)
			{
				int k = j | (1 << y), t = cnt[e[x] & k], t2 = mul(inv2, mul(t, t - 1));
				inc(g[i][0], mul(t, mul(g[k][0], g[i ^ k][0])));
				inc(g[i][1], mul(t, mul(g[k][0], g[i ^ k][1])));
				inc(g[i][1], mul(t, mul(g[k][1], g[i ^ k][0])));
				inc(g[i][1], mul(t2, mul(g[k][0], g[i ^ k][0])));
				if (!j) break;
			}
		}
		f[0][0] = 1;
		REP(i, 1, lim)
			for (int j = i; j; j = (j - 1) & i) if (j & (i & -i))
			{
				inc(f[i][0], mul(cnt[j], mul(g[j][0], f[i ^ j][0])));
				inc(f[i][1], mul(cnt[j], mul(g[j][0], f[i ^ j][1])));
				inc(f[i][1], mul(cnt[j], mul(g[j][1], f[i ^ j][0])));
			}
		cout << add(f[lim][0], f[lim][1]) << endl;
		return 0;
	}
}

int main()
{
#ifdef CraZYali
	file("A");
#endif
	return run::main();
}
