#define REP(i, s, e) for (int i = s; i <= e ; i++)
#define DEBUG fprintf(stderr, "Passing [%s] in Line %d\n", __FUNCTION__, __LINE__)

#include <bits/stdc++.h>
#define int long long
#define chkmin(a, b) a = min(a, b)

using namespace std;
const int maxn = 4000 + 10, inf = 1e9;

int n, L[maxn], R[maxn], sum1[maxn], sum2[maxn];;
int dp[maxn];

bool judge(int l, int r, int L, int R)
{
	if (l > r) return 1;
	return L * 2 * (sum1[r] - sum1[l-1]) <= sum2[r] - sum2[l-1] && sum2[r] - sum2[l-1] <= R * 2 * (sum1[r] - sum1[l-1]);
}
bool ok[maxn][maxn];

signed main()
{
#ifndef ONLINE_JUDGE
	freopen("A.in", "r", stdin);
	freopen("A.out", "w", stdout);
#endif
	cin >> n;
	REP(i, 1, n)
	{
		scanf("%lld%lld", L + i, R + i);
		sum1[i] = sum1[i-1] + R[i] - L[i];
		sum2[i] = sum2[i-1] + (L[i] + R[i]) * (R[i] - L[i]);
	}
	REP(i, 1, n)
		REP(j, i, n)
		if (judge(i, j-1, L[j], R[j])) ok[i][j] = 1;
		else break;
	REP(i, 1, n) dp[i] = inf;
	REP(i, 0, n)
		REP(j, i + 1, n)
		if (ok[i+1][j] && (ok[j+1][n] || j == n)) chkmin(dp[j], max(dp[i], j - i)); 
	cout << dp[n] << endl;
	return 0;
}
