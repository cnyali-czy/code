/*
 * File Name:	C.cpp
 * Author	:	CraZYali
 * Year		:	2019.11.03 19:18
 * Email	:	yms-chenziyang@outlook.com
 */

#define DREP(i, s, e) for (register int i(s), end_##i(e); i >= end_##i; i--)
#define  REP(i, s, e) for (register int i(s), end_##i(e); i <= end_##i; i++)
#define DEBUG fprintf(stderr, "Passing [%s] in Line %d\n", __FUNCTION__, __LINE__)

#define chkmax(a, b) (a < (b) ? a = (b) : a) 
#define chkmin(a, b) (a > (b) ? a = (b) : a) 

#include <iostream>
#include <cstdio>
#include <vector>

using namespace std;
const int maxn = 1000 + 10;

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

int n, m;

vector <int> G[maxn];
int deg[maxn];
inline void add(int x, int y)
{
	deg[x]++;deg[y]++;
	G[x].emplace_back(y);
	G[y].emplace_back(x);
}

vector <int> qaq[maxn];
bool Left[maxn], vis[maxn];
int match[maxn], blg[maxn];

bool dfs(int u)
{
	for (int v : qaq[u])
		if (!vis[v])
		{
			vis[v] = 1;
			if (!match[v] || dfs(match[v]))
			{
				match[v] = u;
				blg[v] = u;blg[u] = v;
				return 1;
			}
		}
	return 0;
}

bool judge(int root)
{
	cerr << root << endl;
	REP(i, 1, n)
	{
		qaq[i].clear();
		Left[i] = blg[i] = match[i] = 0;
	}
	int less = n - 1 - deg[root];
	for (int u : G[root]) Left[u] = 1;
	REP(u, 1, n) if (Left[u])
		for (int v : G[u]) if (v != root && !Left[v])
			qaq[u].emplace_back(v);
	int res(0);
	REP(i, 1, n)
	{
		REP(j, 1, n) vis[j] = 0;
		res += dfs(i);
	}
	return res == less;
}

int main()
{
#ifdef CraZYali
	file("C");
#endif
	n = read<int>();
	m = read<int>();
	while (m--) add(read<int>(), read<int>());
	REP(root, 1, n) if (deg[root] >= n / 2 && judge(root))
	{
		puts("Yes");
		REP(i, 1, n) printf("%d%c", i == root ? -1 : blg[i], i == end_i ? '\n' : ' ');
		return 0;
	}
	puts("No");
	return 0;
}
