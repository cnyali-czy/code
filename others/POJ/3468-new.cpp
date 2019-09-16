/*
 * File Name:	3468-new.cpp
 * Author	:	CraZYali
 * Year		:	2019.09.16 20:40
 * Email	:	yms-chenziyang@outlook.com
 */

#define DREP(i, s, e) for (register int i(s), end_##i(e); i >= end_##i; i--)
#define  REP(i, s, e) for (register int i(s), end_##i(e); i <= end_##i; i++)
#define DEBUG fprintf(stderr, "Passing [%s] in Line %d\n", __FUNCTION__, __LINE__)

#define chkmax(a, b) a = max(a, (b))
#define chkmin(a, b) a = min(a, (b))

#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <algorithm>

using namespace std;
const int maxn = 1e5 + 10;

template <typename T> inline T read()
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

#define file(FILE_NAME) freopen(FILE_NAME".in", "r", stdin), freopen(FILE_NAME".out", "w", stdout);

#define ls(p) ch[p][0]
#define rs(p) ch[p][1]
#define mid (l + r >> 1)

int order[maxn], ch[maxn][2], s[maxn], cur, root;
long long sum[maxn], tag[maxn], val[maxn];

inline void pushup(int x)
{
	s[x] = s[ls(x)] + s[rs(x)] + 1;
	sum[x] = sum[ls(x)] + sum[rs(x)] + val[x];
}
inline void update(int x, long long v)
{
	if (!x) return;
	val[x] += v;
	tag[x] += v;
	sum[x] += v * s[x];
}
inline void pushdown(int x)
{
	if (tag[x])
	{
		update(ls(x), tag[x]);
		update(rs(x), tag[x]);
		tag[x] = 0;
	}
}

inline int newnode(int _val)
{
	++cur;
	order[cur] = rand();
	val[cur] = sum[cur] = _val;
	s[cur] = 1;
	return cur;
}
#define extend(x) merge(root, root, newnode(x))

void merge(int &x, int a, int b)
{
	if (!a || !b) x = a + b;
	else
	{
		pushdown(a);pushdown(b);
		if (order[a] > order[b]) merge(ls(x = b), a, ls(b));
		else merge(rs(x = a), rs(a), b);
		pushup(x);
	}
}
void split(int x, int &a, int &b, int siz)
{
	if (!x) a = b = 0;
	else
	{
		pushdown(x);
		if (s[ls(x)] >= siz) split(ls(b = x), a, ls(x), siz);
		else split(rs(a = x), rs(x), b, siz - s[ls(x)] - 1);
		pushup(x);
	}
}
inline long long query(int l, int r)
{
	int x(0), y(0), z(0);
	split(root, x, y, l - 1);
	split(y, y, z, r - l + 1);
	long long ans(sum[y]);
	merge(y, y, z);
	merge(root, x, y);
	return ans;
}
inline void add(int l, int r, int v)
{
	int x(0), y(0), z(0);
	split(root, x, y, l - 1);
	split(y, y, z, r - l + 1);
	update(y, v);
	merge(y, y, z);
	merge(root, x, y);
}

signed main()
{
#ifdef CraZYali
	file("3468-new");
#endif
	srand((unsigned long long)new char);
	int n(read<int>()), m(read<int>());
	while (n--) extend(read<int>());
	while (m--)
	{
		char c(getchar());
		while (!isalpha(c)) c = getchar();
		int l(read<int>()), r(read<int>());
		if (c == 'Q') printf("%lld\n", query(l, r));
		else add(l, r, read<int>());
	}
	return 0;
}
