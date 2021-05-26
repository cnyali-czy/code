/*
 * File Name:	F.cpp
 * Author	:	CraZYali
 * Time		:	2020.01.25 20:35
 * Email	:	yms-chenziyang@outlook.com
 */

#define DEP(i, s, e) for (register int i(s), end_##i(e); i >= end_##i; i--)
#define REP(i, s, e) for (register int i(s), end_##i(e); i <= end_##i; i++)
#define DEBUG fprintf(stderr, "Passing [%s] in Line %d\n", __FUNCTION__, __LINE__)

#define chkmax(a, b) (a < (b) ? a = (b) : a) 
#define chkmin(a, b) (a > (b) ? a = (b) : a) 

#include <algorithm>
#include <iostream>
#include <cstdio>
#include <vector>
#include <bitset>
using namespace std;
const int maxn = 1000 + 10, maxm = 2e5 + 10;

vector <int> G[maxn];

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

int n, m, u[maxm], v[maxm];

int q[maxn], head, tail;
bool vis[maxn];
void bfs(bool c[], int S)
{
	REP(i, 1, n) vis[i] = 0;
	vis[S] = c[S] = 1;
	q[head = tail = 0] = S;
	while (head <= tail)
	{
		int u = q[head++];
		for (auto v : G[u]) if (!vis[v])
		{
			vis[v] = c[v] = 1;
			q[++tail] = v;
		}
	}
}
pair <int, int> ban;
void bfs(bitset <maxn> &c, int S, int qaq = 0)
{
	vis[S] = c[S] = c[qaq] = 1;
	q[head = tail = 0] = qaq;
	while (head <= tail)
	{
		int u = q[head++];
		for (auto v : G[u])
			if (make_pair(u, v) == ban) break;
			else if (!vis[v])
			{
				vis[v] = c[v] = 1;
				q[++tail] = v;
			}
	}
}

bool c[maxn][maxn];
vector <bitset <maxn> > cp[maxn], cs[maxn];
int p[maxn];

int main()
{
#ifdef CraZYali
	file("F");
#endif
	n = read<int>();
	m = read<int>();
	REP(i, 1, m)
	{
		u[i] = read<int>();
		v[i] = read<int>();
		G[u[i]].emplace_back(v[i]);
	}
	REP(i, 1, n) bfs(c[i], i);
	REP(i, 1, n) if (G[i].size()) 
	{
		REP(j, 1, n) vis[j] = 0;
		int l = G[i].size();
		cp[i].resize(l);
		cs[i].resize(l);
		int lst = i;
		REP(j, 0, l - 1)
		{
			ban = make_pair(i, G[i][j]);
			bfs(cp[i][j], i, lst);
			lst = G[i][j];
			if (j) cp[i][j] |= cp[i][j-1];
		}
		reverse(G[i].begin(), G[i].end());
#ifdef CraZYali
		printf("start = %d\n", i);
		for (auto j : G[i]) printf("%d ", j);putchar(10);puts("");
#endif
		REP(j, 1, n) vis[j] = 0;
		lst = i;
		DEP(j, l - 1, 0)
		{
#ifdef CraZYali
			cout << i << ' ' << j << ' ' << G[i][l - j - 1] << endl;
#endif
			ban = make_pair(i, G[i][l - j - 1]);
			bfs(cs[i][j], i, lst);
			lst = G[i][l - j - 1];
			if (j < l - 1) cs[i][j] |= cs[i][j+1];
		}
#ifdef CraZYali
		reverse(G[i].begin(), G[i].end());
#endif
	}
	REP(i, 1, m)
	{
		int u = ::u[i], v = ::v[i];
		bool pback = c[v][u];
		bool pto = cp[u][p[u]][v] | cs[u][p[u]][v];
		if (pto == pback) puts("same");
		else puts("diff");
#ifdef CraZYali
		cerr << u << ' ' << v << ' ' << pback << ' ' << cp[u][p[u]][v] << ' ' << cs[u][p[u]][v] << endl;
#endif
		p[u]++;
	}
	return 0;
}
