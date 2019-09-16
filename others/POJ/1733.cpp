/*
 * File Name:	1733.cpp
 * Author	:	CraZYali
 * Year		:	2019.09.16 19:52
 * Email	:	yms-chenziyang@outlook.com
 */

#define DREP(i, s, e) for (register int i(s), end_##i(e); i >= end_##i; i--)
#define  REP(i, s, e) for (register int i(s), end_##i(e); i <= end_##i; i++)
#define DEBUG fprintf(stderr, "Passing [%s] in Line %d\n", __FUNCTION__, __LINE__)

#define chkmax(a, b) a = max(a, (b))
#define chkmin(a, b) a = min(a, (b))

#include <algorithm>
#include <iostream>
#include <cstdio>

using namespace std;
const int maxm = 10000 + 10, maxn = maxm << 1;

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

pair <pair <int, int>, bool> q[maxm];
int a[maxn], n;

#define id(x) (lower_bound(a + 1, a + 1 + n, x) - a)

int fa[maxn];
bool d[maxn];
int find(int x)
{
	if (fa[x] == x) return x;
	int root = find(fa[x]);
	d[x] ^= d[fa[x]];
	return fa[x] = root;
}

int main()
{
#ifdef CraZYali
	file("1733");
#endif
	read<int>();
	int m;
	REP(i, 1, (m = read<int>()))
	{
		int l(read<int>()), r(read<int>());
		char c(getchar());
		q[i] = make_pair(make_pair(l-1, r), c == 'o');
		a[++n] = l-1;a[++n] = r;
	}
	sort(a + 1, a + 1 + n);
	n = unique(a + 1, a + 1 + n) - a - 1;
	REP(i, 1, n) fa[i] = i;
	REP(i, 1, m)
	{
		int x(id(q[i].first.first)), y(id(q[i].first.second));
		bool opt = q[i].second;
		int fx(find(x)), fy(find(y));
		if (fx == fy)
		{
			if (d[x] ^ d[y] ^ opt) return 0 * (int)(printf("%d\n", i-1));
		}
		else fa[fx] = fy, d[fx] = d[x] ^ d[y] ^ opt;
	}
	cout << m << endl;
	return 0;
}
