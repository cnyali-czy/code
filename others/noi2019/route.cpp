#define REP(i, s, e) for (int i = s ; i <= e; i++)

#include <bits/stdc++.h>
#define int long long
#define chkmin(a, b) a = min(a, b)
using namespace std;
const int maxn = 8e5 + 10, maxm = 8e5 + 10, inf = 1ll << 50;
int read()
{
	char c = getchar();
	while (!isdigit(c)) c = getchar();
	int ans = 0;
	while (isdigit(c))
	{
		ans = ans * 10 + c - 48;
		c = getchar();
	}
	return ans;
}
int n, m, A, B, C;
int dis[maxm], bg[maxn], ne[maxm], s[maxm], U[maxm], V[maxm], e;
pair <int, int> to[maxm];
map <pair <int, int>, int> id;int cur;
priority_queue <pair <int, pair <pair <int, int> , int> > > q;
void add(int x, int p, int y, int q)
{
	e++;
	U[e] = id[make_pair(x, p)];
	V[e] = id[make_pair(y, q)];
	to[e] = make_pair(y, q);
	ne[e] = bg[x];
	bg[x] = e;
	s[e] = p;
}
signed main()
{
	freopen("route.in", "r", stdin);
	freopen("route.out", "w", stdout);
	cin >> n >> m >> A >> B >> C;
	id[make_pair(1, 0)] = ++cur;
	REP(i, 1, m)
	{
		int x(read()), y(read()), p(read()), q(read());
		if (!id[make_pair(x, p)]) id[make_pair(x, p)] = ++cur;
		if (!id[make_pair(y, q)]) id[make_pair(y, q)] = ++cur;
		add(x, p, y, q);
	}
	REP(i, 2, cur) dis[i] = inf;
	U[0] = 1;V[0] = 1;
	q.push(make_pair(0, make_pair(make_pair(1, 0), 0)));
	while (!q.empty())
	{
		int s = -q.top().first, x = q.top().second.first.first, t = q.top().second.first.second, ID = V[q.top().second.second];
		q.pop();
		if (x == n) {cout << s << endl;return 0;}
		if (dis[ID] < s) continue;
		for (int i = bg[x]; i ; i = ne[i])
		{
			if (::s[i] < t) continue;
			pair <int, int> u = to[i];
			int w = A * (::s[i] - t) * (::s[i] - t) + B * (::s[i] - t) + C;
			if (dis[V[i]] > s + w - t + u.second)
			{
				dis[V[i]] = s + w - t + u.second;
				q.push(make_pair(-dis[V[i]], make_pair(u, i)));
			}
		}		
	}
	return 0;
}
