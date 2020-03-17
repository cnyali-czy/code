/*
	Problem:	A.cpp
	Time:		2020-03-17 11:17
	Author:		CraZYali
	E-Mail:		yms-chenziyang@outlook.com 
*/

#define REP(i, s, e) for (register int i(s), end_##i(e); i <= end_##i; i++)
#define DEP(i, s, e) for (register int i(s), end_##i(e); i >= end_##i; i--)
#define DEBUG fprintf(stderr, "Passing [%s] in Line %d\n", __FUNCTION__, __LINE__)

#define chkmax(a, b) (a < (b) ? a = (b) : a)
#define chkmin(a, b) (a > (b) ? a = (b) : a)

#include <cstring>
#include <iostream>
#include <cstdio>

using namespace std;
const int maxn = 20 + 5, maxT = 10000 + 10, inf = 1e8;

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

int n, T, A[maxn][maxT], G[maxn][maxn][maxT], g[maxn][maxn][maxT];

int dp[1 << 20][maxn], ans[1 << 20];

namespace run
{
	void Read(int a[])
	{
		int Min = inf;
		REP(i, 0, T - 1)
		{
			a[i] = read<int>();
			chkmin(Min, a[i] + i + T);
		}
		DEP(i, T - 1, 0)
		{
			chkmin(Min, a[i] + i);
			a[i] = Min - i;
		}
	}

	int main()
	{
		n = read<int>();T = read<int>();
		REP(i, 1, n) Read(A[i]);
		REP(i, 1, n) REP(j, i + 1, n)
		{
			Read(G[i][j]);
			REP(k, 0, T - 1) G[j][i][k] = G[i][j][k];
		}
		REP(S, 0, (1 << n) - 1) REP(i, 0, n) dp[S][i] = inf;
		REP(i, 1, n) dp[1 << i - 1][i] = 0;
		REP(S, 0, (1 << n) - 1) REP(i, 1, n) if (dp[S][i] < inf)
		{
			register int u = dp[S][i] + A[i][dp[S][i] % T], v = u % T;
			REP(j, 1, n) if (!(S & (1 << j - 1)))
				chkmin(dp[S | (1 << j - 1)][j], u + G[i][j][v]);
		}
		register int q = read<int>();
		while (q--)
		{
			int S = read<int>(), ans = inf;
			REP(i, 1, n) chkmin(ans, dp[S][i] + A[i][dp[S][i] % T]);
			cout << ans << '\n';
		}
		return 0;
	}
}

int main()
{
#ifdef CraZYali
	file("A");
#endif
	return run::main();
	n = read<int>(); T = read<int>();
	REP(i, 1, n) REP(j, 0, T - 1) A[i][j] = read<int>();
	REP(i, 1, n) REP(j, 1, n) REP(k, 0, T - 1) g[i][j][k] = inf;
	REP(u, 1, n) REP(v, u + 1, n) REP(i, 0, T - 1) g[v][u][i] = g[u][v][i] = read<int>();
	REP(i, 1, n) REP(j, 0, T - 1) g[i][i][j] = 0;

	/*
	   REP(k, 1, n)
	   {
	   REP(i, 1, n) REP(j, 1, n) REP(t, 0, T - 1) REP(t2, 0, T - 1)
	   chkmin(G[i][j][t], G[i][k][t] + t2 + G[k][j][(t2 + t + G[i][k][t]) % T]);
	   REP(i, 1, n) REP(j, 1, n)
	   {
	   REP(Case, 1, T)
	   REP(t, 0, T - 1)
	   chkmin(G[i][j][t], 1 + G[i][j][t == end_t ? 0 : t + 1]);
	   REP(t, 0, T - 1)
	   chkmin(G[i][j][t], 1 + G[i][j][t == end_t ? 0 : t + 1]);
	   }
	   }
	//	REP(i, 1, n) REP(j, 1, n) REP(t, 0, T - 1) printf("G[%d][%d][%d] = %d\n",i,j,t,G[i][j][t]);
	REP(i, 0, (1 << n) - 1)
	{
	ans[i] = inf;
	REP(j, 1, n) dp[i][j] = inf;
	}
	REP(i, 1, n) REP(t, 0, T - 1) chkmin(dp[1 << i - 1][i], A[i][t] + t);
	REP(S, 1, (1 << n) - 1)
	{
	REP(i, 1, n) if (S & (1 << i - 1))
	REP(j, 1, n) if (!(S & (1 << j - 1)))
	{
	int nxtS = S | (1 << j - 1);
	REP(k1, 0, T - 1)
	{
	int gotime = dp[S][i] + k1 + G[i][j][(dp[S][i] + k1) % T];
	REP(k2, 0, T - 1)
	{
	int nxttime = gotime + k2 + A[j][(gotime + k2) % T];
	chkmin(dp[nxtS][j], nxttime);
	}
	}
	}
	}
	REP(i, 0, (1 << n) - 1)
	REP(j, 1, n) chkmin(ans[i], dp[i][j]);
	*/
	register int Q = read<int>();
	while (Q--)
	{
		int S = read<int>();
		REP(i, 1, n)
		{
			REP(k, 0, (1 << n) - 1) dp[k][i] = inf;
			REP(j, 1, n)
				if (!(S & (1 << i - 1)) || !(S & (1 << j - 1)))
					REP(t, 0, T - 1) G[i][j][t] = inf;
				else 
					REP(t, 0, T - 1) G[i][j][t] = g[i][j][t];
		}
		REP(k, 1, n) if (S & (1 << k - 1))
		{
			REP(i, 1, n) if (S & (1 << i - 1)) REP(j, 1, n) if (S & (1 << j - 1)) REP(t, 0, T - 1) REP(t2, 0, T - 1)
				chkmin(G[i][j][t], G[i][k][t] + t2 + G[k][j][(t + t2 + G[i][k][t]) % T]);
			/*
			   REP(i, 1, n) REP(j, 1, n)
			   {
			   REP(Case, 1, T)
			   REP(t, 0, T - 1)
			   chkmin(G[i][j][t], 1 + G[i][j][t == end_t ? 0 : t + 1]);
			   REP(t, 0, T - 1)
			   chkmin(G[i][j][t], 1 + G[i][j][t == end_t ? 0 : t + 1]);
			   }
			   */
		}
		REP(i, 1, n) if (S & (1 << i - 1))
			REP(t, 0, T - 1) chkmin(dp[1 << i - 1][i], t + A[i][t]);
		REP(s, 1, (1 << n) - 1) if ((s & S) == s)
		{
			REP(i, 1, n) if (s & (1 << i - 1))
				REP(j, 1, n) if (!(s & (1 << j - 1)) && (S & (1 << j - 1)))
				{
					int nxtS = s | (1 << j - 1);
					REP(k1, 0, T - 1)
					{
						int gotime = dp[s][i] + k1 + G[i][j][(dp[s][i] + k1) % T];
						REP(k2, 0, T - 1)
						{
							int nxttime = gotime + k2 + A[j][(gotime + k2) % T];
							chkmin(dp[nxtS][j], nxttime);
						}
					}
				}
		}
		int ans = inf;
		REP(i, 1, n) chkmin(ans, dp[S][i]);
		cout << ans << '\n';
	}
	return 0;
}
