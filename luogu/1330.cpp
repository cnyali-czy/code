#define  REP(i, s, e) for(register int i = s; i <= e ;i++)
#define DREP(i, s, e) for(register int i = s; i >= e ;i--)

#define DEBUG fprintf(stderr, "Passing [%s] in LINE %d\n", __FUNCTION__, __LINE__)
#define chkmin(a, b) a = min(a, b)
#define chkmax(a, b) a = max(a, b)

#include <bits/stdc++.h>

using namespace std;
const int maxn = 10000 + 10, maxm = 100000 + 10;

int bg[maxn], ne[maxm << 1], to[maxm << 1], e = 1;
inline void add(int x, int y)
{
	e++;
	to[e] = y;
	ne[e] = bg[x];
	bg[x] = e;
}

int m, n, k;

int color[maxn];
bool flag;

queue <pair<int, bool> > q;
bool vis[maxn];

int bfs(int S, bool mode)
{
	while (!q.empty()) q.pop();
	q.push(make_pair(S, color[S] = 0));
	if (mode == 0)
		while (!q.empty())
		{
			register int x = q.front().first;
			register bool now = q.front().second;
			q.pop();
			for (register int i = bg[x]; i ; i = ne[i])
				if (color[to[i]] != -1)
				{
					if (color[to[i]] != now ^ 1) return 0;
				}
				else q.push(make_pair(to[i], color[to[i]] = now ^ 1));
		}
	else while (!q.empty())
	{
		int ansA(0), ansB(0);
		vis[S] = 1;
		while (!q.empty())
		{
			register int x = q.front().first;
			q.pop();
			if (!color[x]) ansA++;
			else ansB++;
			for (register int i = bg[x]; i ; i = ne[i])
				if (!vis[to[i]])
				{
					vis[to[i]] = 1;
					q.push(make_pair(to[i], 0));
				}
		}
		return min(ansA, ansB);
	}
}

int main()
{
#ifdef CraZYali
	freopen("1330.in", "r", stdin);
	freopen("1330.out", "w", stdout);
#endif
	cin >> n >> m;
	memset(color, -1, sizeof(color));
	while (m --> 0)
	{
		register int x, y;
		scanf("%d%d", &x, &y);
		add(x, y);add(y, x);
	}
	register int ans = 0;
	REP(i, 1, n)
		if (color[i] == -1)
		{
			flag = bfs(i, 0);
			if (!flag)
			{
				cout << "Impossible";
				return 0;
			}
			else ans += bfs(i, 1);
		}
	cout << ans;
	return 0;
}
