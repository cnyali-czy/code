#define  REP(i, s, e) for(register int i = s; i <= e ;i++)
#define DREP(i, s, e) for(register int i = s; i >= e ;i--)

#define chkmin(a, b) a = min(a, b)
#define chkmax(a, b) a = max(a, b)

#include <bits/stdc++.h>

using namespace std;
const int maxn = 200000 + 10, maxm = 400000 + 10, inf = 1e9;

int bg[maxn], ne[maxm << 1], to[maxm << 1], w[maxm << 1], h[maxm << 1], e;

inline void init()
{
	memset(bg, 0, sizeof(bg));
	e = 0;
}

inline void add(int x, int y, int z, int H)
{
	e++;
	to[e] = y;
	ne[e] = bg[x];
	bg[x] = e;
	w[e] = z;
	h[e] = H;
}

template <typename T> T read()
{
	T ans(0), p(1);
	char c = getchar();
	while (!isdigit(c))
	{
		if (c == '-') p = -1;
		c = getchar();
	}
	while (isdigit(c))
	{
		ans = ans * 10 + c - 48;
		c = getchar();
	}
	return ans * p;
}

int m, n, k, Q, s;

queue <int> q;
bool vis[maxn];

int dis[maxn];

inline void spfa()
{
	dis[1] = 0;
	q.push(1);
	while (!q.empty())
	{
		register int x = q.front();
		vis[x] = 0;
		q.pop();
		for (register int i = bg[x]; i ; i = ne[i])
			if (dis[to[i]] > dis[x] + w[i])
			{
				dis[to[i]] = dis[x] + w[i];
				if (!vis[to[i]])
				{
					vis[to[i]] = 1;
					q.push(to[i]);
				}
			}
	}
}

inline int solve(int v, int p)
{
	REP(i, 1, n) vis[i] = 0;
	vis[v] = 1;
	q.push(v);
	while (!q.empty())
	{
		register int x = q.front();
		q.pop();
		for (register int i = bg[x]; i ; i = ne[i])
			if (!vis[to[i]] && h[i] > p)
			{
				vis[to[i]] = 1;
				q.push(to[i]);
			}
	}
	int ans = inf;
	REP(i, 1, n) if (vis[i]) chkmin(ans, dis[i]);
	return ans;
}

int main()
{
	freopen("return.in", "r", stdin);
	freopen("return.out", "w", stdout);
	register int T = read<int>();
	while (T--)
	{
		n = read<int>();
		m = read<int>();
		int lastans = 0;
		init();

		bool flag = 1;
		while (m --> 0)
		{
			int A(read<int>()), B(read<int>()), C(read<int>()), D(read<int>());
			add(A, B, C, D);
			add(B, A, C, D);
			if (D ^ 1) flag = 0;
		}

		REP(i, 1, n) dis[i] = inf, vis[i] = 0;
		spfa();

		Q = read<int>();
		k = read<int>();
		s = read<int>();
		if (!flag)
			while (Q--)
			{
				int v(read<int>()), p(read<int>());
				v = (v + k * lastans - 1) % n + 1;
				p = (p + k * lastans) % (s + 1);
				printf("%d\n", lastans = solve(v, p));
			}
		else
			while (Q--)
			{
				int v(read<int>()), p(read<int>());
				v = (v + k * lastans - 1) % n + 1;
				p = (p + k * lastans) % (s + 1);
				if (p > 0) printf("%d\n", lastans = dis[v]);
				else printf("%d\n", lastans = 0);
			}
	}
	
	return 0;
}
