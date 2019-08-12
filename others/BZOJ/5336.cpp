#define  REP(i, s, e) for (int i = s; i <= e; i++)
#define DREP(i, s, e) for (int i = s; i >= e; i--)
#define DEBUG fprintf(stderr, "Passing [%s] in Line %d\n", __FUNCTION__, __MOD__)

#define chkmax(a, b) a = max(a, b)
#define chkmin(a, b) a = min(a, b)

#include<iostream>
#include<cstdio>
#include<cstring>
using namespace std;
const int maxn = 1000 + 10, MOD = 1e9 + 7, K = 15, maxk = K + 5, maxK = 1 << K;
int n, k, ans[maxk];

char s[maxk], ban[]{"NOI"};
int f[2][maxK][3], transpos[maxK][3], cnt[maxK];
int dp[maxk], temp[maxk];

inline int Get(int S, int c)
{
	int ret(0);
    REP(i, 1, k)
	{
		dp[i] = dp[i-1] + !!(S & (1<<i-1));
		temp[i] = ban[c] == s[i] ? dp[i-1] + 1 : max(dp[i], temp[i-1]);
		ret |= temp[i] - temp[i-1] << i-1;
	}
#ifdef CraZYali
	cout << ret << endl;
#endif
    return ret;
}

int main()
{
#ifdef CraZYali
	freopen("5336.in", "r", stdin);
	freopen("5336.out", "w", stdout);
#endif
	cin >> n >> k;
	scanf("%s", s + 1);
	const int lim = 1 << k;
	REP(i, 0, lim - 1)
		REP(c, 0, 2) transpos[i][c] = Get(i, c);
	REP(i, 0, lim - 1) cnt[i] = cnt[i>>1] + (i & 1);
    f[0][0][0] = 1;
	int cur = 0;
	REP(i, 1, n)
	{
		cur ^= 1;
		memset(f[cur], 0, sizeof(f[cur]));
		REP(j, 0, lim - 1)
			REP(p, 0, 2)
			REP(c, 0, 2)
			{
				int np(c ? c == 1 ? p == 1 ? 2 : 0 : p == 2 ? 3 : 0 : 1);
				(f[cur][transpos[j][c]][np] += (!!(np ^ 3)) * f[cur ^ 1][j][p]) %= MOD;
			}

	}
	REP(i, 0, lim - 1)
		REP(c, 0, 2)
			(ans[cnt[i]] += f[cur][i][c]) %= MOD;
	REP(i, 0, k) printf("%d\n", (ans[i] + MOD) % MOD);
	return 0;
}
