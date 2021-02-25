#define REP(i, s, e) for (register int i(s), end_##i(e); i <= end_##i; i++)

#include <vector>
#include <iostream>
#include <cstdio>

using namespace std;
const int maxn = 2e5 + 10, inf = 1e9;

int read()
{
	char c = getchar();
	while (!isdigit(c)) c = getchar();
	int res = 0;
	while (isdigit(c)) res = res * 10 + (c - 48), c = getchar();
	return res;
}

int n, m, q;

int dis[maxn];
int que[maxn], head, tail;
vector <int> G[maxn];
int s[maxn];

int Min[maxn << 2];
#define ls p << 1
#define rs p << 1 | 1
#define lson ls, l, mid
#define rson rs, mid + 1, r
#define mid (l + r >> 1)
void build(int p, int l, int r)
{
	if (l == r) Min[p] = dis[s[l]] + l - 1;
	else
	{
		build(lson);
		build(rson);
		Min[p] = min(Min[ls], Min[rs]);
	}
}
void fix(int p, int l, int r, int pos)
{
	if (l == r) Min[p] = dis[s[l]] + l - 1;
	else
	{
		if (pos <= mid) fix(lson, pos);
		else fix(rson, pos);
		Min[p] = min(Min[ls], Min[rs]);
	}
}

int main()
{
#ifdef CraZYali
	freopen("D.in", "r", stdin);
	freopen("D.out", "w", stdout);
#endif
	cin >> n >> m >> q;
	while (m--)
	{
		int x = read(), y = read();
		G[y].emplace_back(x);
	}
	REP(i, 1, n) dis[i] = inf;
	dis[que[head = tail = 0] = n] = 0;
	while (head <= tail)
	{
		int x = que[head++];
		for (int y : G[x]) if (dis[y] > dis[x] + 1)
		{
			dis[y] = dis[x] + 1;
			que[++tail] = y;
		}
	}
	REP(i, 1, n) s[i] = read();
	build(1, 1, n);
	REP(Case, 1, q)
	{
		int x = read(), y = read();
		swap(s[x], s[y]);
		fix(1, 1, n, x);fix(1, 1, n, y);
		printf("%d", Min[1]);if (Case < q) putchar(10);
	}
	return 0;
}
