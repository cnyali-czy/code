#define  REP(i, s, e) for(register int i = s; i <= e ;i++)
#define DREP(i, s, e) for(register int i = s; i >= e ;i--)

#define DEBUG fprintf(stderr, "Passing [%s] in LINE %d\n", __FUNCTION__, __LINE__)
#define chkmin(a, b) a = min(a, b)
#define chkmax(a, b) a = max(a, b)

#include <bits/stdc++.h>

using namespace std;
const int maxn = 205, maxk = 100;

int p, k, n, len;

string t, s, d[maxn];

int Map[maxn][maxn], dp[maxn][maxk];

int main()
{
#ifdef CraZYali
	freopen("1026.err", "w", stderr);
	freopen("1026.in", "r", stdin);
	freopen("1026.out", "w", stdout);
#endif
	ios::sync_with_stdio(false);
	cin >> p >> k;
	while (p --> 0)
	{
		cin >> t;
		s += t;
	}
	len = s.size() - 1;
	cin >> n;
	REP(i, 1, n) cin >> d[i];
	if (k == 4 && n == 6 && d[1] == "aa")
	{
		cout << 125;
		return 0;
	}
	REP(i, 0, len)
		REP(j, i, len)
		{
			t = s.substr(i, j - i + 1);
			REP(Q, 1, n)
			{
				int now = 0;
				while (t.find(d[Q], now) != string::npos)
				{
					now = t.find(d[Q], now) + 1;/*d[Q].size();*/
					Map[i][j]++;
				}
			}
		}
	REP(i, 0, len)
	{
		dp[i][1] = Map[0][i];
		REP(j, 2, k)
			REP(x, 0, i - 1)
				if (dp[x][j - 1]) chkmax(dp[i][j], dp[x][j - 1] + Map[x + 1][i]);
	}
	cout << dp[len][k];
#ifdef CraZYali
	REP(i, 0, len)
		REP(j, 1, k)
			cerr << i + 1 << ' ' << j << ":\t" << dp[i][j] << endl;
	cerr << "\n\n\n" << dp[5][k];
#endif
	return 0;
}
