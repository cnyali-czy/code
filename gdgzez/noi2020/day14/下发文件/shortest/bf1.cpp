/*
	Problem:	shortest.cpp
	Time:		2020-06-15 07:53
	Author:		CraZYali
	E-Mail:		yms-chenziyang@outlook.com 
*/

#define REP(i, s, e) for (register int i(s), end_##i(e); i <= end_##i; i++)
#define DEP(i, s, e) for (register int i(s), end_##i(e); i >= end_##i; i--)
#define DEBUG fprintf(stderr, "Passing [%s] in Line %d\n", __FUNCTION__, __LINE__)

#define chkmax(a, b) (a < (b) ? a = (b) : a)
#define chkmin(a, b) (a > (b) ? a = (b) : a)

#include <queue>
#include <iostream>
#include <cstdio>

using namespace std;
const int maxn = 3005, maxm = 3005;
const int inf = 1e9;
int bg[maxn], ne[maxm << 1], to[maxm << 1], w[maxm << 1], e = 1;
inline void add(int x, int y, int z)
{
	e++;
	to[e] = y;
	ne[e] = bg[x];
	bg[x] = e;
	w[e] = z;
}

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
		ans = ans * 10 + c - 48;
		c = getchar();
	}
	return ans * flag;
}

#define file(FILE_NAME) freopen(FILE_NAME".in", "r", stdin), freopen(FILE_NAME".out", "w", stdout)

int n, m, k;

struct Node
{
	int x, d;
	inline bool operator < (const Node &B) const {return d > B.d;}
};
priority_queue <Node> q;
int dis[maxn];bool vis[maxn];
int dij()
{
	REP(i, 1, n) dis[i] = inf, vis[i] = 0;
	while (!q.empty()) q.pop();
	dis[1] = 0;
	q.emplace(Node{1, 0});
	while (!q.empty())
	{
		auto res = q.top();q.pop();
		int x = res.x, d = res.d;
		if (vis[x]) continue;
		vis[x] = 1;
		if (x == n) return d;
		for (int i = bg[x]; i; i = ne[i])
			if (w[i] < inf && dis[to[i]] > d + w[i])
			{
				dis[to[i]] = d + w[i];
				q.emplace(Node{to[i], dis[to[i]]});
			}
	}
	return inf;
}
vector <int> qaq;

int main()
{
#ifdef CraZYali
	file("shortest1");
#endif
	n = read<int>();m = read<int>();k = read<int>();
	REP(i, 1, m)
	{
		int x(read<int>()), y(read<int>()), z(read<int>());
		add(x, y, z);add(y, x, z);
	}
	dij();
	REP(times, 1, k)
	{
		REP(x, 1, n)
			for (int i = bg[x]; i; i = ne[i]) if (w[i] < inf && dis[to[i]] == dis[x] + w[i])
			{
				int tmp = w[i];
				w[i] = w[i ^ 1] = inf;
				if (dij() < inf) {qaq.emplace_back(i >> 1);goto End;}
				else w[i] = w[i ^ 1] = tmp;
			}
End:;
	}
	cout << qaq.size() << endl;
	for (auto i : qaq) cout << i << ' ';
	return 0;
}
