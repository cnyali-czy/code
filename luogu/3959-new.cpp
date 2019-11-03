/*
 * File Name:	3959-new.cpp
 * Author	:	CraZYali
 * Year		:	2019.10.30 20:51
 * Email	:	yms-chenziyang@outlook.com
 */

#define DREP(i, s, e) for (register int i(s), end_##i(e); i >= end_##i; i--)
#define  REP(i, s, e) for (register int i(s), end_##i(e); i <= end_##i; i++)
#define DEBUG fprintf(stderr, "Passing [%s] in Line %d\n", __FUNCTION__, __LINE__)

#define chkmax(a, b) (a < (b) ? a = (b) : a) 
#define chkmin(a, b) (a > (b) ? a = (b) : a) 

#include <iostream>
#include <cstring>
#include <cstdio>
#include <vector>

using namespace std;
const int maxn = 12;

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

vector <pair <int, int> > v[1 << maxn];
int n, m, w[maxn][maxn];
int ans, inf, LG[1 << maxn], dp[maxn][1 << maxn];

int main()
{
#ifdef CraZYali
	file("3959-new");
#endif
	memset(w, 0x3f, sizeof w);
	ans = inf = w[0][0];
	cin >> n >> m;
	REP(i, 1, n - 1) LG[1 << i] = i;
	while (m--)
	{
		int x(read<int>() - 1), y(read<int>() - 1), z(read<int>());
		chkmin(w[x][y], z);
		chkmin(w[y][x], z);
	}
	REP(i, 0, n - 1) w[i][i] = 0;
	const int lim = (1 << n) - 1;
	REP(S, 1, lim)
		for (int x = (lim ^ S); x; x = (x - 1) & (lim ^ S))
		{
			int ssr = S | x;
			int cost(0);
			bool flag(1);
			for (int tmp2 = x, v = LG[tmp2 & -tmp2]; tmp2; tmp2 -= tmp2 & -tmp2, v = LG[tmp2 & -tmp2])
			{
				int tmpcost(inf);
				for (int tmp1 = S, u = LG[tmp1 & -tmp1]; tmp1; tmp1 -= tmp1 & -tmp1, u = LG[tmp1 & -tmp1])
					chkmin(tmpcost, w[u][v]);
				if (tmpcost >= inf)
				{
					flag = 0;
					break;
				}
				cost += tmpcost;
			}
			if (!flag) continue;
			v[S].push_back(make_pair(ssr, cost));
		}
	memset(dp, 0x3f, sizeof dp);
	REP(i, 0, n - 1) dp[0][1 << i] = 0;
	REP(i, 0, n - 2)
		REP(S, 1, lim) if (dp[i][S] < inf)
		REP(j, 0, (int)v[S].size() - 1)
		{
			int ssr = v[S][j].first, cost = v[S][j].second;
			chkmin(dp[i+1][ssr], dp[i][S] + cost * (i + 1));
		}
	REP(i, 0, n - 1)
		chkmin(ans, dp[i][lim]);
	cout << ans << endl;
	return 0;
}
