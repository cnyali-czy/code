#define DREP(i, s, e) for(register int i = s; i >= e ;i--)
#define  REP(i, s, e) for(register int i = s; i <= e ;i++)

#define DEBUG fprintf(stderr, "Passing [%s] in Line %d\n", __FUNCTION__, __LINE__)
#define chkmax(a, b) a = max(a, b)
#define chkmin(a, b) a = min(a, b)

#include <bits/stdc++.h>

using namespace std;
const int maxn = 100000 + 10;

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
	int l, r, s, val, order;
	bool tag;
	node() {}
	node(int _val) : val(_val), s(1), l(0), r(0), order(rand()), tag(0) {}
};

struct fhqtreap_splay
{
	int root, cur;
	node t[maxn];
	int newnode(int val) {t[++cur] = node(val);return cur;}
	void maintain(int x) {t[x].s = t[t[x].l].s + t[t[x].r].s + 1;}
	void pushdown(int x)
	{
		t[x].tag = 0;
		int &l(t[x].l), &r(t[x].r);
		swap(l, r);
		if (l) t[l].tag ^= 1;
		if (r) t[r].tag ^= 1;
	}
	void split(int x, int& a, int& b, int siz)
	{
		if (!x) a = b = 0;
		else
		{
			if (t[x].tag) pushdown(x);
			if (t[t[x].l].s >= siz) split(t[b = x].l, a, t[x].l, siz);
			else split(t[a = x].r, t[x].r, b, siz - t[t[x].l].s - 1);
			maintain(x);
		}
	}
	void merge(int& x, int a, int b)
	{
		if (!(a * b)) x = a + b;
		else
		{
			if (t[a].order > t[b].order)
			{
				if (t[a].tag) pushdown(a);
				merge(t[x = a].r, t[a].r, b);
			}
			else
			{
				if (t[b].tag) pushdown(b);
				merge(t[x = b].l, a, t[b].l);
			}
			maintain(x);
		}
	}
	void insert(int val)
	{
		int x(newnode(val));
		merge(root, root, x);
	}
	void reverse(int S, int E)
	{
		int l(0), r(0), T(0);
		split(root, l, T, S - 1);
		split(T, T, r, E - S + 1);
		t[T].tag ^= 1;
		merge(T, T, r);
		merge(root, l, T);
	}
	void print(int x)
	{
		if (t[x].tag) pushdown(x);
		if (t[x].l) print(t[x].l);
		printf("%d ", t[x].val);
		if (t[x].r) print(t[x].r);
	}
}T;

int main()
{
#ifdef CraZYali
	freopen("3391-new.in", "r", stdin);
	freopen("3391-new.out", "w", stdout);
#endif
	srand(time(0));
	cin >> n >> m;
	REP(i, 1, n) T.insert(i);
	while (m --> 0)
	{
		register int l(read<int>()), r(read<int>());
		T.reverse(l, r);
	}
	T.print(T.root);
	return 0;
}
