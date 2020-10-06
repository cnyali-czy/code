#include <bits/stdc++.h>

using namespace std;

#define p2 p << 1
#define p3 p << 1 | 1
#define pb push_back 

	template <class t>
inline void read(t & res)
{
	char ch;
	while (ch = getchar(), !isdigit(ch));
	res = ch ^ 48;
	while (ch = getchar(), isdigit(ch))
		res = res * 10 + (ch ^ 48);
}

const int e = 1e5 + 15, o = 6e7 + 5;
struct node
{
	int l, r, cnt;
}c[o];
vector<int>rt[e << 2], tot[e << 2], pos[30];
queue<int>q[e];
int n, a[e], pool, m, w, lst[e], op, ans;

inline void modify(int y, int &x, int l, int r, int s, int v)
{
	c[x = ++pool] = c[y];
	c[x].cnt += v;
	if (l == r) return;
	int mid = l + r >> 1;
	if (s <= mid) modify(c[y].l, c[x].l, l, mid, s, v);
	else modify(c[y].r, c[x].r, mid + 1, r, s, v);
}

inline int query(int x, int l, int r, int s)
{
	if (s > r) return 0;
	if (s <= l) return c[x].cnt;
	int mid = l + r >> 1;
	if (s <= mid) return c[c[x].r].cnt + query(c[x].l, l, mid, s);
	else return query(c[x].r, mid + 1, r, s); 
}

inline void solve(int l, int r, int p, int d)
{
	if (l == r) return;
	int mid = l + r >> 1, i, len = pos[d].size();
	tot[p].resize(len);
	pos[d + 1].clear();
	pos[d + 1].pb(-1);
	for (i = 1; i < len; i++)
	{
		int v = pos[d][i];
		if (a[v] <= mid) tot[p][i] = tot[p][i - 1] + 1, pos[d + 1].pb(v), lst[a[v]] = 0;
		else tot[p][i] = tot[p][i - 1];
	}
	int l2 = pos[d + 1].size();
	rt[p].resize(l2);
	for (i = 1; i < l2; i++)
	{
		int v = pos[d + 1][i], x = a[v];
		q[x].push(i);
		if (q[x].size() > w)
		{
			modify(rt[p][i - 1], rt[p][i], 1, l2 - 1, q[x].front(), -w - 1);
			if (lst[x])
				modify(rt[p][i], rt[p][i], 1, l2 - 1, lst[x], w);
			lst[x] = q[x].front();
			q[x].pop(); 
		}
		else rt[p][i] = rt[p][i - 1];
	}
	for (i = 0; i < l2; i++)
	{
		int v = pos[d + 1][i], x = a[v];
		while (!q[x].empty()) q[x].pop();
	}
	solve(l, mid, p2, d + 1);
	pos[d + 1].clear();
	pos[d + 1].pb(-1);
	for (i = 0; i < len; i++)
	{
		int v = pos[d][i];
		if (a[v] > mid) pos[d + 1].pb(v);
	}
	solve(mid + 1, r, p3, d + 1);
}

inline int getans(int l, int r, int s, int t, int v, int p)
{
	if (l == r) return l;
	int mid = l + r >> 1, ns = tot[p][s], nt = tot[p][t], l2 = rt[p].size(), sum = 0;
	sum = nt - ns + query(rt[p][nt], 1, l2 - 1, ns + 1);
	if (v <= sum) return getans(l, mid, ns, nt, v, p2);
	else return getans(mid + 1, r, s - ns, t - nt, v - sum, p3);
}

int main()
{
	freopen("A.in", "r", stdin);
	freopen("std.out", "w", stdout);
	int i, l, r, k;
	read(n); read(w); read(m); read(op);
	pos[1].resize(n + 1);
	pos[1][0] = -1;
	for (i = 1; i <= n; i++) read(a[i]), pos[1][i] = i;
	solve(0, n, 1, 1);
	int cc = 0;
	while (m--)
	{
		read(l); read(r); read(k);
		l ^= ans * op; r ^= ans * op; k ^= ans * op;
		ans = getans(0, n, l - 1, r, k, 1);
		printf("%d\n", ans);
	}
	//fclose(stdin);
	//fclose(stdout);
	return 0;
}
