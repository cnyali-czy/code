#define  REP(i, s, e) for (int i = s; i <= e; i++)
#define DREP(i, s, e) for (int i = s; i >= e; i--)
#define DEBUG fprintf(stderr, "Passing [%s] in Line %lld\n", __FUNCTION__, __LINE__)

#define chkmax(a, b) a = max(a, (b))
#define chkmin(a, b) a = min(a, (b))

#include <bits/stdc++.h>
#define int long long

using namespace std;
const int N = 200000, maxn = N + 10, inf = 1ll<<40;

template <typename T> T read()
{
	T ans(0), flag(1);
	char c(getchar());
	while (!isdigit(c))
	{
		if (c == '-') flag = -1;
		c = getchar();
	}
	while (isdigit(c))
	{
		ans = ans * 10 + c - 48;
		c = getchar();
	}
	return ans * flag;
}

void file(string s)
{
	freopen((s + ".in").c_str(), "r", stdin);
	freopen((s + ".out").c_str(), "w", stdout);
	freopen((s + ".err").c_str(), "w", stderr);
}

struct node
{
	int l, r, s, order, val, sum, lmax, rmax, max_sum, tag_reverse, tag_same;
	bool need;
	node() : l(0), r(0), s(0), order(0), val(0), sum(0), lmax(0), rmax(0), max_sum(0), tag_reverse(0), tag_same(0), need(0) {}
	node(int _val) : l(0), r(0), s(1), order(rand()), val(_val), sum(_val), lmax(_val), rmax(_val), max_sum(_val), tag_reverse(0), need(0){};
}t[maxn];
int s[maxn], top, root;
int create(int val)
{
	int id = s[top--];
	t[id] = node(val);
	return id;
}
void recycle(int x) {s[++top] = x;}

#define max3(x, y, z) max(max(x, y), z)
void same(int x, int v)
{
	if (!x) return;
	t[x].tag_same = v;
	t[x].need = 1;
	t[x].val = v;
	t[x].sum = v * t[x].s;
	if (v >= 0) t[x].lmax = t[x].rmax = t[x].max_sum = t[x].sum;
	else t[x].lmax = t[x].rmax = t[x].max_sum = v;
}
void pushdown(int x)
{
	if (!x) return;
	t[0].lmax=t[0].rmax=t[0].max_sum=-1e9;
	int &l(t[x].l), &r(t[x].r);
	if (t[x].tag_reverse)
	{
		t[x].tag_reverse = 0;
		t[l].tag_reverse ^= 1;
		t[r].tag_reverse ^= 1;
		swap(l, r);
		swap(t[x].lmax, t[x].rmax);
	}
	if (t[x].need)
	{
		if (l) same(l, t[x].tag_same);
		if (r) same(r, t[x].tag_same);
		t[x].need = 0;
	}
}
void pushup(int x)
{
	if (!x) return;
	int l = t[x].l, r = t[x].r;
	if(l) pushdown(l);
	if(r) pushdown(r);
	t[x].s = t[l].s + t[r].s + 1;
	t[x].sum = t[l].sum + t[r].sum + t[x].val;
	t[x].lmax = max(t[l].lmax, t[l].sum + max(t[r].lmax, 0ll) + t[x].val);
	t[x].rmax = max(t[r].rmax, t[r].sum + max(t[l].rmax, 0ll) + t[x].val);
	t[x].max_sum = max3( t[l].max_sum, t[r].max_sum, max(t[l].rmax, 0ll) + t[x].val + max(t[r].lmax, 0ll));
}
void merge(int &x, int a, int b)
{
	if (!a || !b) x = a + b;
	else
	{
		if (t[a].order > t[b].order)
		{
			pushdown(b);
			merge(t[x = b].l, a, t[b].l);
		}
		else
		{
			pushdown(a);
			merge(t[x = a].r, t[a].r, b);
		}
		pushup(x);
	}
}
void split(int x, int &a, int &b, int siz)
{
	if (!x) a = b = 0;
	else
	{
		pushdown(x);
		if (t[t[x].l].s >= siz) split(t[b = x].l, a, t[x].l, siz);
		else split(t[a = x].r, t[x].r, b, siz - t[t[x].l].s - 1);
		pushup(x);
	}
}
int GET(int pos)
{
	int x(0), y(0), z(0);
	split(root, x, y, pos - 1);
	split(y, y, z, 1);
	int ans = t[y].val;
	merge(y, y, z);
	merge(root, x, y);
	return ans;
}
void INSERT(int pos, int a[], int len)
{
	int x(0), y(0);
	split(root, x, y, pos);
	REP(i, 1, len) merge(x, x, create(a[i]));
	merge(root, x, y);
}
void del(int y)
{
	if (!y) return;
	del(t[y].l);
	del(t[y].r);
	recycle(y);
}
void DELETE(int pos, int tot)
{
	int x(0), y(0), z(0);
	split(root, x, y, pos - 1);
	split(y, y, z, tot);
	merge(root, x, z);
	del(y);
}
void MAKE_SAME(int pos, int tot, int c)
{
	int x(0), y(0), z(0);
	split(root, x, y, pos - 1);
	split(y, y, z, tot);
	same(y, c);
	merge(y, y, z);
	merge(root, x, y);
}
void REVERSE(int pos, int tot)
{
	int x(0), y(0), z(0);
	split(root, x, y, pos - 1);
	split(y, y, z, tot);
	t[y].tag_reverse ^= 1;
	merge(y, y, z);
	merge(root, x, y);
}
int GET_SUM(int pos, int tot)
{
	int x(0), y(0), z(0);
	split(root, x, y, pos - 1);
	split(y, y, z, tot);
	int ans = t[y].sum;
	merge(y, y, z);
	merge(root, x, y);
	return ans;
}
int MAX_SUM(int pos, int tot)
{
	int x(0), y(0), z(0);
	split(root, x, y, pos - 1);
	split(y, y, z, tot);
	int ans = t[y].max_sum;
	merge(y, y, z);
	merge(root, x, y);
	return ans;
}
void PUSH_BACK(int val)
{
	int z(create(val));
	merge(root, root, z);
}

int m, n, a[maxn];
char ss[20];

signed main()
{
#ifdef CraZYali
	file("2710");
#endif
	srand((unsigned long long)new char);
	top = N;
	REP(i, 1, top) s[i] = i;
	cin >> n >> m;
	REP(i, 1, n) PUSH_BACK(read<int>());
	while (m--)
	{
		scanf("%s", ss + 1);
		if (ss[1] == 'I')
		{
			int pos(read<int>()), tot(read<int>());
			REP(i, 1, tot) a[i] = read<int>();
			INSERT(pos, a, tot);
			n += tot;
		}
		else if (ss[1] == 'D')
		{
			int pos(read<int>()), tot(read<int>());
			DELETE(pos, tot);
			n -= tot;
		}
		else if (ss[1] == 'M' && ss[3] == 'K')
		{
			int pos(read<int>()), tot(read<int>());
			MAKE_SAME(pos, tot, read<int>());
		}
		else if (ss[1] == 'R')
		{
			int pos(read<int>()), tot(read<int>());
			REVERSE(pos, tot);
		}
		else if (ss[1] == 'G' && ss[4] == '-')
		{
			int pos(read<int>()), tot(read<int>());
			printf("%lld\n", GET_SUM(pos, tot));
		}
		else if (ss[1] == 'G') printf("%lld\n", GET(read<int>()));
		else
		{
			int pos(read<int>()), tot(read<int>());
			printf("%lld\n", MAX_SUM(pos, tot));
		}
	}
	return 0;
}
