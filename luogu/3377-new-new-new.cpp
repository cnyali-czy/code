/*
	Problem:	3377-new-new-new.cpp
	Time:		2020-11-05 09:10
	Author:		CraZYali
	E-Mail:		yms-chenziyang@outlook.com 
*/

#define REP(i, s, e) for (register int i(s), end_##i(e); i <= end_##i; i++)
#define DEP(i, s, e) for (register int i(s), end_##i(e); i >= end_##i; i--)
#define DEBUG fprintf(stderr, "Passing [%s] in Line %d\n", __FUNCTION__, __LINE__)

#define chkmax(a, b) (a < (b) ? a = (b) : a)
#define chkmin(a, b) (a > (b) ? a = (b) : a)

#include <cassert>
#include <algorithm>
#include <vector>
#include <iostream>
#include <cstdio>

using namespace std;
const int maxn = 1e5 + 10, maxN = 2.2e7 + 10;

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

int ls[maxN], rs[maxN], s[maxN], cur;
#define lson ls[p], l, mid
#define rson rs[p], mid + 1, r
#define mid (l + r >> 1)

void insert(int &p, int l, int r, int pos)
{
	if (!p) p = ++cur;
	s[p]++;
	if (l == r) return;
	else if (pos <= mid) insert(lson, pos);
	else insert(rson, pos);
}
void merge(int &x, int y)
{
	if (!x || !y) x |= y;
	else
	{
		s[x] += s[y];
		merge(ls[x], ls[y]);
		merge(rs[x], rs[y]);
	}
}
int topandpop(int p, int l, int r)
{
	assert(s[p]);
	s[p]--;
	if (l == r) return l;
	return s[ls[p]] ? topandpop(lson) : topandpop(rson);
}

int n, q, m, a[maxn], b[maxn], real[maxn];

int fa[maxn], rt[maxn];
int find(int x) {return fa[x] == x ? fa[x] : fa[x] = find(fa[x]);}
void uni(int x, int y)
{
	x = find(x);y = find(y);
	if (x == y) return;
	fa[y] = x;
	merge(rt[x], rt[y]);
}

bool del[maxn];
vector <int> v[maxn];

int main()
{
#ifdef CraZYali
	file("3377-new-new-new");
#endif
	n = read<int>();q = read<int>();
	REP(i, 1, n)
	{
		fa[i] = i;
		a[i] = read<int>();
		b[i] = a[i];
	}
	sort(b + 1, b + 1 + n);
	static int cnt[maxn];
	REP(i, 1, n)
	{
		int id = lower_bound(b + 1, b + 1 + n, a[i]) - b;
		cnt[id]++;
		id += cnt[id] - 1;
		real[id] = i;
		insert(rt[i], 1, n, id);
	}
	while (q--)
	{
		int opt = read<int>(), x = read<int>();
		if (opt == 1)
		{
			int y = read<int>();
			if (del[x] || del[y]) continue;
			uni(x, y);
		}
		else
			if (del[x]) puts("-1");
			else
			{
				x = find(x);
				int res = topandpop(rt[x], 1, n);
				printf("%d\n", b[res]);
				del[real[res]] = 1;
			}
	}
	return 0;
}
