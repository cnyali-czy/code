/*
 * File Name:	C.cpp
 * Author	:	CraZYali
 * Time		:	2020.02.08 15:59
 * Email	:	yms-chenziyang@outlook.com
 */

#define DEP(i, s, e) for (register int i(s), end_##i(e); i >= end_##i; i--)
#define REP(i, s, e) for (register int i(s), end_##i(e); i <= end_##i; i++)
#define DEBUG fprintf(stderr, "Passing [%s] in Line %d\n", __FUNCTION__, __LINE__)

#define chkmax(a, b) (a < (b) ? a = (b) : a) 
#define chkmin(a, b) (a > (b) ? a = (b) : a) 

#include <queue>
#include <iostream>
#include <cstdio>

using namespace std;
const int maxn = 150 + 10, maxm = 1e6;

int bg[maxn], ne[maxm], to[maxm], w[maxm], cost[maxm], e = 1;
void add(int x, int y, int z, int c)
{
	e++;
	to[e] = y;
	ne[e] = bg[x];
	bg[x] = e;
	w[e] = z;
	cost[e] = c;
}
void Add(int x, int y, int z, int c)
{
	add(x, y, z, c);
	add(y, x, 0, -c);
}

template <typename T> inline T read()
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

#define file(FILE_NAME) freopen(FILE_NAME".in", "r", stdin), freopen(FILE_NAME".out", "w", stdout);

int n, m, S, T, N;
long long ans;

int dis[maxn], Max[maxn], frm[maxn];
bool vis[maxn];
queue <int> q;
bool spfa()
{
	REP(i, 1, N) vis[i] = 0, dis[i] = 1e9;
	dis[S] = 0;
	Max[S] = 1e9;
	q.emplace(S);
	while (!q.empty())
	{
		int x = q.front();q.pop();
		vis[x] = 0;
		for (int i = bg[x]; i; i = ne[i])
			if (w[i] > 0 && dis[to[i]] > dis[x] + cost[i])
			{
				dis[to[i]] = dis[x] + cost[i];
				Max[to[i]] = min(w[i], Max[x]);
				frm[to[i]] = i;
				if (!vis[to[i]])
				{
					vis[to[i]] = 1;
					q.emplace(to[i]);
				}
			}
	}
	return dis[T] < 1e9;
}
void update()
{
	ans += 1ll * dis[T] * Max[T];
	int x = T;
	while (x ^ S)
	{
		w[frm[x]] -= Max[T];
		w[frm[x] ^ 1] += Max[T];
		x = to[frm[x] ^ 1];
	}
}
int fa[maxn], A[maxn], B[maxn];
int cnt[maxn];

int main()
{
#ifdef CraZYali
	file("C");
#endif
	n = read<int>();
	m = read<int>();
	S = n + 1;
	T = N = n + 2;
	REP(i, 2, n)
		fa[i] = read<int>(), A[i] = read<int>(), B[i] = read<int>();
	long long res = 0;
	REP(i, 1, m)
	{
		int s(read<int>()), t(read<int>()), v(read<int>());
		Add(S, t, 1, 0);
		Add(s, T, 1, 0);
		Add(t, s, 1, v);
		res += v;
		for (; t ^ s; t = fa[t]) cnt[t]++;
	}
	REP(i, 2, n)
		REP(j, 1, cnt[i]) Add(i, fa[i], 1, A[i] * (j + j - 1) + B[i]);
	while (spfa()) update();
	cout << res - ans << endl;
	return 0;
}
