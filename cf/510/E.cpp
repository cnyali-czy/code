/*
	Problem:	E.cpp
	Time:		2021-03-05 21:39
	Author:		CraZYali
	E-Mail:		yms-chenziyang@outlook.com 
*/

#define REP(i, s, e) for (register int i(s), end_##i(e); i <= end_##i; i++)
#define DEP(i, s, e) for (register int i(s), end_##i(e); i >= end_##i; i--)
#define DEBUG fprintf(stderr, "Passing [%s] in Line %d\n", __FUNCTION__, __LINE__)

#define chkmax(a, b) (a < (b) ? a = (b) : a)
#define chkmin(a, b) (a > (b) ? a = (b) : a)

#include <vector>
#include <iostream>
#include <cstdio>

using namespace std;
const int maxn = 20005;
	
	template <typename T>
inline T read()
{
	T ans = 0, flag = 1;
	char c = getchar();
	while (!isdigit(c))
	{
		if (c == '-') flag = -1;
		c = getchar();
	}
	while (isdigit(c))
	{
		ans = ans * 10 + (c - 48);
		c = getchar();
	}
	return ans * flag;
}

#define file(FILE_NAME) freopen(FILE_NAME".in", "r", stdin), freopen(FILE_NAME".out", "w", stdout)

int n, a[maxn];

bool notp[maxn];
struct __init__
{
	__init__(const int n = 2e4)
	{
		notp[1] = 1;
		REP(i, 1, n) if (!notp[i]) REP(j, 2, n / i) notp[i * j] = 1;
	}
}__INIT__;

int N, S, T;
int bg[maxn], ne[maxn], to[maxn], w[maxn], e = 1;
inline void add(int x, int y, int z)
{
	e++;
	to[e] = y;
	ne[e] = bg[x];
	bg[x] = e;
	w[e] = z;
}
inline void Add(int x, int y, int z)
{
	add(x, y, z);
	add(y, x, 0);
}

int dis[maxn];
bool bfs()
{
	static int que[maxn], head, tail;
	REP(i, 1, N) dis[i] = -1;
	dis[que[head = tail = 0] = T] = 1;
	while (head <= tail)
	{
		int x = que[head++];
		for (int i = bg[x]; i; i = ne[i])
			if (dis[to[i]] == -1 && w[i ^ 1] > 0)
			{
				dis[to[i]] = dis[x] + 1;
				que[++tail] = to[i];
			}
	}
	return dis[S] != -1;
}
int cur[maxn];
int dfs(int x = S, int y = 1e9)
{
	if (x == T || !y) return y;
	int res = 0;
	for (int i = cur[x]; i; i = ne[i])
		if (w[i] > 0 && dis[to[i]] == dis[x] - 1)
		{
			int tmp = dfs(to[i], min(y, w[i]));
			if (tmp > 0)
			{
				res += tmp;
				y -= tmp;
				w[i] -= tmp;
				w[i ^ 1] += tmp;
				if (!y) break;
			}
		}
	return res;
}

vector <int> G[maxn];
bool vis[maxn];
vector <int> res;
vector <vector <int> > ans;

void go(int x)
{
	vis[x] = 1;
	res.emplace_back(x);
	for (int y : G[x]) if (!vis[y]) return go(y);
}

int main()
{
#ifdef CraZYali
	file("E");
#endif
	cin >> n;
	REP(i, 1, n) a[i] = read<int>();
	S = n + 1;N = T = n + 2;
	REP(i, 1, n)
		if (a[i] & 1)
		{
			Add(S, i, 2);
			REP(j, 1, n) if (!notp[a[i] + a[j]]) Add(i, j, 1);
		}
		else Add(i, T, 2);
	int flow = 0;
	while (bfs())
		copy(bg, bg + 1 + N, cur), flow += dfs();
	if (flow != n) return 0 * puts("Impossible");
	REP(x, 1, n) if (a[x] & 1)
		for (int i = bg[x]; i; i = ne[i]) if (1 <= to[i] && to[i] <= n && !w[i])
			G[x].emplace_back(to[i]), G[to[i]].emplace_back(x);
	REP(i, 1, n) if (!vis[i])
	{
		res.clear();
		go(i);
		ans.emplace_back(res);
	}
	for (auto i : ans)
	{
		int lst = i.back();
		for (int j : i)
		{
			if (notp[a[j] + a[lst]])
			{
				puts("Impossible");
				return 0;
			}
			lst = j;
		}
	}
	cout << ans.size() << endl;
	for (auto i : ans)
	{
		cout << i.size() ;for (int j : i) cout << ' ' << j;
		cout << '\n';
	}
	return 0;
}
