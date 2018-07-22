#define DREP(i, s, e) for(register int i = s; i >= e ;i--)
#define  REP(i, s, e) for(register int i = s; i <= e ;i++)

#define DEBUG fprintf(stderr, "Passing [%s] in Line %d\n", __FUNCTION__, __LINE__)
#define chkmax(a, b) a = max(a, b)
#define chkmin(a, b) a = min(a, b)

#include <algorithm>
#include <iostream>
#include <cstdlib>
#include <cstring>
#include <cstdio>
#include <bitset>
#include <vector>
#include <cmath>
#include <queue>
#include <map>
#include <set>

using namespace std;
const int maxn = 100000 + 10;

struct node {int s, v, order, l, r, tag;} t[maxn];
int t_cnt, root;

inline int newnode(int val)
{
	t[++t_cnt] = (node) {1, val, rand(), 0, 0, 0};
	return t_cnt;
}

inline void maintain(int x) {t[x].s = t[t[x].l].s + t[t[x].r].s + 1;}

inline void pushdown(int x)
{
	int &l(t[x].l), &r(t[x].r);

	if (l) t[l].tag ^= 1;
	if (r) t[r].tag ^= 1;

	t[x].tag = 0;
	swap(l, r);
}

inline void merge(int &x, int a, int b)
{
	if (!(a * b)) x = a + b;
	else
	{
		if (t[a].order >= t[b].order)
		{
			if (t[a].tag) pushdown(a);
			merge(t[x = a].r, t[a].r, b);
		}
		else
		{
			if (t[b].tag) pushdown(b);
			merge(t[x = b].l, a, t[b].l); 
		}
	}
	maintain(x);
}

inline void split(int x, int &a, int &b, int siz)
{
	if (!x) a = b = 0;
	else
	{
		if (t[x].tag) pushdown(x);
		int T = t[t[x].l].s + 1;
		if (T <= siz) split(t[a = x].r, t[x].r, b, siz - T);
		else split(t[b = x].l, a, t[x].l, siz);
		maintain(x);
	}
}

inline void insert(int val) {merge(root, root, newnode(val));}

inline void reverse(int x, int y)
{

	int a(0), b(0), c(0);
	split(root, a, b, x - 1);
	split(b, b, c, y - x + 1);
	t[b].tag ^= 1;
	merge(a, a, c);
	merge(root, a, b);

/*
	int l(0), r(0), T(0);
	split(root, l, T, x - 1);
	split(T, T, r, y - x + 1);
	t[T].tag ^= 1;
	merge(l, l, T);
	merge(root, l, r);
*/
}

inline void print(int x)
{
	if (!x) return;
	if (t[x].tag) pushdown(x);
	print(t[x].l);
	printf("%d\n", t[x].v);
	print(t[x].r);
}

int m, n, k;

int main()
{
#ifdef CraZYali
	freopen("11922.in", "r", stdin);
	freopen("11922.out", "w", stdout);
#endif
	cin >> n >> m;
	srand(n ^ m);
	REP(i, 1, n) insert(i);
	while (m --> 0)
	{
		register int l, r;
		scanf("%d%d", &l, &r);
		reverse(l, r);
	}
	print(root);

	return 0;
}
