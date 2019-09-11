/*
 * File Name:	A.cpp
 * Author	:	CraZYali
 * Year		:	2019.09.11 21:38
 * Email	:	yms-chenziyang@outlook.com
 */

#define DREP(i, s, e) for (register int i(s), end_##i(e); i >= end_##i; i--)
#define  REP(i, s, e) for (register int i(s), end_##i(e); i <= end_##i; i++)
#define DEBUG fprintf(stderr, "Passing [%s] in Line %d\n", __FUNCTION__, __LINE__)

#define chkmax(a, b) a = max(a, (b))
#define chkmin(a, b) a = min(a, (b))

#include <iostream>
#include <cstdio>
#include <vector>

using namespace std;
const int maxn = 1e6 + 10, maxw = 1e5 + 10, inf = 1e5;

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

int n, m;
int fa[maxn], siz[maxn];
int find(int x) {return fa[x] == x ? x : find(fa[x]);}

int *sta[maxn << 1], pre[maxn << 1], top;
#define pack(x) (sta[++top] = &x, pre[top] = x)

inline void uni(int x, int y)
{
	x = find(x);y = find(y);
	if (x == y) return;
	if (siz[x] < siz[y]) swap(x, y);
	pack(fa[y]);pack(siz[x]);
	siz[x] += siz[y];fa[y] = x;
}
#define undo() *sta[top] = pre[top--]

vector <pair <int, int> > v[maxw]; 

void solve(int l, int r)
{
	if (l == r)
	{
		if (siz[find(1)] == n)
		{
			cout << l << endl;
			exit(0);
		}
		return;
	}
	int mid(l + r >> 1), cur(top);
	REP(i, mid + 1, r)
		for (auto it : v[i]) uni(it.first, it.second);
	solve(l, mid);
	while (top > cur) undo();
	REP(i, l, mid)
		for (auto it : v[i]) uni(it.first, it.second);
	solve(mid + 1, r);
	while (top > cur) undo();
}

int main()
{
#ifdef CraZYali
	file("A");
#endif
	cin >> n >> m;
	REP(i, 1, n) siz[fa[i] = i] = 1;
	while (m--)
	{
		int x(read<int>()), y(read<int>()), z(read<int>());
		v[z].push_back(make_pair(x, y));
	}
	solve(0, inf);
	return 0;
}
