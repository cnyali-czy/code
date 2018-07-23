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

int m, n, k;

struct fhq_treap
{
	struct node {int s, v, order, l, r, tag;} t[maxn];
	int t_cnt, root;

	inline void clear() {root = t_cnt = 0;}
	inline int newnode(int val)
	{
		t[++t_cnt] = (node) {1, val, rand(), 0, 0, 0};
		return t_cnt;
	}
	
	inline void pushdown(int x)
	{
		int &l(t[x].l), &r(t[x].r);
		swap(l, r);
		if (l) t[l].tag ^= 1;
		if (r) t[r].tag ^= 1;
		t[x].tag = 0;
	}

	inline void maintain(int x)	{t[x].s = t[t[x].l].s + t[t[x].r].s + 1;}

	inline void merge(int& x, int a, int b)
	{
		if (!(a * b)) x = a + b;
		else
		{
			if (t[a].order >= t[b].order)
			{
				if (t[a].tag) pushdown(a);
				merge(t[x = a].r, t[x].r, b);
			}
			else
			{
				if (t[b].tag) pushdown(b);
				merge(t[x = b].l, a, t[x].l);
			}
			maintain(x);
		}
	}
/*
	may be fake;
	inline void split_by_val(int x, int &a, int &b, int val)
	{
		if (!x) a = b = 0;
		else
		{
			if (t[x].tag) pushdown(x);
			if (val < t[x].v) split_by_val(t[b = x].l, a, t[x].l, val);
			else split_by_val(t[a = x].r, t[x].r, b, val);
			maintain(x);
		}
	}
*/
	inline void split_by_siz(int x, int &a, int &b, int siz)
	{
		if (!x) a = b = 0;
		else
		{
			if (t[x].tag) pushdown(x);
			int temp = t[t[x].l].s + 1;
			if (siz < temp) split_by_siz(t[b = x].l, a, t[x].l, siz);
			else split_by_siz(t[a = x].r, t[x].r, b, siz - temp);
			maintain(x);
		}
	}

	inline void insert(int val) {merge(root, root, newnode(val));}

	inline void reverse(int x, int y)
	{
		int a(0), b(0), c(0);
		split_by_siz(root, a, b, x - 1);
		split_by_siz(b, b, c, y - x + 1);
		t[b].tag ^= 1;
		merge(a, a, b);
		merge(root, a, c);
	}

	inline void print(int x)
	{
		if (!x) return;
		if (t[x].tag) pushdown(x);
		print(t[x].l);
		fprintf(stderr, "%d ", t[x].v);
		print(t[x].r);
	}

	bool flag;
	int ans;
	inline void dfs(int x, int val)
	{
		if (!x || flag) return; 
		ans++;
		if (t[x].l) dfs(t[x].l, val);
		if (flag) return;
		if (t[x].v == val)
		{
			flag = 1;
			return;
		}
		if (flag) return;
		if (t[x].r) dfs(t[x].r, val);
	}

	inline int find(int val)
	{
		ans = flag = 0;
		dfs(root, val);
		return ans;
	}
}T;

int a[maxn];

int main()
{
#ifdef CraZYali
	freopen("1402.in", "r", stdin);
	freopen("1402.out", "w", stdout);
#endif
	while (scanf("%d", &n) * n)
	{
		srand(n);
		T.clear();
		REP(i, 1, n) {scanf("%d", a + i);T.insert(a[i]);}
		REP(i, 1, n)
		{
			int x = T.find(a[i]);
			printf("%d%c", x, i ^ n ? ' ' : '\n');
			int L(i), R(x);
			if (L > R) swap(L, R);
			T.reverse(L, R);
		}

	}
	
	return 0;
}
