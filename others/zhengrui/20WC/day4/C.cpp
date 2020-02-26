/*
	Problem:	C.cpp
	Time:		2020-02-25 23:37
	Author:		CraZYali
	E-Mail:		yms-chenziyang@outlook.com 
*/

#define REP(i, s, e) for (register int i(s), end_##i(e); i <= end_##i; i++)
#define DEP(i, s, e) for (register int i(s), end_##i(e); i >= end_##i; i--)
#define DEBUG fprintf(stderr, "Passing [%s] in Line %d\n", __FUNCTION__, __LINE__)

#define chkmax(a, b) (a < (b) ? a = (b) : a)
#define chkmin(a, b) (a > (b) ? a = (b) : a)

#include <cstring>
#include <queue>
#include <iostream>
#include <cstdio>

using namespace std;
const int inf = 1e9;
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

namespace run
{
	const int maxn = 45;
	char mp[maxn][maxn];
	int n, m, a, b, c;
	namespace Graph
	{
		const int N = 44 * 44 * 4;

		int bg[N], to[N << 5], ne[N << 5], w[N << 5], e = 1;
		inline void add(int x, int y, int z)
		{
			e++;
			to[e] = y;
			ne[e] = bg[x];
			bg[x] = e;
			w[e] = z;
		}
		int S, T;
		inline void init(int n)
		{
			S = n + 1;
			T = n + 2;
			REP(i, 1, T) bg[i] = 0;
			e = 1;
		}
		inline void adds(int x, int y, int z)
		{
			add(x, y, z);
			add(y, x, 0);
		}
		int dis[N], cur[N];
		inline void ax(int x, int a)
		{
			adds(S, x, a);
		}
		inline void a1_x(int x, int a)
		{
			adds(x, T, a);
		}
		inline void a1_xy(int x, int y, int a)
		{
			adds(x, y, a);
		}
		int q[N], head, tail;
		inline bool bfs()
		{
			REP(i, 1, T) dis[i] = -1;
			dis[T] = 1;
			q[head = tail = 0] = T;
			while (head <= tail)
			{
				int x = q[head++];
				for (int i = bg[x]; i; i = ne[i])
					if (w[i ^ 1] && dis[to[i]] == -1) dis[q[++tail] = to[i]] = dis[x] + 1;
			}
			return dis[S] != -1;
		}
		int dfs(int x, int y)
		{
			if (x == T || !y) return y;
			int res = 0;
			for (int &i = cur[x]; i; i = ne[i])
				if (dis[to[i]] == dis[x] - 1 && w[i] > 0)
				{
					int tmp = dfs(to[i], min(y, w[i]));
					if (tmp > 0)
					{
						res += tmp;
						w[i] -= tmp;
						w[i ^ 1] += tmp;
						y -= tmp;
						if (!y) break;
					}
				}
			return res;
		}
		inline int dinic()
		{
			int ans = 0;
			while (bfs())
			{
				copy(bg, bg + 1 + T, cur);
				int tmp = dfs(S, inf);
				while (tmp)
				{
					ans += tmp;
					tmp = dfs(S, inf);
				}
			}
			return ans;
		}
	}
	int bh[maxn][maxn], _bv[maxn][maxn], wv[maxn][maxn], _wh[maxn][maxn];
	inline void work()
	{
		n = read<int>();
		m = read<int>();
		a = read<int>();
		b = read<int>();
		c = read<int>();
		REP(i, 1, n) scanf("%s", mp[i] + 1);
		int t = 0;
		REP(i, 1, n)
			REP(j, 1, m)
			{
				bh[i][j] = ++t;
				wv[i][j] = ++t;
				_wh[i][j] = ++t;
				_bv[i][j] = ++t;
			}
		Graph::init(t);
		REP(i, 1, n) REP(j, 1, m)
		{
			Graph :: ax(bh[i][j], a);
			Graph :: ax(wv[i][j], a);
			Graph :: a1_x(_bv[i][j], a);
			Graph :: a1_x(_wh[i][j], a);

			if (j < m)
			{
				Graph :: a1_xy(bh[i][j + 1], bh[i][j], b);
				Graph :: a1_xy(_wh[i][j], _wh[i][j + 1], b);
			}
			else
			{
				Graph :: ax(bh[i][j], b);
				Graph :: a1_x(_wh[i][j], b);
			}

			if (i < n)
			{
				Graph :: a1_xy(wv[i + 1][j], wv[i][j], b);
				Graph :: a1_xy(_bv[i][j], _bv[i + 1][j], b);
			}
			else
			{
				Graph :: ax(wv[i][j], b);
				Graph :: a1_x(_bv[i][j], b);
			}
		}

		REP(i, 1, n) REP(j, 1, m)
			if (mp[i][j] == '#')
			{
				Graph :: ax(wv[i][j], inf);
				Graph :: a1_x(_wh[i][j], inf);
				Graph :: a1_xy(bh[i][j], _bv[i][j], c);
			}
			else
			{
				Graph :: a1_xy(wv[i][j], bh[i][j], c);
				Graph :: a1_xy(_bv[i][j], _wh[i][j], c);
				Graph :: a1_xy(_bv[i][j], bh[i][j], inf);
			}
		cout << Graph::dinic() << '\n';
		return;
	}
	signed main()
	{
		register int T = read<int>();
		while (T--) work();
		return 0;
	}
}

int main()
{
#ifdef CraZYali
	file("C");
#endif
	return run::main();
}
