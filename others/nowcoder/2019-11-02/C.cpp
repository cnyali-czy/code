/*
 * File Name:	C.cpp
 * Author	:	CraZYali
 * Year		:	2019.11.02 20:23
 * Email	:	yms-chenziyang@outlook.com
 */

#define DREP(i, s, e) for (register int i(s), end_##i(e); i >= end_##i; i--)
#define  REP(i, s, e) for (register int i(s), end_##i(e); i <= end_##i; i++)
#define DEBUG fprintf(stderr, "Passing [%s] in Line %d\n", __FUNCTION__, __LINE__)

#define chkmax(a, b) (a < (b) ? a = (b) : a) 
#define chkmin(a, b) (a > (b) ? a = (b) : a) 

#include <iostream>
#include <cstdio>
#include <vector>

using namespace std;
const int maxn = 2000 + 10, MOD = 1e9 + 7;

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

int n, m, a[maxn];
vector <int> G[maxn];

inline void add(int x, int y)
{
	G[x].emplace_back(y);
	G[y].emplace_back(x);
}

int tms[maxn][maxn], ans;

int main()
{
#ifdef CraZYali
	file("C");
#endif
	cin >> n >> m;
	REP(i, 1, n) a[i] = read<int>();
	while (m--) add(read<int>(), read<int>());
	REP(i, 1, n)
		REP(u, 0, (int)G[i].size() - 1)
		REP(v, u + 1, (int)G[i].size() - 1)
		{
			int x(min(G[i][u], G[i][v]));
			int y(max(G[i][u], G[i][v]));
			tms[x][y]++;
		}
	const int inv2 = (MOD + 1) / 2;
	REP(i, 1, n)
		REP(j, i + 1, n)
			(ans += 1ll * tms[i][j] * (tms[i][j] - 1) % MOD * inv2 % MOD * (a[i] + a[j]) % MOD) %= MOD;
	cout << (MOD + ans) % MOD << endl;
	return 0;
}
