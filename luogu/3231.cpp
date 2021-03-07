/*
	Problem:	3231.cpp
	Time:		2021-03-05 15:37
	Author:		CraZYali
	E-Mail:		yms-chenziyang@outlook.com 
*/

#define REP(i, s, e) for (register int i(s), end_##i(e); i <= end_##i; i++)
#define DEP(i, s, e) for (register int i(s), end_##i(e); i >= end_##i; i--)
#define DEBUG fprintf(stderr, "Passing [%s] in Line %d\n", __FUNCTION__, __LINE__)

#define chkmax(a, b) (a < (b) ? a = (b) : a)
#define chkmin(a, b) (a > (b) ? a = (b) : a)

#include <iostream>
#include <cstdio>

using namespace std;
const int maxn = 3e4 + 10;

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

int a, b, c;
int m, pa[maxn], pb[maxn], pc[maxn];

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
void clear()
{
	REP(i, 1, N) bg[i] = 0;e = 1;
}
bool oked[maxn];
void build()
{
	clear();
	S = b + c + 1;N = T = b + c + 2;
	REP(i, 1, b) Add(S, i, 1);
	REP(i, 1, c) Add(i + b, T, 1);
	REP(i, 1, m) if (!oked[i])
		Add(pb[i] + 1, pc[i] + b + 1, 1);
}
int dis[maxn];
bool bfs()
{
	static int que[maxn], head, tail;
	REP(i, 1, N) dis[i] = -1;
	dis[que[head = tail = 0] = T] = 0;
	while (head <= tail)
	{
		int x = que[head++];
		for (int i = bg[x]; i; i = ne[i]) if (dis[to[i]] == -1 && w[i ^ 1] > 0)
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
	for (int &i = cur[x]; i; i = ne[i])
		if (dis[to[i]] == dis[x] - 1 && w[i] > 0)
		{
			int tmp = dfs(to[i], min(w[i], y));
			if (tmp > 0)
			{
				w[i] -= tmp;
				w[i ^ 1] += tmp;
				y -= tmp;
				res += tmp;
				if (!y) break;
			}
		}
	return res;
}

void work()
{
	a = read<int>();b = read<int>();c = read<int>();
	m = 0;
	REP(i, 0, a - 1) REP(j, 0, b - 1) REP(k, 0, c - 1) if (read<int>())
	{
		++m;
		pa[m] = i;pb[m] = j;pc[m] = k;
	}
	if (a > b) swap(a, b), swap(pa, pb);
	if (a > c) swap(a, c), swap(pa, pc);
	int ans = 666;
	REP(s, 0, (1 << a) - 1)
	{
		int res = 0;
		REP(i, 0, a - 1) if (s >> i & 1) res++;
		REP(i, 1, m) oked[i] = (s >> pa[i] & 1);
		build();
		int flow = 0;
		while (bfs())
			copy(bg, bg + 1 + N, cur), flow += dfs();
		res += flow;
		ans = min(ans, res);
	}
	cout << ans << endl;
}

int main()
{
#ifdef CraZYali
	file("3231");
#endif
	register int T = read<int>();
	while (T--) work();
	return 0;
}
