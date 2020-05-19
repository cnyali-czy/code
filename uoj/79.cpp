/*
	Problem:	79.cpp
	Time:		2020-05-08 22:53
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
#include <vector>

using namespace std;
const int maxn = 500 + 5;

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

int n, m;
vector <int> G[maxn];

int fa[maxn], mat[maxn], pre[maxn], q[maxn], head, tail = -1, col[maxn];
int find(int x) {return x == fa[x] ? fa[x] : fa[x] = find(fa[x]);}
int lca(int u, int v)
{
	static int fl[maxn], Time;
	Time++;
	while (fl[u] ^ Time)
	{
		if (u) fl[u] = Time, u = find(pre[mat[u]]);
		swap(u, v);
	}
	return u;
}
void blossum(int u, int v, int t)
{
	while (find(u) != t)
	{
		pre[u] = v, v = mat[u];
		fa[u] = fa[v] = t;
		if (col[v] == 1) col[q[++tail] = v] = 2;
		u = pre[v];
	}
}
bool match(int rt)
{
	REP(i, 1, n) fa[i] = i, col[i] = 0;
	q[head = tail = 0] = rt;
	col[rt] = 2;
	while (head <= tail)
	{
		int u(q[head++]);
		for (int v : G[u])
			if (!col[v])
			{
				col[v] = 1;
				col[mat[v]] = 2;
				pre[v] = u;
				q[++tail] = mat[v];
				if (!mat[v])
				{
					while (u)
					{
						u = mat[pre[v]];
						mat[v] = pre[v];
						mat[pre[v]] = v;
						v = u;
					}
					return 1;
				}
			}
			else if (col[v] == 2)
			{
				int l = lca(u, v);
				blossum(u, v, l);
				blossum(v, u, l);
			}
	}
	return 0;
}
int main()
{
#ifdef CraZYali
	file("79");
#endif
	n = read<int>();m = read<int>();
	while (m--)
	{
		int x(read<int>()), y(read<int>());
		G[x].emplace_back(y);
		G[y].emplace_back(x);
	}
	int ans = 0;
	REP(i, 1, n) if (!mat[i] && match(i)) ans++;
	cout << ans << endl;
	REP(i, 1, n) printf("%d%c", mat[i], i == n ? '\n' : ' ');
	return 0;
}
