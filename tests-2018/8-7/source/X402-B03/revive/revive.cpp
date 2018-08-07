#define  REP(i, s, e) for(register long long i = s; i <= e ;i++)
#define DREP(i, s, e) for(register long long i = s; i >= e ;i--)

#define DEBUG fprintf(stderr, "Passing [%s] in LINE %d\n", __FUNCTION__, __LINE__)
#define chkmin(a, b) a = min(a, b)
#define chkmax(a, b) a = max(a, b)

#include <bits/stdc++.h>

using namespace std;
const long long maxn = 1e5 + 10, maxm = maxn;
const long long MOD = 1e9 + 7, inf = 1ll << 40ll;

long long bg[maxn], ne[maxm << 1], to[maxm << 1], e = 1;
long long w[maxm << 1];
inline void add(long long x, long long y, long long z)
{
	e++;
	to[e] = y;
	ne[e] = bg[x];
	bg[x] = e;
	w[e] = z;
}

long long m, n, q;
long long fa[maxn];

namespace bf
{
	long long dis[maxn];
	bool vis[maxn];
	void dfs(long long x)
	{
		for (register long long i = bg[x] ; i ; i = ne[i])
			if (!vis[to[i]])
			{
				vis[to[i]] = 1;
				dis[to[i]] = (dis[x] + w[i]) % MOD;
				dfs(to[i]);
			}
	}

	inline void solve()
	{
		long long ans = 0;
		REP(u, 1, n)
		{
			REP(j, 1, n) vis[j] = 0;
			vis[u] = 1;
			dis[u] = 0;
			dfs(u);
			REP(v, u + 1, n)
				ans += dis[v] * dis[v], ans %= MOD;
		}
		printf("%lld\n", ans);
	}

	inline void work()
	{
		solve();
		while (q--)
		{
			register long long u;
			long long v;
			scanf("%d%lld", &u, &v);
			for (register long long i = bg[u]; i ; i = ne[i])
				if (to[i] == fa[u])
				{
					w[i] += v;
					w[i ^ 1] += v;
				}
			solve();
		}
	}
}

int main()
{
	freopen("revive.in", "r", stdin);
	freopen("revive.out", "w", stdout);
	long long Case;
	cin >> Case >> n >> q;
	REP(i, 2, n)
	{
		register long long f;
		register long long W;
		scanf("%d%lld", &f, &W);
		W %= MOD;
		fa[i] = f;
		add(i, f, W);
		add(f, i, W);
	}
	if (n <= 4000) bf::work();
	return 0;
}
