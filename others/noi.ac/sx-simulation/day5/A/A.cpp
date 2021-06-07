/*
	Problem:	A.cpp
	Time:		2021-06-07 08:31
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
#include <cassert>
#include <iostream>
#include <cstdio>
#define i64 long long

using namespace std;
const int maxn = 1e5 + 10, maxm = 15, maxs = 14348907, MOD = 998244353;
inline void reduce(int &x) {x += x >> 31 & MOD;}

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

int n, m, bin3[maxm + 5], bin2[maxn];

int h[maxs], cnt[1 << maxm], g[1 << maxm];
inline int at(int sta, int x) {return sta / bin3[x] % 3;}
inline int md(int sta, int x, int y) {return sta + bin3[x] * (y - at(sta, x));}

int main()
{
#ifdef CraZYali
	file("A");
#endif
	cin >> n >> m;
	bin3[0] = 1;REP(i, 1, m) bin3[i] = bin3[i - 1] * 3;
	bin2[0] = 1;REP(i, 1, n) bin2[i] = bin2[i - 1] * 2 % MOD;
	REP(i, 1, n)
	{
		static char s[maxm];
		scanf("%s", s);
		int sta = 0;
		REP(j, 0, m - 1) sta = md(sta, j, s[j] == '1');
		h[sta]++;
	}
	static int fir[maxs], no2[maxs];
	REP(i, 0, bin3[m] - 1) fir[i] = m + 1;
	no2[0] = (1 << m) - 1;
	REP(i, 1, bin3[m] - 1)
	{
		fir[i] = (i % 3 == 2 ? 0 : fir[i / 3] + 1);
		no2[i] = ((no2[i / 3] << 1) | (i % 3 != 2)) & ((1 << m) - 1);
	}

	REP(sta, 0, bin3[m] - 1) if (no2[sta] != no2[0])
		reduce(h[sta] = h[md(sta, fir[sta], 0)] + h[md(sta, fir[sta], 1)] - MOD);
	REP(sta, 0, bin3[m] - 1)
	{
		int r = no2[sta];
		reduce(g[r] += bin2[h[sta]] - 1 - MOD);
	}
	REP(sta, 0, (1 << m) - 1) reduce(g[sta] += 1 - MOD);
	
	int ans = 0;
	/*
	REP(sta, 1, (1 << m) - 1)
	{
		cnt[sta] = cnt[sta >> 1] + (sta & 1);
		i64 res = 0;
		for (int x = sta; ; x = (x - 1) & sta)
		{
			res += (cnt[x] & 1 ? -1 : 1) * g[x];
			if (!x) break;
		}
		res = (res % MOD + MOD) % MOD;
		ans ^= res;
	}*/
	REP(sta, 0, (1 << m) - 1)
	{
		cnt[sta] = cnt[sta >> 1] + (sta & 1);
		if (cnt[sta] & 1) reduce(g[sta] = -g[sta]);
	}
	REP(i, 0, m - 1)
		REP(sta, 0, (1 << m) - 1) if (sta >> i & 1)
		reduce(g[sta] += g[sta ^ (1 << i)] - MOD);
	REP(i, 1, (1 << m) - 1) ans ^= g[i];
	cout << ans << endl;
	return 0;
}
