/*
	Problem:	arrange.cpp
	Time:		2020-06-12 08:43
	Author:		CraZYali
	E-Mail:		yms-chenziyang@outlook.com 
*/

#define REP(i, s, e) for (register int i(s), end_##i(e); i <= end_##i; i++)
#define DEP(i, s, e) for (register int i(s), end_##i(e); i >= end_##i; i--)
#define DEBUG fprintf(stderr, "Passing [%s] in Line %d\n", __FUNCTION__, __LINE__)

#define chkmax(a, b) (a < (b) ? a = (b) : a)
#define chkmin(a, b) (a > (b) ? a = (b) : a)

#ifdef CraZYali
#include <ctime>
#endif
#include <iostream>
#include <cstdio>

using namespace std;
const int maxn = 2e5 + 10;

int bg[maxn], ne[maxn << 1], to[maxn << 1], e;
inline void add(int x, int y)
{
	e++;
	to[e] = y;
	ne[e] = bg[x];
	bg[x] = e;
}

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
		ans = ans * 10 + c - 48;
		c = getchar();
	}
	return ans * flag;
}

#define file(FILE_NAME) freopen(FILE_NAME".in", "r", stdin), freopen(FILE_NAME".out", "w", stdout)

int n, k, a[maxn];

int siz[maxn], Min[maxn];
void dfs0(int x, int fa = 0)
{
	siz[x] = 1;
	Min[x] = a[x];
	for (int i = bg[x]; i; i = ne[i]) if (to[i] ^ fa)
	{
		dfs0(to[i], x);
		chkmin(Min[x], Min[to[i]]);
		siz[x] += siz[to[i]];
	}
}
int M;
bool dfs(int x, int k, int fa = 0)
{
	if (a[x] < M) return 0;
	k--;if (!k) return 1;
	for (int i = bg[x]; i; i = ne[i]) if (to[i] ^ fa && Min[to[i]] >= M)
	{
		k -= siz[to[i]];
		if (k <= 0) return 1;
	}
	for (int i = bg[x]; i; i = ne[i]) if (to[i] ^ fa && Min[to[i]] < M && dfs(to[i], k, x)) return 1;
	return 0;
}
int id[maxn];
bool judge(int mid)
{
	M = mid;
	REP(i, 1, n)
	{
		dfs0(i);
		if (dfs(i, k)) return 1;
	}
	return 0;
}

int main()
{
	freopen("bf.out", "w", stdout);
	freopen("arrange.in", "r", stdin);
	n = read<int>();k = read<int>();
	REP(i, 1, n) a[i] = read<int>();
	REP(i, 2, n)
	{
		int x(read<int>()), y(read<int>());
		add(x, y);add(y, x);
	}
	int l = 1, r = 0, good = 1;
	REP(i, 1, n) chkmax(r, a[i]);
	while (l <= r)
	{
		int mid = l + r >> 1;
		if (judge(mid)) {good = mid;l = mid + 1;}
		else r = mid - 1;
	}
	cout << good << endl;
	return 0;
}
