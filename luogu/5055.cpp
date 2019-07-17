#define REP(i, s, e) for (int i = s; i <= e; i++)

#include <bits/stdc++.h>

using namespace std;
const int maxn = 2e5 + 10, maxnode = 20050000;

struct node
{
	int l, r, s, order, tag;
	long long sum, val;
	node() : l(0), r(0), s(0), sum(0){}
	node(long long _val) : l(0), r(0), s(1), val(_val), sum(_val), order(rand()) {}
}t[maxnode];
int cur;
int newnode(long long val)
{
	t[++cur] = node(val);
	return cur;
}
int copy(int x)
{
	t[++cur] = t[x];
	return cur;
}
int root[maxn];
void pushup(int x)
{
	t[x].s = t[t[x].l].s + t[t[x].r].s + 1;
	t[x].sum = t[t[x].l].sum + t[t[x].r].sum + t[x].val;
}
void work(int x)
{
	if (!x) return;
	t[x].tag ^= 1;
	swap(t[x].l, t[x].r);
}
void pushdown(int x)
{
	if (t[x].tag)
	{
		if (t[x].l) t[x].l = copy(t[x].l), work(t[x].l);
		if (t[x].r) t[x].r = copy(t[x].r), work(t[x].r);
		t[x].tag = 0;
	}
}
void merge(int &x, int a, int b)
{
	if (!a || !b) x = a + b;
	else
	{
		if (t[a].order > t[b].order)
		{
			pushdown(b);
			merge(t[x = b].l, a, t[b].l);
		}
		else
		{
			pushdown(a);
			merge(t[x = a].r, t[a].r, b);
		}
		pushup(x);
	}
}
void split(int x, int &a, int &b, int k)
{
	if (!x) a = b = 0;
	else
	{
		pushdown(x);
		if (t[t[x].l].s >= k)
		{
			b = copy(x);
			split(t[b].l, a, t[b].l, k);
			pushup(b);
		}
		else
		{
			a = copy(x);
			split(t[a].r, t[a].r, b, k - t[t[x].l].s - 1);
			pushup(a);
		}
	}
}
void insert(int pre, int &rt, int pos, int val)
{
	int x(0), y(0);
	split(pre, x, y, pos);
	merge(x, x, newnode(val));
	merge(rt, x, y);
}
void erase(int pre, int &rt, int pos)
{
	int x(0), y(0), z(0);
	split(pre, x, y, pos);
	split(x, x, z, pos - 1);
	merge(rt, x, y);
}
void reverse(int pre, int &rt, int l, int r)
{
	int x(0), y(0), z(0);
	split(pre, x, y, l - 1);
	split(y, y, z, r - l + 1);
	work(y);
	merge(y, y, z);
	merge(rt, x, y);
}
long long query(int pre, int &rt, int l, int r)
{
	int x(0), y(0), z(0);
	split(pre, x, y, l - 1);
	split(y, y, z, r - l + 1);
	long long ans = t[y].sum;
	merge(y, y, z);
	merge(rt, x, y);
	return ans;
}
long long lastans;

signed main()
{
#ifndef ONLINE_JUDGE
	freopen("5055.in", "r", stdin);
	freopen("5055.out", "w", stdout);
#endif
	int n;
	cin >> n;
	REP(i, 1, n)
	{
		long long v, opt;
		scanf("%lld%lld", &v, &opt);
		if (opt == 1)
		{
			long long p, x;scanf("%lld%lld", &p, &x);
			p ^= lastans;x ^= lastans;
			insert(root[v], root[i], p, x);
		}
		else if (opt == 2)
		{
			long long p;scanf("%lld", &p);
			p ^= lastans;
			erase(root[v], root[i], p);
		}
		else if (opt == 3)
		{
			long long l, r;scanf("%lld%lld", &l, &r);
			l ^= lastans;r ^= lastans;
			reverse(root[v], root[i], l, r);
		}
		else
		{
			long long l, r;scanf("%lld%lld", &l, &r);
			l ^= lastans;r ^= lastans;
			printf("%lld\n", lastans = query(root[v], root[i], l, r));
		}
	}
	return 0;
}

