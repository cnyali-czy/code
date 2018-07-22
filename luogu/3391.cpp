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
const int maxn = 100010;

int n, m, k;

struct node {int s, v, order, l, r, tag;}t[maxn];

int t_cnt, root;
inline int newnode(int val)
{
	t[++t_cnt] = (node){1, val, rand(), 0, 0, 0};
	return t_cnt;
}

inline void maintain(int x) {t[x].s = t[t[x].l].s + t[t[x].r].s + 1;}

inline void pushdown(int x)
{
	int &l(t[x].l), &r(t[x].r);
	swap(l, r);
	if (l) t[l].tag ^= 1;
	if (r) t[r].tag ^= 1;
	t[x].tag = 0;
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
		int temp = t[t[x].l].s + 1;
		if (siz < temp) split(t[b = x].l, a, t[x].l, siz);
		else split(t[a = x].r, t[x].r, b, siz - temp);
		maintain(x);
	}
}

inline void insert(int val)
{
	int x(0), y(0), z(newnode(val));
	merge(root, root, z);
}

inline void reverse(int x, int y)
{
	int l(0), r(0), T(0);
	split(root, l, T, x - 1);
	split(T, T, r, y - x + 1);
	t[T].tag ^= 1;merge(l, l, T);merge(root, l, r);
}

inline void print(int now)
{
	if (t[now].tag) pushdown(now);
	if (t[now].l) print(t[now].l);
	printf("%d ", t[now].v);
	if (t[now].r) print(t[now].r);
}

int main()
{
#ifdef CraZYali
	freopen("3391.in", "r", stdin);
	freopen("3391.out", "w", stdout);
#endif
	cin >> n >> m;
	srand(n ^ m ^ 19260817);
	REP(i, 1, n) insert(i);
	while (m --> 0)
	{
		register int x, y;
		scanf("%d%d", &x, &y);
		reverse(x, y);
	}
	print(root);
	return 0;
}
