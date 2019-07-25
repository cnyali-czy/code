//modify
#define  REP(i, s, e) for (register int i = s; i <= e; i++)
#define DREP(i, s, e) for (register int i = s; i >= e; i--)

#include <algorithm>
#include <iostream>
#include <cstdio>
#include <ctime>
using namespace std;
const long long N = 150, maxn = N + 10, MOD = 1e9 + 7;

inline long long power_pow(long long a, long long b)
{
	long long ans = 1, base = a;
	while (b)
	{
		if (b & 1) ans = ans * base % MOD;
		base = base * base % MOD;
		b >>= 1;
	}
	return ans;
}
#define inv(x) power_pow(x, MOD-2)
int n, m, k;
int fac[maxn], Inv[maxn], single[maxn], bin[maxn], dp[maxn];
int v[maxn], p;

int calc()
{
	int n = p;
	REP(i, 1, m) dp[i] = 0;
	dp[0] = 1;
	REP(i, 1, m)
	{
		long long coef = single[i];
		REP(j, 1, n) coef = coef * bin[__gcd(v[j], i)] % MOD;
		DREP(j, m, 0)
		{
			long long cur = coef;
			for (int k = 1; j + i * k <= m; k++)
			{
				dp[j + i * k] = (dp[j + i * k] + dp[j] * cur % MOD * Inv[k]) % MOD;
				cur = cur * coef % MOD;
			}
		}
	}
	int ans = dp[m], cnt = 0;
	REP(i, 1, n)
	{
		ans = ans * 1ll * single[v[i]] % MOD;
		if (i > 1 && v[i] ^ v[i - 1])
		{
			ans = ans * 1ll * Inv[cnt] % MOD;
			cnt = 0;
		}
		cnt++;
	}
	return ans * 1ll * Inv[cnt] % MOD;
}

int dfs(int less, int last)
{
	if (!less) return calc();
	int res = 0;
	DREP(i, min(less, last), 1)
	{
		res = (0ll + res + dfs(less - i, v[++p] = i)) % MOD;
		--p;
	}
	return res;
}

signed main()
{
#ifndef ONLINE_JUDGE
	freopen("A.in", "r", stdin);
	freopen("A.out", "w", stdout);
#endif
	cin >> n >> m >> k;
	fac[0] = Inv[0] = bin[0] = 1;
	REP(i, 1, N)
	{
		fac[i] = 1ll * fac[i - 1] * i % MOD;
		single[i] = power_pow(i, MOD - 2);
		bin[i] = 1ll * bin[i - 1] * k % MOD;
	}
	Inv[N] = inv(fac[N]);
	DREP(i, N-1, 1) Inv[i] = 1ll * Inv[i+1] * (i+1) % MOD;

	cout << dfs(n, n) << endl;
#ifndef ONLINE_JUDGE
	cerr<<clock()*1./CLOCKS_PER_SEC<<endl;
#endif
	return 0;
}
