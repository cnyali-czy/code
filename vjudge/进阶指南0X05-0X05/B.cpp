#define  REP(i, s, e) for (int i = s; i <= e; i++)
#define DREP(i, s, e) for (int i = s; i >= e; i--)
#define DEBUG fprintf(stderr, "Passing [%s] in Line %d\n", __FUNCTION__, __LINE__)

#define chkmax(a, b) a = max(a, b)
#define chkmin(a, b) a = min(a, b)

#include <iostream>
#include <cstring>
#include <cstdlib>
#include <algorithm>
#include <cstdio>

using namespace std;
const int maxn = 10000 + 10;

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

int n;

struct node
{
	int l, r, s, order, val;
	node() {}
	node(int _val) : val(_val), order(rand()), s(1), l(0), r(0) {}
}t[maxn];

int root, cur;
int newnode(int val) {t[++cur] = node(val);return cur;}
void maintain(int x) {t[x].s = t[t[x].l].s + t[t[x].r].s + 1;}
void merge(int &x, int a, int b)
{
	if (!(a * b)) x = a + b;
	else
	{
		if (t[a].order > t[b].order) merge(t[x = a].r, t[a].r, b);
		else merge(t[x = b].l, a, t[b].l);
		maintain(x);
	}
}
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
void insert(int val)
{
	int x(0), y(0), z(newnode(val));
	split(root, x, y, val);
	merge(x, x, z);
	merge(root, x, y);
}
int kth(int k)
{
	int now = root;
	while (t[t[now].l].s + 1 != k)
		if (t[t[now].l].s >= k) now = t[now].l;
		else k -= t[t[now].l].s + 1, now = t[now].r;
	return t[now].val;
}
int ans[maxn];

int main()
{
#ifdef CraZYali
	freopen("B.in", "r", stdin);
	freopen("B.out", "w", stdout);
#endif
	srand((unsigned long long) new char);
	register int Cases = read<int>();
	while (Cases --> 0)
	{
		root = cur = 0;
		int now = read<int>();
		printf("%d %d\n", now, (n = read<int>()) + 1 >> 1);
		int cnt = 0;
		REP(i, 1, n)
		{
			insert(read<int>());
			if (i & 1)
			{
				printf("%d", kth(i + 1 >> 1));
				++cnt;
				if (i == n || i == n - 1) putchar(10);
				else if (cnt == 10) putchar(10), cnt = 0;
				else putchar(' ');
			}
		}
	}
	return 0;
}
