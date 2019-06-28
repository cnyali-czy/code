#define DREP(i, s, e) for(int i = s; i >= e ;i--)
#define  REP(i, s, e) for(int i = s; i <= e ;i++)

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

int n, m, k;

struct node
{
	int l, r, s, val, order;
	bool tag;
	node() : l(0), r(0), s(0), tag(0){}
	node(int _val) : val(_val), l(0), r(0), s(1), order(rand()), tag(0){}
}t[maxn];
int root, cnt;
int newnode(int val)
{
	t[++cnt] = node(val);
	return cnt;
}
void maintain(int x) {t[x].s = t[t[x].l].s + t[t[x].r].s + 1;}
void pushdown(int x)
{
	int &l = t[x].l, &r = t[x].r;
	swap(l, r);
	t[x].tag = 0;
	t[l].tag ^= 1;t[r].tag ^= 1;
}
void merge(int &x, int a, int b)
{
	if (!(a * b)) x = a + b;
	else
	{
		if (t[a].order > t[b].order)
		{
			if (t[b].tag) pushdown(b);
			merge(t[x = b].l, a, t[b].l);
		}
		else
		{
			if (t[a].tag) pushdown(a);
			merge(t[x = a].r, t[a].r, b);
		}
		maintain(x);
	}
}
void split(int x, int &a, int &b, int siz)
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
void insert(int val)
{
	int z(newnode(val));
	merge(root, root, z);
}
void output(int x = root)
{
	if (!x) return;
	if (t[x].tag) pushdown(x);
	output(t[x].l);
	printf("%d ", t[x].val);
	output(t[x].r);
}
void reverse(int l, int r)
{
	int x(0), y(0), z(0);
	split(root, x, y, l - 1);
	split(y, y, z, r - l + 1);
	t[y].tag ^= 1;
	merge(y, y, z);
	merge(root, x, y);
}

int main()
{
#ifdef CraZYali
	freopen("B.in", "r", stdin);
	freopen("B.out", "w", stdout);
#endif
	srand((unsigned long long)new char);
	cin >> n >> m;
	REP(i, 1, n) insert(i);
	while (m--)
	{
		int l(read<int>()), r(read<int>());
		reverse(l, r);
	}
	output();
	return 0;
}
