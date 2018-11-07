#define DREP(i, s, e) for(register int i = s; i >= e ;i--)
#define  REP(i, s, e) for(register int i = s; i <= e ;i++)

#define DEBUG fprintf(stderr, "Passing [%s] in Line %d\n", __FUNCTION__, __LINE__)
#define chkmax(a, b) a = max(a, b)
#define chkmin(a, b) a = min(a, b)

#include <bits/stdc++.h>

using namespace std;
const int maxn = 1e5 + 10;

template <typename T> inline T read()
{
	T ans(0), p(1);
	char c = getchar();
	while (!isdigit(c))
	{
		if (c == '-') p = -1;
		c = getchar();
	}
	while (isdigit(c))
	{
		ans = ans * 10 + c - 48;
		c = getchar();
	}
	return ans * p;
}

template <typename T> void write(T x)
{
	if (x < 0) putchar('-'), write(-x);
	else
	{
		if (x / 10) write(x / 10);
		putchar(x % 10 + '0');
	}
}

int m, n, k;

struct node
{
	int val, l, r, s, order;
	node() {}
	node(int _val) : val(_val) {l = r = 0;s = 1;order = rand();}
};

struct FHQ_TREAP
{
	node t[maxn];
	int root, cnt;
	int newnode(int val) {t[++cnt] = node(val);return cnt;}
	void maintain(int p) {t[p].s = t[t[p].l].s + t[t[p].r].s + 1;}
	void split_by_val(int x, int &a, int &b, int val)
	{
		if (!x) a = b = 0;
		else
		{
			if (t[x].val > val) split_by_val(t[b = x].l, a, t[x].l, val);
			else split_by_val(t[a = x].r, t[x].r, b, val);
			maintain(x);
		}
	}	
	void merge(int &x, int a, int b)
	{
		if (!(a * b)) x = a + b;
		else
		{
			if (t[a].order > t[b].order) merge(t[x = b].l, a, t[b].l);
			else merge(t[x = a].r, t[a].r, b);
			maintain(x);
		}
	}
	void insert(int val)
	{
		int x(0), y(0), z(newnode(val));
		split_by_val(root, x, y, val);
		merge(x, x, z);
		merge(root, x, y);
	}
	void del(int val)
	{
		int x(0), y(0), z(0);
		split_by_val(root, x, y, val);
		split_by_val(x, x, z, val - 1);
		merge(z, t[z].l, t[z].r);
		merge(x, x, z);
		merge(root, x, y);
	}
	int _rank(int val)
	{
		int x(0), y(0), ans;
		split_by_val(root, x, y, val - 1);
		ans = t[x].s + 1;
		merge(root, x, y);
		return ans;
	}
	int kth(int k, int now)
	{
		while (t[t[now].l].s + 1 != k)
			if (t[t[now].l].s >= k) now = t[now].l;
			else
			{
				k -= t[t[now].l].s + 1;
				now = t[now].r;
			}
		return t[now].val;
	}
	int pre(int val)
	{
		int x(0), y(0), ans;
		split_by_val(root, x, y, val - 1);
		ans = kth(t[x].s, x);
		merge(root, x, y);
		return ans;
	}
	int nxt(int val)
	{
		int x(0), y(0), ans;
		split_by_val(root, x, y, val);
		ans = kth(1, y);
		merge(root, x, y);
		return ans;
	}
}T;

int main()
{
#ifdef CraZYali
	freopen("3369-new.in", "r", stdin);
	freopen("3369-new.out", "w", stdout);
#endif
	srand(time(0));
	k = read<int>();
	while (k --> 0)
	{
		register int opt = read<int>(), x = read<int>();
		if (opt == 1) T.insert(x);
		else if (opt == 2) T.del(x);
		else if (opt == 3) write<int>(T._rank(x)), putchar(10);
		else if (opt == 4) write<int>(T.kth(x, T.root)), putchar(10);
		else if (opt == 5) write<int>(T.pre(x)), putchar(10);
		else write(T.nxt(x)), putchar(10);
	}
	return 0;
}
