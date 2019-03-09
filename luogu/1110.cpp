#define DREP(i, s, e) for(int i = s; i >= e ;i--)
#define  REP(i, s, e) for(int i = s; i <= e ;i++)

#define DEBUG fprintf(stderr, "Passing [%s] in Line %d\n", __FUNCTION__, __LINE__)
#define chkmax(a, b) a = max(a, b)
#define chkmin(a, b) a = min(a, b)

#include <algorithm>
#include <iostream>
#include <cstring>
#include <cstdio>
#include <set>
#define int long long
#define getchar() getchar_unlocked()
using namespace std;
const int maxn = 500000 + 10 << 1, inf = 1e9;

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

struct node
{
	int l, r, s, order, val;
	node() {}
	node(int _val) : l(0), r(0), s(1), order(rand()), val(_val) {}
};

void write(int x)
{
	if (x / 10) write(x / 10);
	putchar(x % 10 + '0');
}

struct FHQ_TREAP
{
	int root, cur;
	FHQ_TREAP() {root = cur = 0;}
	node t[maxn];
	int newnode(int val) {t[++cur] = node(val);return cur;}
	void maintain(int x) {t[x].s = t[t[x].l].s + t[t[x].r].s + 1;}
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
	void split_by_siz(int x, int &a, int &b, int siz)
	{
		if (!x) a = b = 0;
		else
		{
			if (t[t[x].l].s >= siz) split_by_siz(t[b = x].l, a, t[x].l, siz);
			else split_by_siz(t[a = x].r, t[x].r, b, siz - t[t[x].l].s - 1);
			maintain(x);
		}
	}
	void insert_treap(int val)
	{
		int x(0), y(0), z(newnode(val));
		split_by_val(root, x, y, val);
		merge(x, x, z);
		merge(root, x, y);
	}
	void insert_queue(int pos, int val)
	{
		int x(0), y(0), z(newnode(val));
		split_by_siz(root, x, y, pos - 1);
		merge(x, x, z);
		merge(root, x, y);
	}
	int query_pos(int pos)
	{
		int x(0), y(0), z(0);
		split_by_siz(root, x, y, pos - 1);
		split_by_siz(y, y, z, 1);
		int ans = t[y].val;
		merge(y, y, z);
		merge(root, x, y);
		return ans;
	}
	int kth(int k, int now)
	{
		while (t[t[now].l].s + 1 != k)
			if (t[t[now].l].s >= k) now = t[now].l;
			else k -= t[t[now].l].s + 1, now = t[now].r;
		return t[now].val;
	}
	int kth(int k) {return kth(k, root);}
	int pre(int val)
	{
		int x(0), y(0);
		split_by_val(root, x, y, val);
		int ans = (x ? kth(t[x].s, x) : inf);
		merge(root, x, y);
		return ans;
	}
	int nxt(int val)
	{
		int x(0), y(0);
		split_by_val(root, x, y, val-1);
		int ans = (y ? kth(1, y) : inf);
		merge(root, x, y);
		return ans;
	}
}Queue, Sorted;

int n, m, a[maxn];
char s[20];

bool flag1, flag2;

multiset <int> S1, S2;
int MIN_GAP() {return *S1.begin();}
int MIN_SORT_GAP()
{
	if (flag2) return 0;
	int ans = *S2.begin();
	if (!ans) flag2 = 1;
	return ans;
}

int c[maxn];
void add(int x)
{
	while (x <= n)
	{
		c[x]++;
		x += x & -x;
	}
}
int sum(int x)
{
	int y = 0;
	while (x > 0)
	{
		y += c[x];
		x -= x & -x;
	}
	return y;
}

void INSERT(int pos, int k)
{
	int now = Queue.query_pos(sum(pos));
	S1.insert(abs(now - k));
	if (pos < n)
	{
		int nxt1 = Queue.query_pos(sum(pos) + 1);
		S1.erase(S1.find(abs(now - nxt1)));
		S1.insert(abs(k - nxt1));
	}
	Queue.insert_queue(sum(pos) + 1, k);
	if (!flag2)
	{
		int pre = Sorted.pre(k), nxt = Sorted.nxt(k);
		if (pre ^ inf) S2.insert(abs(pre - k));
		if (nxt ^ inf) S2.insert(abs(k - nxt));
		if (pre != inf && nxt != inf) S2.erase(S2.find(abs(pre-nxt)));
		Sorted.insert_treap(k);
	}
	add(pos);
}

signed main()
{
#ifdef CraZYali
	freopen("1110.in", "r", stdin);
	freopen("1110.out", "w", stdout);
#endif
	srand((unsigned long long) new char);
	cin >> n >> m;
	REP(i, 1, n)
	{
		add(i);
		a[i] = read<int>();
		Queue.insert_queue(i, a[i]);
		Sorted.insert_treap(a[i]);
	}
	REP(i, 2, n) S1.insert(abs(a[i] - a[i-1]));
	sort(a + 1, a + 1 + n);
	REP(i, 2, n) S2.insert(abs(a[i] - a[i-1]));
	REP(i, 1, m)
	{
		scanf("%s", s + 1);
		int len = strlen(s + 1);
		if (len == 6)
		{
			int pos = read<int>(), k = read<int>();
			INSERT(pos, k);
		}
		else if (len == 7) write(MIN_GAP()), putchar(10);
		else write(MIN_SORT_GAP()), putchar(10);
	}
	return 0;
}

