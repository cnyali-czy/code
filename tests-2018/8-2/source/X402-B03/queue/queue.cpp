#define  REP(i, s, e) for(register int i = s; i <= e ;i++)
#define DREP(i, s, e) for(register int i = s; i >= e ;i--)

#define DEBUG fprintf(stderr, "Passing [%s] in LINE %d\n", __FUNCTION__, __LINE__)
#define chkmin(a, b) a = min(a, b)
#define chkmax(a, b) a = max(a, b)

#include <bits/stdc++.h>

using namespace std;
const int maxn = 2000 + 5, maxm = 100000, inf = 1e9;
const long long MOD = 20000909;
		
bool vis[maxn];
		
int a[maxn], b[maxn], c[maxn];
int m, n, L, ans = 1e9;
	
namespace bf
{
	inline void calc()
	{
		int res = -1;
		REP(i, 1, n)
		{
			chkmax(res, min(abs(a[i] - b[c[i]]), abs(L - abs(a[i] - b[c[i]]))));
			if (res >= ans) return;
		}
		ans = res;
	}

	void dfs(int x)
	{
		if (x == n)
		{
			calc();
			return;
		}
		x++;
		REP(i, 1, n)
			if (!vis[i])
			{
				c[x] = i;
				vis[i] = 1;
				dfs(x);
				vis[i] = 0;
			}
	}
	inline void work()
	{
		dfs(0);
		long long ANS = 1, base = 2;
		while (ans)
		{
			if (ans & 1) ANS *= base, ANS %= MOD;
			base = (base * base) % MOD;
			ans >>= 1;
		}
		cout << ANS;
	}
}

namespace bf1
{
	struct Graph
	{
		int bg[maxn], ne[maxm << 1], to[maxm << 1], w[maxm << 1], cost[maxm << 1], e = 1;
		inline void add(int x, int y, int z, int c)
		{
			e++;
			to[e] = y;
			ne[e] = bg[x];
			bg[x] = e;
			w[e] = z;
			cost[e] = c; 
		}
	}G1, G2;
	int S, T;

	bool vis[maxn];
	queue <int> q;
	int dis[maxn], pre[maxn], Max[maxn];

	bool forbid[maxn][maxn];

	inline bool spfa()
	{
		while (!q.empty()) q.pop();
		REP(i, 1, T) dis[i] = inf;
		memset(vis, 0, sizeof(vis));
		REP(i, 1, T) Max[i] = 0;
		Max[S] = inf;
		q.push(S);
		while (!q.empty())
		{
			register int x = q.front();
			vis[x] = 0;
			q.pop();
			for (register int i = G2.bg[x]; i ; i = G2.ne[i])
				if (G2.w[i] > 0 && !forbid[x][G2.to[i]] && dis[G2.to[i]] > dis[x] + G2.cost[i])
				{
					dis[G2.to[i]] = dis[x] + G2.cost[i];
					pre[G2.to[i]] = i;
					Max[G2.to[i]] = min(Max[x], G2.w[i]);
					if (!vis[G2.to[i]])
					{
						vis[G2.to[i]] = 1;
						q.push(G2.to[i]);
					}
				}
		}
		return dis[T] != inf;
	}

	int max_flow, min_cost;

	inline bool update(int mid)
	{
		DEBUG;
		int x = T;
		while (x ^ S)
		{
			G2.w[pre[x]] -= Max[T];
			G2.w[pre[x] ^ 1] += Max[T];
			x = G2.to[pre[x] ^ 1];
		}
		max_flow += Max[T];
		return 1;
	}

	inline void work()
	{
		S = n * 2 + 1, T = n * 2 + 2;
		REP(i, 1, n)
		{
			G1.add(S, i, 1, 0);
			G1.add(i, S, 0, 0);
		}
		REP(i, 1, n)
		{
			G1.add(i + n, T, 1, 0);
			G1.add(T, i + n, 0, 0);
		}
		REP(i, 1, n)
			REP(j, 1, n)
			{
				int x = i, y = j + n, c = min(abs(a[i] - b[j]), L - abs(a[i] - b[j]));
				G1.add(x, y, 1, c);
				G1.add(y, x, 0, -c);
			}
		int l(0), r(L), ans(L);
		while (l <= r)
		{
			register int mid = l + r >> 1;
			REP(i, 1, T)
				REP(j, 1, T)
					forbid[i][j] = 0;
			G2 = G1;
			REP(x, 1, T)
				for (register int i = G2.bg[x] ; i ; i = G2.ne[i])
					if (G2.cost[i] > mid) forbid[x][G2.to[i]] = 1;
			min_cost = 0;
			max_flow = 0;
			while (spfa())
			{
				register bool flag = update(mid);
			}
			if (max_flow != n) l = mid + 1;
			else
			{
				ans = mid;
				r = mid - 1;
			}
no:;
		}
		long long ANS = 1, base = 2;
		while (ans)
		{
			if (ans & 1) ANS *= base, ANS %= MOD;
			base = (base * base) % MOD;
			ans >>= 1;
		}
		
		cout << ANS;
	}
}

int main()
{
	freopen("queue.in", "r", stdin);
	freopen("queue.out", "w", stdout);
	cin >> n >> L;
	REP(i, 1, n) scanf("%d", a + i);
	REP(i, 1, n) scanf("%d", b + i);
	if (n <= 10) bf::work();
//	else bf1::work();
	return 0;
}
