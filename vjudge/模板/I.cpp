#define DREP(i, s, e) for(int i = s; i >= e ;i--)
#define  REP(i, s, e) for(int i = s; i <= e ;i++)

#define DEBUG fprintf(stderr, "Passing [%s] in Line %d\n", __FUNCTION__, __LINE__)
#define chkmax(a, b) a = max(a, b)
#define chkmin(a, b) a = min(a, b)

#include <bits/stdc++.h>

using namespace std;
const int maxn = 20, maxm = 1000 + 10, inf = 1e8;

int bg[maxn], ne[maxm << 1], to[maxm << 1], w[maxm << 1], e = 1;
void add(int x, int y, int z)
{
	e++;
	to[e] = y;
	ne[e] = bg[x];
	bg[x] = e;
	w[e] = z;
}

template <typename T> inline T read()
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

int n, m;

int q[maxn], head, tail, dis[maxn];
bool bfs()
{
	dis[q[head = tail = 1] = 1] = 0;
	REP(i, 2, n) dis[i] = -1;
	while (head <= tail)
	{
		int x = q[head++];
		for (int i = bg[x]; i ; i = ne[i])
			if (dis[to[i]] == -1 && w[i] > 0) dis[q[++tail] = to[i]] = dis[x] + 1;
	}
	return dis[n] != -1;
}
int dfs(int x = 1, int y = inf)
{
	if (x == n || !y) return y;
	int tot = 0;
	for (int i = bg[x]; i ; i = ne[i])
		if (dis[to[i]] == dis[x] + 1 && w[i] > 0)
		{
			int temp = dfs(to[i], min(y, w[i]));
			if (temp > 0)
			{
				y -= temp;
				w[i] -= temp;
				w[i ^ 1] += temp;
				tot += temp;
			}
		}
	return tot;
}

int main()
{
#ifdef CraZYali
	freopen("I.in", "r", stdin);
	freopen("I.out", "w", stdout);
#endif
	int Case = read<int>();
	REP(kase, 1, Case)
	{
		n = read<int>();m = read<int>();
		e = 1;
		REP(i, 1, n) bg[i] = 0;
		while (m --> 0)
		{
			int x(read<int>()), y(read<int>()), z(read<int>());
			add(x, y, z);add(y, x, 0);
		}
		int ans = 0;
		while (bfs()) ans += dfs();
		printf("Case %d: %d\n", kase, ans);
	}
	
	return 0;
}
