#pragma GCC optimize(3)
#define DREP(i, s, e) for(int i = s; i >= e ;i--)
#define  REP(i, s, e) for(int i = s; i <= e ;i++)

#define DEBUG fprintf(stderr, "Passing [%s] in Line %d\n", __FUNCTION__, __LINE__)
#define chkmax(a, b) a = max(a, b)
#define chkmin(a, b) a = min(a, b)

#include <bits/stdc++.h>

using namespace std;
typedef unsigned long long ull;
const int maxn = 100000 + 10;
const ull P = 1e9 + 9;

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
char s[maxn];

ull base[maxn];

struct node
{
	int l, r, s, order;
	char c;
	ull Hash;
	node(){}
	node(char _c) : c(_c), Hash(c), s(1), l(0), r(0), order(rand()){}
};

node t[maxn];
int root, cur;
int newnode(char c) {t[++cur] = node(c);return cur;}
void maintain(int x)
{
	t[x].s = t[t[x].l].s + t[t[x].r].s + 1;
	t[x].Hash = t[t[x].l].Hash + t[x].c * base[t[t[x].l].s] + t[t[x].r].Hash * base[t[t[x].l].s + 1];
}
void split(int x, int &a, int &b, int siz)
{
	if (!x) a = b = 0;
	else
	{
		if (t[t[x].l].s >= siz) split(t[b = x].l, a, t[x].l, siz);
		else split(t[a = x].r, t[x].r, b, siz - t[t[x].l].s - 1);
		maintain(x);
	}
}
void merge(int &x, int a, int b)
{
	if (!(a * b)) x = a + b;
	else
	{
		if (t[a].order < t[b].order) merge(t[x = b].l, a, t[b].l);
		else merge(t[x = a].r, t[a].r, b);
		maintain(x);
	}
}
void insert(int pos, char c)
{
	int x(0), y(0), z(newnode(c));
	split(root, x, y, pos);
	merge(x, x, z);
	merge(root, x, y);
}
void modify(int pos, char c, int x = root)
{
	if (t[t[x].l].s + 1 == pos) t[x].c = c;
	else if (t[t[x].l].s >= pos) modify(pos, c, t[x].l);
	else modify(pos - t[t[x].l].s - 1, c, t[x].r);
	maintain(x);
}
ull getHash(int S, int T)
{
	int x(0), y(0), z(0);
	split(root, x, y, S - 1);
	split(y, y, z, T - S + 1);
	ull ret = t[y].Hash;
	merge(y, y, z);
	merge(root, x, y);
	return ret;
}
int query(int S1, int S2)
{
	int l = 0, r = min(n - S1, n - S2), ans = 0;
	while (l <= r)
	{
		int mid = l + r >> 1;
		if (getHash(S1, S1 + mid) == getHash(S2, S2 + mid)) ans = l = mid + 1;
		else r = mid - 1;
	}
	return ans;
}

int main()
{
#ifdef CraZYali
	freopen("1014.in", "r", stdin);
	freopen("1014.out", "w", stdout);
#endif
	srand((unsigned long long)new char);
	scanf("%s", s + 1);
	n = strlen(s + 1);
	base[0] = 1;
	REP(i, 1, maxn - 10) base[i] = base[i-1] * P;
	REP(i, 1, n) insert(i-1, s[i]);
	cin >> m;
	while (m--)
	{
		char c = getchar();
		while (c ^ 'Q' && c ^ 'R' && c ^ 'I') c = getchar();
		if (c == 'Q') printf("%d\n", query(read<int>(), read<int>()));
		else
		{
			int x = read<int>();
			char d = getchar();
			while (d == ' ' || d == '\n') d = getchar();
			if (c == 'R') modify(x, d);
			else ++n, insert(x, d);
		}
	}
	return 0;
}
