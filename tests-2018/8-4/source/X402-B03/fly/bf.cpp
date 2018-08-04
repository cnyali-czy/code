#define  REP(i, s, e) for(register int i = s; i <= e ;i++)
#define DREP(i, s, e) for(register int i = s; i >= e ;i--)

#define DEBUG fprintf(stderr, "Passing [%s] in LINE %d\n", __FUNCTION__, __LINE__)
#define chkmin(a, b) a = min(a, b)
#define chkmax(a, b) a = max(a, b)

#include <bits/stdc++.h>

using namespace std;

template <typename T> T read()
{
	register T ANS = 0;
	register short p(1);
	register char c = getchar_unlocked();
	while (!isdigit(c))
	{
		if (c == '-') p = -1;
		c = getchar_unlocked();
	}
	while (isdigit(c))
	{
		ANS = ANS * 10 + c - '0';
		c = getchar_unlocked();
	}
	return ANS * p;
}

const int maxn = 2e5 + 10, maxm = 30 + maxn;
const long long inf = 1ll << 50ll;

int bg[maxn], ne[maxm << 1], to[maxm << 1], e = 1;
long long w[maxm << 1];
inline void add(int x, int y, long long z)
{
	e++;
	to[e] = y;
	ne[e] = bg[x];
	bg[x] = e;
	w[e] = z;
}

int m, n, k;

long long dis[maxn];

priority_queue <pair<long long, int> > q;

inline void dij(int root)
{
	REP(i, 1, n) dis[i] = inf;
	dis[root] = 0;
	q.push(make_pair(0, root));
	while (!q.empty())
	{
		register long long dist = -q.top().first;
		register int x = q.top().second;
		q.pop();
		if (dist > dis[x]) continue;
		for (register int i = bg[x]; i ; i = ne[i])
			if (dis[to[i]] > dist + w[i]) q.push(make_pair(-(dis[to[i]] = dist + w[i]), to[i]));
	}
}

int x, y;
long long z;

long long d[maxn], D;

inline long long c_dis(int x, int y)
{
	if (x > y) swap(x, y);
	return min(d[y - 1] - d[x - 1], D - (d[y - 1] - d[x - 1]));
}

int main()
{
	freopen("fly.in", "r", stdin);
	freopen("fly.out", "w", stdout);
	n = read<int>();m = read<int>();
	REP(i, 1, n)
	{
		register long long temp = read<long long>();
		d[i] = temp + d[i - 1];
		D += temp;
		if (i < n) {add(i, i + 1, temp);add(i + 1, i, temp);}
		else add(n, 1, temp), add(1, n, temp);
	}
	bool miszero = !m;
	while (m --> 0)
	{
		x = read<int>();y = read<int>();
		z = read<long long>();
		add(x, y, z);
		add(y, x, z);
	}
	register int q = read<int>();
	while (q --> 0)
	{
		register int u = read<int>();
		register int v = read<int>();
		if (miszero) printf("%lld\n", c_dis(u, v));
		else
		{
			dij(u);
			printf("%lld\n", dis[v]);
		}
	}
	return 0;
}
