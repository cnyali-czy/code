#define  REP(i, s, e) for(register int i = s; i <= e ;i++)
#define DREP(i, s, e) for(register int i = s; i >= e ;i--)

#define DEBUG fprintf(stderr, "Passing [%s] in LINE %d\n", __FUNCTION__, __LINE__)
#define chkmin(a, b) a = min(a, b)
#define chkmax(a, b) a = max(a, b)

#include <bits/stdc++.h>

using namespace std;
const int maxn = 1000000 + 10, maxm = 2000000 + 10, inf = 1e9;

int bg[maxn], ne[maxm << 1], to[maxm << 1], w[maxm << 1], e = 1;
inline void add(int x, int y, int z = 0)
{
	e++;
	to[e] = y;
	ne[e] = bg[x];
	bg[x] = e;
	w[e] = z;
}
int m, n, k, q;
int c[maxn];

namespace istree
{
	queue <int> Q;
	int depth[maxn];
	
	inline void bfs_depth()
	{
		REP(i, 1, n) depth[i] = -1;
		depth[1] = 0;
		Q.push(1);
		while (!Q.empty())
		{
			register int x = Q.front();
			Q.pop();
			for (register int i = bg[x] ; i ; i = ne[i])
				if (depth[to[i]] == -1)
				{
					Q.push(to[i]);
					depth[to[i]] = depth[x] + 1;
				}
		}
	}

	int ans[maxn];
	inline void bfs_getans()
	{
		REP(i, 1, n) ans[i] = c[i];
		Q.push(1);
		while (!Q.empty())
		{
			register int x = Q.front();
			Q.pop();
			for (register int i = bg[x] ; i ; i = ne[i])
				if (depth[to[i]] == depth[x] + 1)
				{
					chkmin(ans[to[i]], ans[x]);
					Q.push(to[i]);
				}
		}
	}

	inline void solve()
	{
		bfs_depth();
		bfs_getans();

		while (q --> 0)
		{
			scanf("%d", &k);
			printf("%d\n", ans[k]);
		}
	}
}

namespace bf
{
	int ans[maxn];

	bool vis[maxn];
	int flag = 0, times = 0;

	inline void dfs(int x, int nowans)
	{
		if (times == 20000) return;times++;
		if (flag == 50) return;
		if (x == k)
		{
			flag++;
			chkmin(ans[k], nowans);
			return;
		}
		for (register int i = bg[x]; i ; i = ne[i])
			if (!vis[to[i]])
			{
				vis[to[i]] = 1;
				dfs(to[i], min(nowans, c[to[i]]));
				vis[to[i]] = 0;
			}
	}

	inline void solve()
	{
		REP(i, 1, n) ans[i] = inf;
		ans[1] = c[1];
		while (q --> 0)
		{
			scanf("%d", &k);
			if (ans[k] == inf)
			{
				times = 0;
				REP(i, 2, n) vis[i] = 0;
				vis[1] = 1;
				flag = times = 0;
				dfs(1, c[1]);
			}
			printf("%d\n", ans[k]);
		}
	}
};
/*
bool vis[maxn];

stack <pair<int, int> > s;

vector <int> v;

inline void find_huan(int S, int T)
{
	v.clear();
	while (s.top().first ^ T)
	{
		v.push_back(s.top().first);
		s.pop();
	}
	v.push_back(T);
	s.pop();
	int siz = v.size(), Min(inf);
	for (register int i = 0; i < siz ;i++)
		chkmin(Min, c[v[i]]);
	for (register int i = 0; i < siz ;i++)
		c[v[i]] = Min;
}

inline void solve()
{
	vis[1] = 1;
	s.push(make_pair(1, 1));
	while (!s.empty())
	{
		register pair<int, int> temp = s.top();
		register int x = temp.first;
		register int fa = temp.second;
		for (register int i = bg[x]; i ; i = ne[i])
			if (vis[to[i]] && fa ^ to[i])
			{
				find_huan(x, to[i]);
				goto no;
			}
			else
			{
				vis[to[i]] = 1;
				s.push(to[i]);
			}
		s.pop();
no:;
	}
	
}
*/
int main()
{
	freopen("road.in", "r", stdin);
	freopen("road.out", "w", stdout);
	cin >> n >> m >> q;
	bool istree = 0;
	if (m == n - 1) istree = 1;
	while (m--)
	{
		register int x, y;
		scanf("%d%d", &x, &y);
		x *= -1;y *= -1;
		add(x, y);
		add(y, x);
	}
	REP(i, 1, n) scanf("%d", c + i);
	if (istree) istree::solve();
	else bf::solve();
//	else solve();
	return 0;
}
