/*
	Problem:	B.cpp
	Time:		2020-06-06 22:56
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

using namespace std;
const int maxn = 15 + 5, MOD = 1e9 + 7;

inline void inc(int &x, int y) {x += y; if (x >= MOD) x -= MOD;}

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

int n, m, r[maxn], id[maxn];
int f[16][1 << 15], mem[1 << 15], gg[1 << 15], a[15], p[15];

int main()
{
#ifdef CraZYali
	file("B");
#endif
	n = read<int>();m = read<int>();
	REP(i, 0, n - 1)
	{
		r[i] = read<int>() + 1;
		id[i] = i;
	}
	sort(id, id + n, [](int x, int y) {return r[x] < r[y];});
	REP(i, 0, n - 1) a[i] = r[id[i]], p[id[i]] = i;
	while (m--)
	{
		int x(p[read<int>() - 1]), y(p[read<int>() - 1]);
		REP(i, 0, (1 << n) - 1)
			gg[i] |= i >> x & i >> y & 1;
	}
	REP(i, 1, (1 << n) - 1) mem[i] = __builtin_ctz(i);
	f[0][(1 << n) - 1] = 1;
	REP(i, 0, n - 1) REP(S, 0, (1 << n) - 1) if (f[i][S])
		for (int x = S; x; x = (x - 1) & S) if (!gg[x] && (x >> mem[S] & 1) && a[mem[x]] > i)
			inc(f[i + 1][S ^ x], 1ll * f[i][S] * (a[mem[x]] - i) % MOD);
	int ans = 0;
	REP(i, 1, n) inc(ans, 1ll * i * f[i][0] % MOD);
	cout << ans << endl;
	return 0;
}
