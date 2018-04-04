#define DREP(i, s, e) for(register int i = s; i >= e ;i--)
#define  REP(i, s, e) for(register int i = s; i <= e ;i++)

#define DEBUG fprintf(stderr, "Passing [%s] in Line %d\n", __FUNCTION__, __LINE__)
#define chkmax(a, b) a = max(a, b)
#define chkmin(a, b) a = min(a, b)

#include <algorithm>
#include <iostream>
#include <cstdlib>
#include <cstring>
#include <cstdio>
#include <bitset>
#include <vector>
#include <cmath>
#include <queue>
#include <map>
#include <set>

using namespace std;
const int maxn = 200 + 5, maxtime = maxn * maxn + maxn;

int m, n, k;

pair <int, int> A[maxn];
inline bool cmp(pair <int, int> A, pair <int, int> B) {return A.second > B.second;}

int dp[2][maxtime], sum[maxn];

int main()
{
#ifdef CraZYali
	freopen("2577.in", "r", stdin);
	freopen("2577.out", "w", stdout);
#endif
	cin >> n;
	REP(i, 1, n) scanf("%d %d", &A[i].first, &A[i].second);
	sort(A + 1, A + 1 + n, cmp);
	REP(i, 1, n) sum[i] = sum[i - 1] + A[i].first;
	memset(dp[0], 0x3f, sizeof(dp[0]));
	dp[0][0] = 0;
	REP(i, 1, n)
	{
		int now = i & 1, pre = now ^ 1;
		memset(dp[now], 0x3f, sizeof(dp[now]));
		DREP(j, sum[i], 0)
		{
			if (j >= A[i].first) 			chkmin(dp[now][j], max(dp[pre][j - A[i].first], j + A[i].second));
			if (sum[i] - j >= A[i].first) 	chkmin(dp[now][j], max(dp[pre][j], sum[i] - j + A[i].second));
		}
	}
	int ans = 0x3f3f3f3f;
	REP(i, 0, sum[n]) chkmin(ans, dp[n & 1][i]);
	cout << ans;
	return 0;
}

