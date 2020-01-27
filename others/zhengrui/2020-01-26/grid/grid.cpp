/*
 * File Name:	grid.cpp
 * Author	:	CraZYali
 * Time		:	2020.01.26 10:35
 * Email	:	yms-chenziyang@outlook.com
 */

#define DEP(i, s, e) for (register int i(s), end_##i(e); i >= end_##i; i--)
#define REP(i, s, e) for (register int i(s), end_##i(e); i <= end_##i; i++)
#define DEBUG fprintf(stderr, "Passing [%s] in Line %d\n", __FUNCTION__, __LINE__)

#define chkmax(a, b) (a < (b) ? a = (b) : a) 
#define chkmin(a, b) (a > (b) ? a = (b) : a) 

#include <set>
#include <map>
#include <iostream>
#include <cstdio>

using namespace std;

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

int q, T;
const int d[][2] = {{1, 0}, {-1, 0}, {0, 1}, {0, -1}};
namespace bf
{
	const int maxn = 200 + 5;
	bool vis[maxn][maxn], del[maxn][maxn];
	int ans;

	pair <int, int> q[maxn * maxn];
	int head, tail;

	int main()
	{
		while (::q--)
		{
			int x(read<int>() ^ (T * ans)), y(read<int>() ^ (T * ans));
			x += 100;y += 100;
			del[x][y] = 1;
			ans = 0;
			REP(i, 0, 200) REP(j, 0, 200) vis[i][j] = 0;
			REP(i, 0, 200) REP(j, 0, 200) if (!vis[i][j] && !del[i][j])
			{
				ans++;
				vis[i][j] = 1;
				q[head = tail = 0] = make_pair(i, j);
				while (head <= tail)
				{
					int x = q[head].first, y = q[head].second;
					head++;
					REP(i, 0, 3)
					{
						int tx = x + d[i][0], ty = y + d[i][1];
						if (tx < 0 || tx > 200 || ty < 0 || ty > 200 || vis[tx][ty] || del[tx][ty]) continue;
						vis[tx][ty] = 1;
						q[++tail] = make_pair(tx, ty);
					}
				}
			}
			printf("%d\n", ans);
		}
		return 0;
	}
}

namespace cheat
{
	const int maxn = 1500 + 5, maxq = 1e5 + 10;
	bool vis[maxn][maxn], del[maxn][maxn];
	int ans, id[maxn][maxn];
	int fa[maxn * maxn];
	int find(int x) {return fa[x] == x ? fa[x] : fa[x] = find(fa[x]);}
	void uni(int x, int y)
	{
		x = find(x);y = find(y);
		if (x == y) return;
		fa[x] = y;
		ans--;
	}
	pair <int, int> q[maxn * maxn];
	int head, tail;
	int x[maxq], y[maxq], res[maxq];
	int main()
	{
		REP(i, 1, ::q)
		{
			x[i] = read<int>() + 501;
			y[i] = read<int>() + 501;
			del[x[i]][y[i]] = 1;
		}
		int N(0);
		REP(i, 1, 1001)
			REP(j, 1, 1001)
			{
				id[i][j] = ++N;
				fa[N] = N;
			}
		ans = N;
		REP(i, 1, 1001)
			REP(j, 1, 1001) 
			if (del[i][j]) ans--;
			else if (!vis[i][j])
			{
				vis[i][j] = 1;
				q[head = tail = 0] = make_pair(i, j);
				while (head <= tail)
				{
					int x = q[head].first, y = q[head].second;
					uni(id[x][y], id[i][j]);
					head++;
					REP(i, 0, 3)
					{
						int tx = x + d[i][0], ty = y + d[i][1];
						if (tx < 1 || tx > 1001 || ty < 1 || ty > 1001 || vis[tx][ty] || del[tx][ty]) continue;
						vis[tx][ty] = 1;
						q[++tail] = make_pair(tx, ty);
					}
				}
			}
		DEP(i, ::q, 1)
		{
			res[i] = ans;
			int x = cheat::x[i], y = cheat::y[i], u = id[x][y];
			del[x][y] = 0;
			ans++;
			if (x > 1 && !del[x-1][y])		uni(u, id[x-1][y]);
			if (x < 1001 && !del[x+1][y])	uni(u, id[x+1][y]);
			if (y > 1 && !del[x][y-1])		uni(u, id[x][y-1]);
			if (y < 1001 && !del[x][y+1])	uni(u, id[x][y+1]);
		}
		REP(i, 1, ::q) printf("%d\n", res[i]);
		return 0;
	}
}
namespace shit
{
	const int maxn = 1e6 + 10;
	int fa[maxn], F, ans, V, E;
	int find(int x) {return fa[x] == x ? fa[x] : fa[x] = find(fa[x]);}
	struct __init__
	{
		__init__()
		{
			REP(i, 0, maxn - 10) fa[i] = i;
		}
	}__INIT__;
	inline void uni(int x, int y)
	{
		x = find(x);y = find(y);
		if (x == y) return;
		fa[x] = y;
		F--;
	}
	int cur;
	map <pair <int, int>, int> id;
	set <pair <int, int> > del;
	inline void uni(int x1, int y1, int x2, int y2)
	{
		const pair <int, int> u(x1, y1), v(x2, y2);
		if (!id[u]) id[u] = ++cur;
		if (!id[v]) id[v] = ++cur;
		uni(id[u], id[v]);
	}
	int main()
	{
		while (q--)
		{
			int x = read<int>() ^ (T * ans);
			int y = read<int>() ^ (T * ans);
			REP(i, 0, 3)
			{
				int X = x + d[i][0], Y = y + d[i][1];
				if (del.find(make_pair(X, Y)) != del.end()) continue;
				E--;
				if (X > x) uni(X, y, X, y + 1);
				if (X < x) uni(x, y, x, y + 1);
				if (Y > y) uni(x, Y, x + 1, Y);
				if (Y < y) uni(x, y, x + 1, y);
			}
			V--;
			del.emplace(x, y);
			printf("%d\n", ans = V + F - E + 1);
		}
		return 0;
	}
}

int main()
{
#ifdef CraZYali
	file("grid");
#endif
	cin >> q >> T;
	return shit::main();
	if (!T) return cheat::main();
	else return bf::main();
	return 0;
}
