/*
	Problem:	B.cpp
	Time:		2020-10-17 19:30
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
const int maxn = 24;

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

int n;
bool G[maxn][maxn];
bool f[1 << maxn];
int out[1 << maxn];

namespace orzpzk
{
	void work()
	{
		n = read<int>();
		REP(i, 0, (1 << n) - 1) f[i] = 1, out[i] = 0;
		REP(i, 0, n - 1)
		{
			REP(j, 0, n - 1)
			{
				G[i][j] = read<int>();
				if (G[i][j]) out[1 << i] |= (1 << j);
			}
		}

		const int lim = (1 << n) - 1;
		out[0] = lim;
		REP(i, 1, (1 << n) - 1)
		{
			out[i] = out[i & -i] & out[i & (i - 1)];
			out[i] &= (lim ^ i);
		}
		REP(S, 1, (1 << n) - 1) if (f[S])
			for (int T = out[S], x = T; x; x = (x - 1) & T)
				f[S | x] = 0;
		int ans = 1;
		REP(i, 1, lim) ans += f[i];
		printf("%d\n", ans);
	}
}


int main()
{
#ifdef CraZYali
	file("B");
#endif
	register int T = read<int>();
	while (T--) orzpzk :: work();
	return 0;
}
