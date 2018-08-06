#define  REP(i, s, e) for(register int i = s; i <= e ;i++)
#define DREP(i, s, e) for(register int i = s; i >= e ;i--)

#define chkmin(a, b) a = min(a, b)
#define chkmax(a, b) a = max(a, b)

#include <bits/stdc++.h>

using namespace std;
const long long MOD = 998244353;

inline long long power_pow(long long a, long long b)
{
	long long ans = 1, base = a;
	while (b)
	{
		if (b & 1) ans = (ans * base) % MOD;
		base = (base * base) % MOD;
		b >>= 1;
	}
	return ans;
}

int m, n, k, Case, q, x, l, r;

long long A, B, t;

namespace ONE
{
	const int maxn = 20;
	long long p[maxn], pai, pbi, cb[maxn];
	inline void work()
	{
		REP(i, 1, n)
		{
			scanf("%lld%lld", &pai, &pbi);
			pai %= MOD;
			pbi %= MOD;
			p[i] = (pai * power_pow(pbi, MOD - 2)) % MOD;
			p[i] = (p[i] + MOD) % MOD;
		}

		while (q --> 0)
		{
			scanf("%d", &x);
			if (!x)
			{
				scanf("%d%lld%lld", &x, &pai, &pbi);
				pai %= MOD;pbi %= MOD;
				p[x] = (pai * power_pow(pbi, MOD - 2)) % MOD;
				p[x] = (p[x] + MOD) % MOD;
			}
			else
			{
				scanf("%d%d", &l, &r);
				long long BasicScore = 0;
				REP(i, l, r) BasicScore += p[i], BasicScore %= MOD;
				cb[l] = p[l];
				REP(i, l + 1, r)
					if (p[i]) cb[i] = (cb[i - 1] + 1) % MOD;
					else cb[i] = (cb[i - 1] * t) % MOD, cb[i] = (cb[i] + MOD) % MOD;
				long long ComboScore = B % MOD;
				REP(i, l, r) ComboScore *= cb[i], ComboScore %= MOD;
				long long totol = (BasicScore + ComboScore) % MOD;
				printf("%lld\n", (ComboScore + MOD) % MOD);
			}
		}
	}
}

namespace bf
{

	const int maxn = 20;
	int opt, x, l, r;
	long long pai[maxn], pbi[maxn], cb[maxn], ans;

	bool vis[maxn];

	void calc()
	{
		long long BasicScore, TOT = 0;
		REP(i, l, r) TOT += vis[i];
		TOT %= MOD;
		BasicScore = TOT * A % MOD;
		cb[l] = vis[l];
		REP(i, l + 1, r)
			if (vis[i]) cb[i] = (cb[i - 1] + 1) % MOD;
			else cb[i] = cb[i - 1] * t % MOD, cb[i - 1] = (cb[i - 1] + MOD) % MOD;
		long long ComboScore = 0;
		REP(i, l, r)
		{
			ComboScore += vis[i] * cb[i] % MOD, ComboScore = (ComboScore + MOD) % MOD;
		}
		ComboScore = ComboScore * B % MOD;
		ComboScore = (ComboScore + MOD) % MOD;
		long long tt = (BasicScore + ComboScore) % MOD;
		long long chu = 1;
		REP(i, l, r)
		{
			if (pai[i] == pbi[i] || !pai[i]) continue;
			long long AAA = pai[i] * power_pow(pbi[i], MOD - 2) % MOD;
			long long BBB = ((MOD + pbi[i] - pai[i]) % MOD) * power_pow(pbi[i], MOD - 2) % MOD;
			AAA = (AAA + MOD) % MOD;
			BBB = (BBB + MOD) % MOD;
			if (vis[i]) chu = chu * AAA % MOD;
			else chu = chu * BBB % MOD;
			chu = (chu + MOD) % MOD;
		}
		ans += (tt *chu) % MOD;
		ans = (ans + MOD) % MOD;
	}
	void dfs(int x)
	{
		if (x == r) calc();
		else
		{
			x++;
			if (pai[x] == 0) vis[x] = 0, dfs(x);
			else if (pai[x] == pbi[x]) vis[x] = 1, dfs(x);
			else 
			{
				vis[x] = 1;
				dfs(x);
				vis[x] = 0;
				dfs(x);
			}
		}
	}

	inline void work()
	{
		REP(i, 1, n)
		{
			scanf("%lld%lld", pai + i, pbi + i);
			pai[i] %= MOD;
			pbi[i] %= MOD;
		}
		while (q --> 0)
		{
			scanf("%d", &opt);
			if (opt == 0)
			{
				scanf("%d", &x);
				scanf("%lld%lld", pai + x, pbi + x);
				pai[x] %= MOD;pbi[x] %= MOD;
			}
			else
			{
				scanf("%d%d", &l, &r);
				ans = 0;
				memset(vis, 0, sizeof(vis));
				dfs(l - 1);
				ans %= MOD;
				printf("%lld\n", (ans + MOD) % MOD);
			}
		}
	}
}

int main()
{
	freopen("omeed.in", "r", stdin);
	freopen("omeed.out", "w", stdout);

	register long long ta, tb;

	cin >> Case >> n >> q >> ta >> tb >> A >> B;

	ta %= MOD;tb %= MOD;

	t = ta * power_pow(tb, MOD - 2) % MOD;

	t = (t + MOD) % MOD;

	if (Case == 1) return 0;
	else bf::work();
	return 0;
}
