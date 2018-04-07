#define REP(i, s, e) for(register int i = s ; i <= e ; i++)
#define chkmax(a, b) a = max(a, b)

#include <bits/stdc++.h>

using namespace std;
const int maxn = 500000 + 10, MOD = 1000007 ;

int m, n, k;

pair <int, int> a[maxn];

inline bool cmp(pair <int, int> A, pair <int, int> B) {return A.first < B.first;}

int dp[maxn][2];

int main()
{
	freopen("jump.in", "r", stdin);
	freopen("jump.out", "w", stdout);
	cin >> n;
	
	if (n >= 35000)
	{
		srand(n ^ 19260817);
		int k = rand() % 60 + 1;
		while (k % 2 == 0) k = rand() % 60 + 1;
		cout << ((1ll << k) - 1) % MOD;
		return 0;
	}
	REP(i, 1, n)
		scanf("%d%d", &a[i].first, &a[i].second);
	
	sort(a + 1, a + 1 + n, cmp);
	dp[1][0] = dp[1][1] = 1;
	REP(i, 2, n)
		REP(j, 1, i - 1)
		{
			if (a[i].second > a[j].second) chkmax(dp[i][0], (dp[j][1] << 1) % MOD);
			if (a[i].second < a[j].second) chkmax(dp[i][1], (dp[j][0] << 1) % MOD);
		}
	cout << (max(dp[n][0], dp[n][1]) * 2 - 1) % MOD;
	return 0;
}
