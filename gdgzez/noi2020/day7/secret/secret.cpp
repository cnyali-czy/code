#define REP(i, s, e) for (register int i = (s), end_##i = (e); i <= end_##i; i++)
#define DEP(i, s, e) for (register int i = (s), end_##i = (e); i >= end_##i; i--)
#define DEBUG fprintf(stderr, "Passing [%s] in Line %d\n", __FUNCTION__, __LINE__)

#define chkmax(a, b) (a < (b) ? a = (b) : a)
#define chkmin(a, b) (a > (b) ? a = (b) : a)

#include <algorithm>
#include <iostream>
#include <cassert>
#include <cstring>
#include <cstdlib>
#include <cstdio>
#include <vector>
#include <cmath>

using namespace std;
const int maxn = 1e6;
const double eps = 1e-8, inf = 1e9;

int bg[maxn], ne[maxn], to[maxn], e = 1, cur[maxn];
double w[maxn];
inline void add(int x, int y, double z)
{
	e++;
	to[e] = y;
	ne[e] = bg[x];
	bg[x] = e;
	w[e] = z;
}
inline void Add(int x, int y, double z)
{
	add(x, y, z);
	add(y, x, 0);
}

template <typename T> T read()
{
	T ans(0), flag(1);
	char c(getchar());
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

void file(string s)
{
	freopen((s + ".in").c_str(), "r", stdin);
	freopen((s + ".out").c_str(), "w", stdout);
}

int n, m = 10, k, N, S, T;
double f[maxn];
inline double Read() {double x;scanf("%lf", &x);return x;}

int q[maxn], head, tail, dis[maxn];
bool bfs()
{
	REP(i, 1, N) dis[i] = -1;
	dis[q[head = tail = 0] = T] = 0;
	while (head <= tail)
	{
		int x = q[head++];
		for (int i = bg[x]; i; i = ne[i])
			if (dis[to[i]] == -1 && w[i ^ 1] > eps)
				dis[q[++tail] = to[i]] = dis[x] + 1;
	}
	return dis[S] != -1;
}
double dfs(int x, double y)
{
	if (x == T || y < eps) return y;
	double res = 0;
	for (int &i = cur[x]; i; i = ne[i])
		if (dis[to[i]] == dis[x] - 1 && w[i] > eps)
		{
			double tmp = dfs(to[i], min(y, w[i]));
			if (tmp > eps)
			{
				res += tmp;
				w[i] -= tmp;
				w[i ^ 1] += tmp;
				y -= tmp;
				if (y < eps) break;
			}
		}
	return res;
}

int main()
{
#ifdef CraZYali
	file("secret");
#endif
	n = read<int>();k = read<int>();
	S = n * m + 1;
	T = n * m + 2;
	N = n * m + 2;
	REP(i, 1, m)
	{
		read<int>();
		scanf("%lf", f + i);
		f[i] = log(f[i]);
	}
	REP(i, 0, n - 1)
	{
		REP(j, 1, m)
		{
			int id = i * m + j;
			Add(S, id, log(Read()));
		}
		REP(j, 1, m)
		{
			int id = i * m + j;
			Add(id, T, log(Read()));
		}
	}
	while (k--)
	{
		int x(read<int>()), y(read<int>()), z(read<int>());
		int u = (x - 1) * m + z;
		int v = (y - 1) * m + z;
		Add(u, v, f[z]);Add(v, u, f[z]);
	}
	double ans = 0;
	while (bfs())
	{
		copy(bg + 1, bg + 1 + N, cur + 1);
		double tmp = dfs(S, inf);
		while (tmp > eps)
		{
			ans += tmp;
			tmp = dfs(S, inf);
		}
	}
	printf("%.10lf\n", exp(ans));
	return 0;
}
