#define  REP(i, s, e) for (int i(s), end_##i(e); i <= end_##i; i++)
#define DREP(i, s, e) for (int i(s), end_##i(e); i >= end_##i; i--)
#define DEBUG fprintf(stderr, "Passing [%s] in Line %lld\n", __FUNCTION__, __LINE__)

#define chkmax(a, b) a = max(a, b)
#define chkmin(a, b) a = min(a, b)

#include <iostream>
#include <cstring>
#include <cstdio>
#define int long long

using namespace std;
const int maxn = 50 + 5, maxm = 1e5 + 10, M = 1e5, inf = 0x3f3f3f3f;
int n, a[maxn];

int dp[maxm];
int ans = inf;

int prime[maxm], pcnt;
bool notprime[maxm];
inline void init(const int N = 1e5)
{
	REP(i, 2, N)
	{
		if (!notprime[i]) prime[++pcnt] = i;
		REP(j, 1, pcnt)
		{
			if (i * prime[j] > N) break;
			notprime[i * prime[j]] = 1;
			if (i % prime[j] == 0) break;
		}
	}
}

signed main()
{
#ifdef CraZYali
	freopen("3233.in", "r", stdin);
	freopen("3233.out", "w", stdout);
#endif
	init();
	cin >> n;
	REP(i, 1, n) scanf("%lld", a + i);
	memset(dp, inf, sizeof dp);
	dp[1] = 0;
	REP(i, 1, M)
	{
		REP(j, 1, pcnt)
		{
			if (prime[j] * i > M) break;
			int val(prime[j] * i), temp(0);
			REP(k, 1, n) temp += a[k] % val / i;
			chkmin(dp[val], dp[i] + temp);
		}
		int temp(dp[i]);
		REP(k, 1, n) temp += a[k] / i;
		chkmin(ans, temp);
	}
	cout << ans << endl;
	return 0;
}
