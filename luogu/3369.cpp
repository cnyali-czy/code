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

int n, opt, x;

struct node {int s, v, order, l, r;} t[maxn];
int t_cnt, root = 1;
inline int new_node(int val)
{
	t[++t_cnt] = (node) {1, val, rand(), 0, 0};
	return t_cnt;
}

inline void maintain(int x) {t[x].s = t[t[x].l].s + t[t[x].r].s + 1;}
inline void split(int x, int &a, int &b, int val)
{
	if (!x) {a = b = 0;return;}
	if (t[x].v > val) split(t[x].l, a, t[b = x].l, val);
	else split(t[x].r, t[a = x].r, b, val);
	maintain(x);
}

inline void merge(int &x, int a, int b)
{
	if (!(a * b)) {x = a + b;return;}
	if (t[a].order >= t[b].order) merge(t[x = b].l, a, t[b].l);
	else merge(t[x = a].r, t[a].r, b);
	maintain(x);
}

inline int kth(int now, int k)
{
	while ((t[t[now].l].s + 1) ^ k)
		if (t[t[now].l].s >= k) now = t[now].l;
		else k -= t[t[now].l].s + 1, now = t[now].r;
	return t[now].v;
}

inline void insert(int val)
{
	int x(0), y(0), z(new_node(val));
	split(root, x, y, val);
	merge(x, x, z);
	merge(root, x, y);
}

inline void delet(int val)
{
	int x(0), y(0), z(0);
	split(root, x, y, val);
	split(x, x, z, val - 1);
	merge(z, t[z].l, t[z].r);
	merge(x, x, z);
	merge(root, x, y);
}

inline int _rank(int val)
{
	int x(0), y(0);
	split(root, x, y, val - 1);
	int ans = t[x].s + 1;
	merge(root, x, y);
	return ans;
}

inline int pre(int val)
{
	int x(0), y(0);
	split(root, x, y, val - 1);
	int ans = kth(x, t[x].s);
	merge(root, x, y);
	return ans;
}

inline int nxt(int val)
{
	int x(0), y(0);
	split(root, x, y, val);
	int ans = kth(y, 1);
	merge(root, x, y);
	return ans;
}

int main()
{
#ifdef CraZYali
	freopen("3369.in", "r", stdin);
	freopen("3369.out", "w", stdout);
#endif
	cin >> n;
	srand(n);
	new_node(1e9);
	t[1].s = 0;
	while (n --> 0)
	{
		scanf("%d%d", &opt, &x);
		if (opt == 1) insert(x);
		else if (opt == 2) delet(x);
		else if (opt == 3) printf("%d\n", _rank(x));
		else if (opt == 4) printf("%d\n", kth(root, x));
		else if (opt == 5) printf("%d\n", pre(x));
		else printf("%d\n", nxt(x));
	}

	return 0;
}
