#define DREP(i, s, e) for(int i = s; i >= e ;i--)
#define  REP(i, s, e) for(int i = s; i <= e ;i++)

#define DEBUG fprintf(stderr, "Passing [%s] in Line %d\n", __FUNCTION__, __LINE__)
#define chkmax(a, b) a = max(a, b)
#define chkmin(a, b) a = min(a, b)

#include <bits/stdc++.h>

using namespace std;
const int maxn = 1e4 + 10, maxq = 1e4 + 10;

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

int n, m, q, a[maxn], b[maxn + maxq];
int to(int val) {return lower_bound(b + 1, b + 1 + m, val) - b;}

bool type[maxq];
int x[maxq], y[maxq], z[maxq];

struct node *null;
struct node
{
	node *ls, *rs;
	int sum;
	node() : ls(null), rs(null), sum(0) {}
}*c[maxn];

#define mid (l + r >> 1)

void update(node *pre, node *&p, int l, int r, int pos, int num)
{
	node temp = *pre;
	p = new node();
	p -> ls = temp.ls;
	p -> rs = temp.rs;
	p -> sum = temp.sum + num;
	if (l == r) return;
	else if (pos <= mid)	update(temp.ls, p -> ls, l, mid, pos, num);
	else					update(temp.rs, p -> rs, mid + 1, r, pos, num);
}
void add(int x, int pos, int num = 1)
{
	while (x <= n)
	{
		if (c[x] == NULL) c[x] = new node();
		update(c[x], c[x], 1, m, pos, num);
		x += x & -x;
	}
}
void update(int l, int r, int pos, int num = 1) {add(l, pos, num);add(r + 1, pos, num * -1);}

int lsz, rsz;
node *LLL[maxn], *RRR[maxn];

int query(int l, int r, int k)
{
	if (l == r) return l;
	int x = 0;
	REP(i, 1, rsz) x += RRR[i] -> ls -> sum;
	REP(i, 1, lsz) x -= LLL[i] -> ls -> sum;
	if (x >= k)
	{
		REP(i, 1, lsz) LLL[i] = LLL[i] -> ls;
		REP(i, 1, rsz) RRR[i] = RRR[i] -> ls;
		return query(l, mid, k);
	}
	else
	{
		REP(i, 1, lsz) LLL[i] = LLL[i] -> rs;
		REP(i, 1, rsz) RRR[i] = RRR[i] -> rs;
		return query(mid + 1, r, k - x);
	}
}

int main()
{
#ifdef CraZYali
	freopen("1901-new.in", "r", stdin);
	freopen("1901-new.out", "w", stdout);
#endif
	null = new node();
	null -> ls = null -> rs = null;null -> sum = 0;
	cin >> n >> q;
	REP(i, 1, n) a[i] = b[++m] = read<int>();
	REP(i, 1, q)
	{
		char cc = getchar();
		while (cc != 'Q' && cc != 'C') cc = getchar();
		x[i] = read<int>();y[i] = read<int>();
		if (cc == 'Q') type[i] = 1, z[i] = read<int>();
		else b[++m] = y[i];
	}
	sort(b + 1, b + 1 + m);
	m = unique(b + 1, b + 1 + m) - b - 1;

	REP(i, 1, n) add(i, to(a[i]));
	REP(i, 1, q)
		if (type[i])
		{
			lsz = rsz = 0;
			for (int now = x[i]-1; now > 0;now -= (now & -now)) LLL[++lsz] = c[now];
			for (int now = y[i]; now > 0;now -= (now & -now)) RRR[++rsz] = c[now];
			printf("%d\n", b[query(1, m, z[i])]);
		}
		else
		{
			add(x[i], to(a[x[i]]), -1);
			add(x[i], to(a[x[i]] = y[i]));
		}
	return 0;
}
