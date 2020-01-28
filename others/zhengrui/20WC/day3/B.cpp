/*
 * File Name:	B.cpp
 * Author	:	CraZYali
 * Time		:	2020.01.27 20:11
 * Email	:	yms-chenziyang@outlook.com
 */

#define DEP(i, s, e) for (register int i(s), end_##i(e); i >= end_##i; i--)
#define REP(i, s, e) for (register int i(s), end_##i(e); i <= end_##i; i++)
#define DEBUG fprintf(stderr, "Passing [%s] in Line %d\n", __FUNCTION__, __LINE__)

#define chkmax(a, b) (a < (b) ? a = (b) : a) 
#define chkmin(a, b) (a > (b) ? a = (b) : a)

#include <vector>
#include <iostream>
#include <cstdio>
#include <bitset>

using namespace std;

template <typename T> inline T read()
{
	T ans(0), flag(1);
	char c(getchar());
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

#define file(FILE_NAME) freopen(FILE_NAME".in", "r", stdin), freopen(FILE_NAME".out", "w", stdout);
namespace run
{
	const int maxn = 1500 + 10;

	bitset <maxn> G[15][maxn], A[maxn];
	int n, m, lg[maxn], ans[maxn];
	struct __init__
	{
		__init__()
		{
			REP(i, 2, 1500) lg[i] = lg[i >> 1] + 1;
		}
	}__INIT__;

	inline bitset <maxn> get(int l, int r)
	{
		int k = lg[r - l + 1];
		return G[k][l] & G[k][r - (1 << k) + 1];
	}
	char s[maxn];

	vector <pair <int, int> > used[maxn], q[maxn];

	int main()
	{
		n = read<int>();
		m = read<int>();
		REP(i, 1, n)
		{
			scanf("%s", s + 1);
			REP(j, 1, n)
				if (s[j] == '1') A[i].set(j);
			G[0][i] = A[i];
		}
		DEP(i, n, 1)
			for (int j = 1; i + (1 << j) - 1 <= n; j++)
			G[j][i] = G[j-1][i] & G[j-1][i + (1 << j - 1)];
		REP(i, 1, n)
		{
			int cnt = 0;
			DEP(j, n, 1)
			if (A[i][j]) used[++cnt].emplace_back(i, j);
			else cnt = 0;
		}
		REP(i, 1, m)
		{
			int r(read<int>()), c(read<int>());
			q[c].emplace_back(r, i);
		}
		REP(i, 1, n)
		{
			REP(j, 1, n)
				for (auto t : q[i])
				{
					if (j + t.first - 1 > n) continue;
					auto tmp = get(j, j + t.first - 1);
					ans[t.second] += (tmp & (tmp >> i - 1) & A[j] & A[j + t.first - 1]).count();
				}
			for (auto p : used[i]) A[p.first][p.second] = 0;
		}
		REP(i, 1, m) printf("%d\n", ans[i]);
		return 0;
	}
}

int main()
{
#ifdef CraZYali
	file("B");
#endif
	return run::main();
}
