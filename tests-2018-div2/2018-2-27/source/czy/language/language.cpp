#define  REP(i, s, e) for(register int i = s; i <= e ;i++)
#define DREP(i, s, e) for(register int i = s; i >= e ;i--)

#define DEBUG fprintf(stderr, "Passing [%s] in LINE %d\n", __FUNCTION__, __LINE__)
#define chkmin(a, b) a = min(a, b)
#define chkmax(a, b) a = max(a, b)

#include <bits/stdc++.h>

using namespace std;
const int maxn = 200 + 5, maxm = 200 + 5;

int m, n, k;
map <string, int> d;
bool G[maxn][maxn];
int DP[maxn], path[maxn], in[maxn];

inline int dp(int x)
{
	if (DP[x] > 0) return DP[x];
	REP(i, 1, m)
		if (G[x][i])
		{
			register int temp = dp(i) + 1;
			if (temp > DP[x])
			{
				DP[x] = temp;
				path[x] = i;
			}
		}
	return DP[x];
}

string a[maxn], t1[maxm], t2[maxm];

int main()
{
	freopen("language.in", "r", stdin);
	freopen("language.out", "w", stdout);
	ios::sync_with_stdio(false);
	cin >> n >> m;
	REP(i, 1, n)
	{
		cin >> a[i];
		d[a[i]] = i;
	}
	REP(i, 1, m) cin >> t1[i] >> t2[i];
	REP(i, 1, m)
		REP(j, 1, m)
			if (i ^ j && t1[j] == t2[i]) G[i][j] = 1, in[j]++;
	int Max(0), cho(0);
	REP(i, 1, m) if (!in[i])
	{
		memset(DP, 0, sizeof(DP));
		memset(path, -1, sizeof(path));
		int now = dp(i);
		if (now > Max)
		{
			Max = now;
			cho = i;
		}
	}
	memset(DP, 0, sizeof(DP));
	memset(path, -1, sizeof(path));
	dp(cho);
	cout << Max + 2 << endl << t1[cho];
	do
	{
		cout << ' ' << t2[cho];
		cho = path[cho];
	}while (cho != -1);
	return 0;
}
