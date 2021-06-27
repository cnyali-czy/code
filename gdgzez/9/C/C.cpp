/*
	Problem:	C.cpp
	Time:		2021-06-21 16:37
	Author:		CraZYali
	E-Mail:		yms-chenziyang@outlook.com 
*/

#define REP(i, s, e) for (register int i(s), end_##i(e); i <= end_##i; i++)
#define DEP(i, s, e) for (register int i(s), end_##i(e); i >= end_##i; i--)
#define DEBUG fprintf(stderr, "Passing [%s] in Line %d\n", __FUNCTION__, __LINE__)

#define chkmax(a, b) (a < (b) ? a = (b) : a)
#define chkmin(a, b) (a > (b) ? a = (b) : a)

#include <cstring>
#include <unordered_map>
#include <iostream>
#include <cstdio>
#define i64 int

using namespace std;
const int maxn = 1e6 + 10;

	template <typename T>
inline T read()
{
	T ans = 0, flag = 1;
	char c = getchar();
	while (!isdigit(c))
	{
		if (c == '-') flag = -1;
		c = getchar();
	}
	while (isdigit(c))
	{
		ans = ans * 10 + (c - 48);
		c = getchar();
	}
	return ans * flag;
}

#define file(FILE_NAME) freopen(FILE_NAME".in", "r", stdin), freopen(FILE_NAME".out", "w", stdout)

int n, m, opt;
char str[maxn];
#define fi first
#define se second
unordered_map <int, i64> s[maxn], sold[maxn];
int rs[maxn], rold[maxn];

namespace Treap
{
	const int maxnode = 2e7;
	struct node
	{
		int l, r, s, order;
		int sum, val;
		node() : l(0), r(0), s(0), sum(0) {}
		node(int _val) : l(0), r(0), s(1), val(_val), sum(_val), order(rand()) {}
	}t[maxnode];
	int cur;
	int newnode(int val)
	{
		t[++cur] = node(val);
		return cur;
	}
	int copy(int x)
	{
		t[++cur] = t[x];
		return cur;
	}
	int root[maxn];
	void pushup(int x)
	{
		t[x].s = t[t[x].l].s + t[t[x].r].s + 1;
		t[x].sum = t[t[x].l].sum + t[t[x].r].sum + t[x].val;
	}
	void merge(int &x, int a, int b)
	{
		if (!a || !b) x = a + b;
		else
		{
			if (t[a].order > t[b].order) merge(t[x = b].l, a, t[b].l);
			else merge(t[x = a].r, t[a].r, b);
			pushup(x);
		}
	}
	void split(int x, int &a, int &b, int k)
	{
		if (!x) a = b = 0;
		else
		{
			if (t[t[x].l].s >= k)
			{
				b = copy(x);
				split(t[b].l, a, t[b].l, k);
				pushup(b);
			}
			else
			{
				a = copy(x);
				split(t[a].r, t[a].r, b, k - t[t[x].l].s - 1);
				pushup(a);
			}
		}
	}
	void insert(int pre, int &rt, int pos, int val)
	{
		int x(0), y(0);
		split(pre, x, y, pos);
		merge(x, x, newnode(val));
		merge(rt, x, y);
	}
	void erase(int pre, int &rt, int pos)
	{
		int x(0), y(0), z(0);
		split(pre, x, y, pos);
		split(x, x, z, pos - 1);
		merge(rt, x, y);
	}
	int query(int pre, int &rt, int l, int r)
	{
		int x(0), y(0), z(0);
		split(pre, x, y, l - 1);
		split(y, y, z, r - l + 1);
		int ans = t[y].sum;
		merge(y, y, z);
		merge(rt, x, y);
		return ans;
	}
	int get(int x, int k)
	{
		int y = 0, z = 0;
		split(x, y, z, k);
		return y;
	}
}

using namespace Treap;
namespace AC
{
	int ch[maxn][26], fail[maxn], len[maxn], fa[maxn], cur = 1;
	int ins()
	{
		scanf("%s", str + 1);
		int p = 1;
		REP(i, 1, strlen(str + 1))
		{
			int c = str[i] - 'a';
			if (!ch[p][c])
			{
				ch[p][c] = ++cur;
				len[ch[p][c]] = len[p] + 1;
				fa[ch[p][c]] = p;
			}
			p = ch[p][c];
		}
		return p;
	}
	int que[maxn], head, tail;

	int sb[maxn];

	void build()
	{
		REP(i, 1, n) merge(sb[i], copy(sb[i - 1]), newnode(0));
		REP(i, 0, 25) ch[0][i] = 1;
		que[head = tail = 0] = 1;
		while (head <= tail)
		{
			int x = que[head++];

			s[x] = s[fa[x]];
			for (auto i : sold[fail[x]]) sold[x][len[x] - len[fail[x]] + i.fi] += i.se;
			for (auto i : sold[x]) s[x][i.fi] += i.se;
		

			REP(i, 0, 25)
				if (ch[x][i]) fail[que[++tail] = ch[x][i]] = ch[fail[x]][i];
				else ch[x][i] = ch[fail[x]][i];
		}
	}
}
int main()
{
#ifdef CraZYali
	file("C");
#endif
	n = read<int>();m = read<int>();opt = read<int>();
	AC :: ins();
	while (m--)
	{
		int p = AC :: ins(), x = read<int>();
		sold[p][1] += x;
		if (!rold[p]) rold[p] = newnode(x);
		else t[rold[p]].val += x, t[rold[p]].sum += x;
	}
	AC :: build();
	i64 ans = 0, q = read<int>();
	while (q--)
	{
		i64 l = read<i64>(), r = read<i64>();
		if (opt) l ^= ans, r ^= ans;
		ans = 0;
		for (auto i : s[r + 1]) if (i.fi >= l) ans += i.se;
		printf("%lld\n", ans);
	}
	return 0;
}
