#define  REP(i, s, e) for(register int i = s; i <= e ;i++)
#define DREP(i, s, e) for(register int i = s; i >= e ;i--)

#define DEBUG fprintf(stderr, "Passing [%s] in LINE %d\n", __FUNCTION__, __LINE__)
#define chkmin(a, b) a = min(a, b)
#define chkmax(a, b) a = max(a, b)

#include <bits/stdc++.h>

using namespace std;
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

const int maxn = 200, maxc = 50 + 5, maxm = 4e4 + 10;

int bg[maxn], ne[maxm], to[maxm], w[maxm], e, wmax, dis[maxn][maxn];
inline void add(int x, int y, int z)
{
	e++;
	to[e] = y;
	ne[e] = bg[x];
	bg[x] = e;
	w[e] = z;
	chkmax(wmax, z);
	dis[x][y] = 1;
}

int m, n, c;

struct temp
{
	int u, v, l;
}t[maxm];
int _w[maxc];

struct node
{
	int now, sw, ans;
};

#define Node pair<int, int>
#define x first
#define step second
bool vis[maxn];
inline void cheat()
{
	if (w[1]) cout << "Impossible";
	else
	{
		queue <Node> q;
		q.push(make_pair(1, 0));
		vis[1] = 1;
		while (!q.empty())
		{
			register Node now = q.front();
			int x= now.x;
			if (x == n)
			{
				cout << now.step;
				return;
			}
			q.pop();
			for (register int i = bg[x]; i ; i = ne[i])
				if (!vis[to[i]])
				{
					if (to[i] == n)
					{
						cout << now.step + 1;
						return;
					}
					vis[to[i]] = 1;
					q.push(make_pair(to[i], now.step + 1));
				}
		}
	}
	cout << "Impossible";
}

inline void floyd()
{
	REP(k, 1, n)
		REP(i, 1, n)
			REP(j, 1, n)
				chkmin(dis[i][j], dis[i][k] + dis[k][j]);
}

int AL[maxn];

int main()
{
	freopen("griffin.in", "r", stdin);
	freopen("griffin.out", "w", stdout);
	DEBUG;
	n = read<int>();
	m = read<int>();
	c = read<int>();
	DEBUG;
	REP(i, 1, m) t[i].u = read<int>(), t[i].v = read<int>(), t[i].l = read<int>();
	REP(i, 1, c) _w[i] = read<int>();
	bool flag = 0;
	REP(i, 1, m)
		if (!_w[t[i].l])
		{
			flag = 1;
			break;
		}
	if (!flag) {cout << "Impossible";return 0;}
	REP(i, 1, m) add(t[i].u, t[i].v, _w[t[i].l]);
	if (c == 1) {cheat();return 0;}
	REP(i, 1, n) dis[i][i] = 0;
	floyd();
	queue <node> q;
	q.push((node){1, 0, 0});
	double NOW = clock();
	DEBUG;
	while (!q.empty())
	{
		if ((clock() - NOW) * 1.0 / CLOCKS_PER_SEC >= 0.8) {cout << "Imposiible";return 0;}
		cout << (clock() - NOW) * 1.0 / CLOCKS_PER_SEC << endl;
		node f = q.front();
		q.pop();
		int x = f.now;
		if (x == n)
		{
			cout << f.ans;
			return 0;
		}
		if (f.sw >= wmax && dis[f.sw][n])
		{
			cout << f.ans + dis[f.sw][n];
			return 0;
		}
		for (register int i = bg[x]; i ; i = ne[i])
			if (f.sw >= w[i])
			{
				if (to[i] == n)
				{
					cout << f.ans + 1;
					return 0;
				}
				q.push((node){to[i], f.sw + 1, f.ans + 1});
			}
	}
	cout << "Impossible";
	return 0;
}
