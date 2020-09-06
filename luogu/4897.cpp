/*
	Problem:	4897.cpp
	Time:		1010-06-17 10:40
	Author:		CraZYali
	E-Mail:		yms-chenziyang@outlook.com 
*/

#define REP(i, s, e) for (register int i(s), end_##i(e); i <= end_##i; i++)
#define DEP(i, s, e) for (register int i(s), end_##i(e); i >= end_##i; i--)
#define DEBUG fprintf(stderr, "Passing [%s] in Line %d\n", __FUNCTION__, __LINE__)

#define chkmax(a, b) (a < (b) ? a = (b) : a)
#define chkmin(a, b) (a > (b) ? a = (b) : a)

#include <vector>
#include <cstdlib>
#include <iostream>
#include <cstdio>

using namespace std;
const int maxn = 500 + 5, maxm = 1500 + maxn << 1;

int bg[maxn], ne[maxm << 1], to[maxm << 1], w[maxm << 1], ww[maxm << 1], e = 1;
inline void add(int x, int y, int z)
{
	e++;
	to[e] = y;
	ne[e] = bg[x];
	bg[x] = e;
	ww[e] = z;
}
inline void Add(int x, int y, int z)
{
	add(x, y, z);
	add(y, x, z);
}

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

int n, m, dis[maxn], q[maxn], head, tail, cur[maxn], S, T;
bool bfs()
{
	REP(i, 1, n) dis[i] = -1;
	dis[T] = 0;
	q[head = tail = 0] = T;
	while (head <= tail)
	{
		int x = q[head++];
		for (int i = bg[x]; i; i = ne[i])
			if (w[i ^ 1] > 0 && dis[to[i]] == -1)
			{
				dis[to[i]] = dis[x] + 1;
				q[++tail] = to[i];
			}
	}
	return dis[S] != -1;
}
int dfs(int x, int y = 1e9)
{
	if (x == T || !y) return y;
	int res = 0;
	for (int &i = cur[x]; i; i = ne[i]) if (w[i] > 0 && dis[to[i]] == dis[x] - 1)
	{
		int tmp = dfs(to[i], min(w[i], y));
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
int Dinic()
{
	int ans = 0;
	while (bfs())
	{
		copy(bg, bg + 1 + n, cur);
		int tmp = dfs(S);
		while (tmp > 0)
		{
			ans += tmp;
			tmp = dfs(S);
		}
	}
	return ans;
}

vector <pair <int, int> > G[maxn];
bool vis[maxn];

int Rand(int l, int r) {return rand() % (r - l + 1) + l;}

void work(vector <int> Set)
{
	const int siz = Set.size();
	if (siz < 2) return;
	S = rand() % siz, T = rand() % siz;
	while (S == T) T = rand() % siz;
	S = Set[S];T = Set[T];
//	for(auto i : Set) cout <<i << ' ';
	copy(ww, ww + 1 + e, w);
	int z = Dinic();
//	cout<< " | " << S << ' ' << T << ' ' << z << endl;
	G[S].emplace_back(T, z);
	G[T].emplace_back(S, z);
	REP(i, 1, n) vis[i] = 0;

	vector <int> v1, v2;
	vis[q[head = tail = 0] = S] = 1;
	while (head <= tail)
	{
		int x = q[head++];
		for (int i = bg[x]; i; i = ne[i])
			if (w[i] > 0 && !vis[to[i]])
				vis[q[++tail] = to[i]] = 1;
	}
	for (auto i : Set) if (!vis[i]) v2.push_back(i);
	else v1.push_back(i);
//	Add(S, T, z);
//	REP(x, 1, n) for (int i = bg[x]; i; i = ne[i]) if (!w[i])
//		printf("full %d %d\n", x, to[i]);
//	printf("v1 : ");for (auto i : v1) cout << i << ' ' ;cout << endl;
//	printf("v2 : ");for (auto i : v2) cout << i << ' ' ;cout << endl;
//	cout << vis[3] << endl;
	work(v1);work(v2);
}

int Min[maxn][10], anc[maxn][10], dep[maxn];

void dfs0(int x)
{
	vis[x] = 1;
	dep[x] = dep[anc[x][0]] + 1;
	REP(i, 1, 9)
	{
		anc[x][i] = anc[anc[x][i - 1]][i - 1];
		Min[x][i] = min(Min[x][i - 1], Min[anc[x][i - 1]][i - 1]);
	}
	for (auto E : G[x])
	{
		int y = E.first, z = E.second;
		if (vis[y]) continue;
		anc[y][0] = x;
		Min[y][0] = z;
		dfs0(y);
	}
}
int lca(int x, int y)
{
	if (dep[x] < dep[y]) swap(x, y);
	DEP(i, 9, 0) if (dep[anc[x][i]] >= dep[y]) x = anc[x][i];
	if (x == y) return x;
	DEP(i, 9, 0)
		if (anc[x][i] ^ anc[y][i]) x = anc[x][i], y = anc[y][i];
	return anc[x][0];
}
int main()
{
#ifdef CraZYali
	file("4897");
#endif
	n = read<int>() + 1;m = read<int>();
    REP(i, 1, m)
	{
		int x(read<int>() + 1), y(read<int>() + 1), z(read<int>());
		Add(x, y, z);
	}
	vector <int> tmp(n);
	REP(i, 0, n - 1) tmp[i] = i + 1;
	work(tmp);
	REP(i, 1, n) vis[i] = 0;
	REP(i, 1, n) if (!vis[i]) dfs0(i);
//	REP(i, 1, n) for (auto j : G[i]) printf("%d %d %d\n", i, j.first, j.second);
//	REP(i, 1, n) REP(j, 0, 9) printf("%d%c", anc[i][j], j == end_j ? '\n' : ' ');
//	REP(i, 1, n) REP(j, 0, 9) printf("%d%c", Min[i][j], j == end_j ? '\n' : ' ');
	int q = read<int>();
	while (q--)
	{
		int x = read<int>() + 1, y = read<int>() + 1, l = lca(x, y);
		int orzhzy = 1e9;
		DEP(i, 9, 0) if (dep[anc[x][i]] >= dep[l])
		{
			chkmin(orzhzy, Min[x][i]);
			x = anc[x][i];
		}
		DEP(i, 9, 0) if (dep[anc[y][i]] >= dep[l])
		{
			chkmin(orzhzy, Min[y][i]);
			y = anc[y][i];
		}
		printf("%d\n", orzhzy);
	}
	return 0;
}
