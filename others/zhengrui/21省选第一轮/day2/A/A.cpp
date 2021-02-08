#define REP(i, s, e) for (register int i(s), end_##i(e); i <= end_##i; i++)
#define DEP(i, s, e) for (register int i(s), end_##i(e); i >= end_##i; i--)

#include <algorithm>
#include <vector>
#include <iostream>
#include <cstdio>
#define i64 long long

using namespace std;
const int maxn = 300 + 5;
const i64 inf = 1e18;

int n, val[maxn], u[maxn], v[maxn];

i64 ans[maxn];

namespace bf
{
	int fa[maxn], s[maxn];
	int find(int x) {return fa[x] == x ? fa[x] : fa[x] = find(fa[x]);}
	void uni(int x, int y) {fa[find(x)] = find(y);}
	void work()
	{
		REP(i, 1, n) ans[i] = inf;
		REP(S, 0, (1 << n - 1) - 1)
		{
			REP(i, 1, n) fa[i] = i, s[i] = 0;
			int cnt = n;
			REP(i, 1, n - 1) if (S >> (i - 1) & 1)
			{
				cnt--;
				uni(u[i], v[i]);
			}
			REP(i, 1, n) s[find(i)] += val[i];
			i64 res = 0;
			REP(i, 1, n) if (find(i) == i) res += 1ll * s[i] * s[i];
			ans[cnt] = min(ans[cnt], res);
		}
		REP(i, 1, n) printf("%lld%c", ans[i], i == end_i ? '\n' : ' ' );
	}
}
namespace tiaozheng
{
	vector <int> G[maxn];
	bool pick[maxn];
	void build()
	{
		REP(i, 1, n) G[i].clear();
		REP(i, 1, n - 1) if (pick[i])
		{
			G[u[i]].emplace_back(v[i]);
			G[v[i]].emplace_back(u[i]);
		}
	}
	i64 tot;
	bool vis[maxn];
	void dfs(int x)
	{
		vis[x] = 1;
		tot += val[x];
		for (int y : G[x]) if (!vis[y]) dfs(y);
	}
	i64 calc()
	{
		build();
		REP(i, 1, n) vis[i] = 0;
		i64 res = 0;
		REP(i, 1, n) if (!vis[i])
			tot = 0, dfs(i), res += tot * tot;
		return res;
	}
	void work()
	{
		static int id[maxn];
		REP(i, 1, n - 1) id[i] = i;
		REP(k, 0, n - 1)
		{
			int times;
			if (k == 0 || k == n - 1) times = 0;
			else if (k == 1 || k == n - 2) times = 2000;
			else times = 50000;
			random_shuffle(id + 1, id + n);
			REP(i, 1, n - 1) pick[i] = 0;
			REP(i, 1, k) pick[id[i]] = 1;
			vector <int> sta[2];
			REP(i, 1, n - 1) sta[pick[i]].emplace_back(i);

			i64 ans = calc(), realans = ans;

			while (times--)
			{
				int posx = rand() % sta[1].size(), posy = rand() % sta[0].size();
				int x = sta[1][posx], y = sta[0][posy];

				sta[1][posx] = y;sta[0][posy] = x;
				pick[x] = 0;pick[y] = 1;

				i64 New = calc();
				realans = min(realans, New);

				if (New <= ans || rand() % 100 == 0) ans = New;
				else
				{
					sta[1][posx] = y;sta[0][posy] = x;
					pick[x] = 0;pick[y] = 1;
				}
			}
			::ans[n - k] = realans;
		}
		REP(i, 1, n) printf("%lld%c", ans[i], i == end_i ? '\n' : ' ' );
	}
}

int main()
{
#ifdef CraZYali
	freopen("A.in", "r", stdin);
	freopen("A.out", "w", stdout);
#endif
	srand(666233);
	int T;cin >> T;
	while (T--)
	{
		scanf("%d", &n);
		REP(i, 1, n) scanf("%d", val + i);
		REP(i, 1, n - 1) scanf("%d%d", u + i, v + i);
		if (0 && n <= 20) bf :: work();
		else tiaozheng :: work();
	}
	return 0;
}
