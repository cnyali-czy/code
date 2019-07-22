#define REP(i, s, e) for (int i = s; i <= e ; i++)
#define DEBUG fprintf(stderr, "Passing [%s] in Line %d\n", __FUNCTION__, __LINE__) 

#include <bits/stdc++.h>
using namespace std;
const int maxn = 10000 + 10, maxm = 200000 + 10, maxw = 1000000 + 10;;

struct Edge
{
	int x, y, dist, value;
	Edge(){}
	Edge(int _x, int _y, int _dist, int _value) : x(_x), y(_y), dist(_dist), value(_value) {}
}E[maxm];
bool cmp(Edge A, Edge B) {return A.dist < B.dist;}
int m, n, cnt;
double tot;

int vis[maxw], End[maxw];
int fa[maxn], siz[maxn];
int find(int x)
{
	return fa[x] == x ? x : find(fa[x]);
}
void uni(int x, int y)
{
	x = find(x);y = find(y);
	siz[fa[x] = y] += siz[x];
}
void split(int x)
{
	if (x != fa[x]) siz[find(x)] -= siz[x];
	fa[x] = x;
}
void Kruskal()
{
	REP(i, 1, n) fa[i] = i, siz[i] = 1;
	REP(i, 1, m)
	{
		int x = find(E[i].x), y = find(E[i].y);
		if (x ^ y)
		{
			uni(x, y);
			vis[E[i].dist]++;
		}
	}
}
bool pick[maxm];
void calc()
{
	cnt++;
	REP(i, 1, m) tot += E[i].value * pick[i];
}
void dfs(int x, int cur = 0)
{
	if (x == m) calc();
	else
	{
		x++;
		if (!vis[E[x].dist]) dfs(x, 0);
		else
		{
			int u, v;
			bool flag = (u = find(E[x].x)) != (v = find(E[x].y));
			if (siz[u] > siz[v]) swap(u, v);
			if (cur + (End[E[x].dist] - x + flag) < vis[E[x].dist]) return;
			if (x == End[E[x].dist])
				if (cur == vis[E[x].dist]) dfs(x, 0);
				else if (flag && cur + 1 == vis[E[x].dist])
				{
					uni(u, v);
					pick[x] = 1;
					dfs(x, 0);
					pick[x] = 0;
					split(u);
				}
				else return;
			else
			{
				if (flag)
				{
					uni(u, v);
					pick[x] = 1;
					dfs(x, cur + 1);
					pick[x] = 0;
					split(u);
				}
				pick[x] = 0;
				dfs(x, cur);
			}
		}
	}
}

int main()
{
#ifndef ONLINE_JUDGE
	freopen("B.in", "r", stdin);
	freopen("B.out", "w", stdout);
#endif
	cin >> n >> m;
	REP(i, 1, m)
	{
		int x, y, dist, value;
		scanf("%d%d%d%d", &x, &y, &dist, &value);
		E[i] = Edge(x, y, dist, value);
	}
	sort(E + 1, E + 1 + m, cmp);
	REP(i, 1, m) End[E[i].dist] = i;
	Kruskal();
	REP(i, 1, n) fa[i] = i, siz[i] = 1;
	dfs(0);
	printf("%.5lf", tot / cnt);
	return 0;
}
