#define DEBUG fprintf(stderr, "Passing [%s] in Line %d\n", __FUNCTION__, __LINE__)
#define REP(i, s, e) for (int i = s; i <= e ; i++)

#include <iostream>
#include <cstdio>

using namespace std;
const int maxn = 100000 + 10;

int m, n;
int root, ch[maxn][2], s[maxn], fa[maxn], val[maxn];
bool tag[maxn];

void maintain(int x)
{
	s[x] = s[ch[x][0]] + s[ch[x][1]]+ 1;
}
void work(int x) {swap(ch[x][0], ch[x][1]);tag[x] ^= 1;}
void pushdown(int x)
{
	work(ch[x][0]);
	work(ch[x][1]);
	tag[x] = 0;
}
void rotate(int x)
{
	int y = fa[x];
	bool k = (ch[y][1] == x);
	fa[ch[x][k ^ 1]] = y;
	ch[y][k] = ch[x][k ^ 1];
	ch[x][k ^ 1] = y;
	if (fa[y]) ch[fa[y]][y == ch[fa[y]][1]] = x;
	fa[x] = fa[y];
	fa[y] = x;
	maintain(y);
	maintain(x);
}
void splay(int x, int end = 0)
{
	/*
	for (int f = fa[x]; f = fa[x], f != end; rotate(x))
		if (fa[f]) rotate((ch[f][1] == x) == (ch[fa[f]][1] == f) ? f : x);
		*/
	while (fa[x] != end)
	{
		int y = fa[x];
		int z = fa[y];
		if (z != end)
			rotate((ch[z][1] == y) ^ (ch[y][1] == x) ? x : y);
		rotate(x);
	}
	if (!end) root = x;
}
int cnt;
int newnode(int _val)
{
	++cnt;
	s[cnt] = 1;
	val[cnt] = _val;
	return cnt;
}
void push_back(int _val)
{
	int u = root, f(0);
	while (u) f = u, u = ch[u][_val > val[u]];
	if (fa[u = newnode(_val)] = f) ch[f][_val > val[f]] = u;
	splay(u);
}
void output(int x)
{
	if (!x) return;
	if (tag[x]) pushdown(x);
	output(ch[x][0]);
	if (1 <= val[x] - 1 && val[x] - 1 <= n) printf("%d ", val[x]-1);
	output(ch[x][1]);
}

int kth(int k)
{
	int u = root;
	while (1)
	{
		if (tag[u]) pushdown(u);
		int x = s[ch[u][0]];
		if (x >= k) u = ch[u][0];
		else if (x + 1 == k) return u;
		else u = ch[u][1], k -= x + 1;
	}
}

void Swap(int l, int r)
{
	l = kth(l);
	r = kth(r+2);
	splay(l);splay(r, l);
	work(ch[ch[root][1]][0]);
}

int main()
{
#ifndef ONLINE_JUDGE
	freopen("luogu-3391.in", "r", stdin);
	freopen("luogu-3391.out", "w", stdout);
#endif
	cin >> n >> m;
	REP(i, 1, n+2) push_back(i);
	while (m--)
	{
		int l, r;
		scanf("%d%d", &l, &r);
		Swap(l, r);
	}
	output(root);
	return 0;
}
