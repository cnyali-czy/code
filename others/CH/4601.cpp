#define  REP(i, s, e) for (int i = s; i <= e; i++)
#define DREP(i, s, e) for (int i = s; i >= e; i--)
#define DEBUG fprintf(stderr, "Passing [%s] in Line %d\n", __FUNCTION__, __LINE__)

#define chkmax(a, b) a = max(a, b)
#define chkmin(a, b) a = min(a, b)

#include <bits/stdc++.h>

using namespace std;
const int maxn = 100000 + 10;

template <typename T> T read()
{
	T ans = 0, p = 1;
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

struct node
{
	int l, r, order, s, val;
	node(){}
	node(int _val) : val(_val), l(0), r(0), order(rand()), s(1) {}
};

struct FHQ
{
	node t[maxn];
	int root, cur;
	int newnode(int val) {t[++cur] = node(val);return cur;}
	void maintain(int x) {t[x].s = t[t[x].l].s + t[t[x].r].s + 1;}
	void split(int x, int &a, int &b, int val)
	{
		if (!x) a = b = 0;
		else
		{
			if (t[x].val > val) split(t[b = x].l, a, t[x].l, val);
			else split(t[a = x].r, t[x].r, b, val);
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
		split(root, x, y, val);
		merge(x, x, z);
		merge(root, x, y);
	}
	void del(int val)
	{
		int x(0), y(0), z(0);
		split(root, x, y, val);
		split(x, x, z, val - 1);
		merge(z, t[z].l, t[z].r);
		merge(x, x, z);
		merge(root, x, y);
	}
	int _rank(int val)
	{
		int x(0), y(0);
		split(root, x, y, val - 1);
		int ans = t[x].s + 1;
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
		int x(0), y(0);
		split(root, x, y, val - 1);
		int ans = kth(t[x].s, x);
		merge(root, x, y);
		return ans;
	}
	int nxt(int val)
	{
		int x(0), y(0);
		split(root, x, y, val);
		int ans = kth(1, y);
		merge(root, x, y);
		return ans;
	}
}T;

int main()
{
#ifdef CraZYali
	freopen("4601.in", "r", stdin);
	freopen("4601.out", "w", stdout);
#endif
	srand(time(0));
	int n = read<int>();
	REP(i, 1, n)
	{
		int opt = read<int>();
		if (opt == 1) T.insert(read<int>());
		else if (opt == 2) T.del(read<int>());
		else if (opt == 3) printf("%d\n", T._rank(read<int>()));
		else if (opt == 4) printf("%d\n", T.kth(read<int>(), T.root));
		else if (opt == 5) printf("%d\n", T.pre(read<int>()));
		else printf("%d\n", T.nxt(read<int>()));
	}
	return 0;
}
