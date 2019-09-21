/*
 * File Name:	5E02.cpp
 * Author	:	CraZYali
 * Year		:	2019.09.20 23:21
 * Email	:	yms-chenziyang@outlook.com
 */

#define DREP(i, s, e) for (register int i(s), end_##i(e); i >= end_##i; i--)
#define  REP(i, s, e) for (register int i(s), end_##i(e); i <= end_##i; i++)
#define DEBUG fprintf(stderr, "Passing [%s] in Line %d\n", __FUNCTION__, __LINE__)

#define chkmax(a, b) a = max(a, (b))
#define chkmin(a, b) a = min(a, (b))

#include <iostream>
#include <cstdio>

using namespace std;
const int maxn = 100 + 10, maxm = 100 + 10, inf = 1e7;//((1 << 30) - 1 << 1) + 1;

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

int m, n;
int a[maxn][maxm], dp[maxn][maxm];
pair <int, int> frm[maxn][maxm];

int patha[maxm], pathb[maxm];

inline void getpath(int a[], int qaq, pair <int, int> now)
{
	int cur = m;
	a[cur] = qaq;
	while (--cur)
	{
		a[cur] = now.first;
		now = frm[now.first][now.second];
	}
}

inline bool better(int New, int Old)
{
	getpath(patha, New, frm[New][m]);
	getpath(pathb, Old, frm[Old][m]);
	REP(i, 1, m)
		if (patha[i] < pathb[i]) return 1;
		else if (patha[i] > pathb[i]) return 0;
	return 1;
}

int main()
{
#ifdef CraZYali
	file("5E02");
#endif
	cin >> m >> n;
	REP(i, 1, m)
		REP(j, 1, n) a[j][i] = read<int>();
	REP(i, 1, n)
		REP(j, 1, m) dp[i][j] = -inf;
	REP(i, 1, n) dp[i][1] = a[i][1];
	REP(k, 2, m)
		REP(i, 2, n)
		REP(j, 1, i-1)
		{
			int res = dp[j][k-1] + a[i][k];
			if (res > dp[i][k]) frm[i][k] = make_pair(j, k - 1);
			chkmax(dp[i][k], res);
		}
	int pos(m);
	REP(i, m, n) if (dp[i][m] > dp[pos][m] || dp[i][m] == dp[pos][m] && better(i, pos)) pos = i;
	printf("%d\n", dp[pos][m]);
	getpath(patha, pos, frm[pos][m]);
	REP(i, 1, m) printf("%d%c", patha[i], i == m ? '\n' : ' ');
	return 0;
}
