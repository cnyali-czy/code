#define REP(i, s, e) for (int i = s; i <= e; i++)
#define DEBUG fprintf(stderr, "Passing [%s] in Line %d\n", __FUNCTION__, __LINE__)
#include <bits/extc++.h>
#include <unordered_map>
#include <iostream>
#include <cstdio>
#include <cmath>
#define int long long
using namespace std;
const int N = 1e6, maxn = N + 10, MOD = 1e9 + 7;

int n, ans, s[maxn], top;
inline bool reverse(int x, int N = n)
{
	top = 0;
	REP(i, 1, N) s[++top] = x % 10, x /= 10;
	int l(1), r(top);
	while (l < r) if (s[l++] ^ s[r--]) return 0;
	return 1;
}

inline bool judge(int x)
{
	if (!reverse(x)) return 0;
	int cnt[2]={0}, cur(0);
	while (x)
		cnt[cur ^= 1] += x % 10, x /= 10;
	return cnt[0] == cnt[1];
}
int power_pow(int a, int b)
{
	int ans = 1,base(a);
	while (b)
	{
		if (b & 1) ans = ans * base % MOD;
		base = base * base % MOD;
		b >>= 1;
	}
	return ans;
}

namespace dp
{
	__gnu_pbds::gp_hash_table <int, int> dp[2];
	int cur;
	int ANS[maxn];
	int delta(int x)// ji - ou
	{
		int cnt[2]={0},cur=0;
		while (x)
			cnt[cur^=1]+=x%10,x/=10;
		return cnt[1] - cnt[0];
	}
	int N = 3;
	void work()
	{
		for (int i = N + 2; i <= n; i += 2)
		{
			dp[cur ^= 1].clear();
			int lim=(i+1>>1)*9,Min=-(i>>1)*9,ll=(i>>1)*9;
			REP(j, -(i-2>>1)*9, ll) REP(k, 0, 9) if (Min<=k+k-j&&k+k-j<=lim)
			{
				dp[cur][k+k-j] += dp[cur ^ 1][j];
				if (dp[cur][k+k-j] >= MOD) dp[cur][k+k-j] %= MOD;
			}
			ANS[i] = dp[cur][0];
		}
		ans = ANS[n];
		N = max(N, n);
	}
	void init()
	{
		ANS[1] = 1;
		REP(i, 0, 999)
			if (reverse(i, 3)) dp[cur][delta(i)]++;
		ANS[3] = dp[cur][0];
	}
}

signed main()
{
#ifndef ONLINE_JUDGE
	freopen("B.in", "r", stdin);
	freopen("B.out", "w", stdout);
#endif
	dp::init();
	int T;cin >> T;
	while (T--)
	{
		scanf("%lld", &n);
		if (n % 2 == 0) ans = power_pow(10, n >> 1);
		else dp::work();
		printf("%lld\n", (ans % MOD + MOD) % MOD);
	}
	return 0;
}
