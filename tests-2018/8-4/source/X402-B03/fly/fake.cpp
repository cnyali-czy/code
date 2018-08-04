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

const int maxn = 2e5 + 10, maxm = 30;
const long long inf = 1ll << 40ll;

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
long long a[maxn], d[maxn], D;

bool is[maxn];
int im[100];

long long dis[60][maxn];

priority_queue <pair<long long, int> > q;

inline void dij(int root, int cnt)
{
	REP(i, 1, n) dis[cnt][i] = inf;
	dis[cnt][root] = 0;
	q.push(make_pair(0, root));
	while (!q.empty())
	{
		register int dist = -q.top().first;
		register int x = q.top().second;
		q.pop();
		if (dist > dis[cnt][x]) continue;
		for (register int i = bg[x]; i ; i = ne[i])
			if (dis[cnt][to[i]] > dist + w[i])
			{
				dis[cnt][to[i]] = dist + w[i];
				q.push(make_pair(-dis[cnt][to[i]], to[i]));
			}
	}
}

int x, y;
long long z;

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
		D += a[i] = read<long long>();
		d[i] = d[i - 1] + a[i];
	}
	while (m --> 0)
	{
		is[x = read<int>()] = 1;
		is[y = read<int>()] = 1;
		z = read<long long>();
		add(x, y, z);
		add(y, x, z);
	}
	register int cnt = 0;
	REP(i, 1, n) if (is[i]) im[++cnt] = i;
	REP(i, 1, cnt)
		REP(j, i + 1, cnt)
		{
			x = im[i];
			y = im[j];
			add(x, y, c_dis(x, y));
			add(y, x, c_dis(x, y));
		}
	REP(i, 1, cnt) dij(im[i], i);

	register int q = read<int>();
	while (q --> 0)
	{
		register int u = read<int>();
		register int v = read<int>();
		long long ans = c_dis(u, v);
		REP(i, 1, cnt)
		{
			x = im[i];
			REP(j, 1, cnt)
			if (i ^ j)
			{
				y = im[j];
				chkmin(ans, c_dis(x, u) + dis[i][y] + c_dis(y, v));
			}
		}
		printf("%lld\n", ans);
	}
	/*
	int cnt(0);
	REP(i, 1, n)
		if (is[i])
		{
			im[++cnt] = i;
			dij(i, cnt);
		}
	register int q = read<int>();
	while (q --> 0)
	{
		register int u = read<int>();
		register int v = read<int>();
		long long ans = inf;
		REP(i, 1, cnt)
		{
			x = max(im[i], u);
			y = min(im[i], u); 
			chkmin(ans, min(d[x - 1] - d[y - 1], D - (d[x - 1] - d[y - 1])) + dis[i][v]);
		}
		printf("%lld\n", ans);
	}*/
	return 0;
}
