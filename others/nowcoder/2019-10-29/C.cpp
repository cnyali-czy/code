/*
 * File Name:	C.cpp
 * Author	:	CraZYali
 * Year		:	2019.10.29 21:20
 * Email	:	yms-chenziyang@outlook.com
 */

#define DREP(i, s, e) for (register int i(s), end_##i(e); i >= end_##i; i--)
#define  REP(i, s, e) for (register int i(s), end_##i(e); i <= end_##i; i++)
#define DEBUG fprintf(stderr, "Passing [%s] in Line %d\n", __FUNCTION__, __LINE__)

#define chkmax(a, b) (a < (b) ? a = (b) : a) 
#define chkmin(a, b) (a > (b) ? a = (b) : a) 

#include <iostream>
#include <cstdio>
#include <vector>

using namespace std;
const int maxn = 1e5 + 10, maxk = maxn;

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

int n, k, q, a[maxk], b[maxk], ans[maxn];
int fa[maxn], ed[maxn], siz[maxn];
int find(int x) {return x == fa[x] ? fa[x] : fa[x] = find(fa[x]);}
inline void uni(int x, int y)
{
	x = find(x);y = find(y);
	if (siz[x] > siz[y]) swap(x, y);
	if (x == y) ed[x]++;
	else
	{
		siz[y] += siz[x];
		ed[y] += ed[x] + 1;
		fa[x] = y;
	}
}
int Min[maxn], Max[maxn], lim[maxn];
vector <pair <int, int> > Q[maxn];

int main()
{
#ifdef CraZYali
	file("C");
#endif
	cin >> n >> k;
	REP(i, 1, n) siz[fa[i] = i] = 1;
	bool qaq(1);
	REP(i, 1, k) uni(read<int>(), read<int>());
	REP(i, 1, n) lim[i] = 1e9, Min[i] = 1e9;
	REP(i, 1, n)
	{
		int qaq = find(i);
		chkmin(Min[qaq], i);
		chkmax(Max[qaq], i);
	}
	REP(i, 1, n) if (i == fa[i] && ed[i] == siz[i] - 1)
		chkmin(lim[Min[i]], Max[i]);
	q = read<int>();
	REP(i, 1, q)
	{
		int l(read<int>()), r(read<int>());
		Q[l].emplace_back(r, i);
	}
	int nowlim = n + 1;
	DREP(i, n, 1)
	{
		chkmin(nowlim, lim[i]);
		for (auto j : Q[i]) 
			ans[j.second] = j.first < nowlim;
	}
	REP(i, 1, q) puts(ans[i] ? "Yes" : "No");
	return 0;
}
