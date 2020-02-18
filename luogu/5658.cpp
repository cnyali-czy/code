/*
	Problem:	5658.cpp
	Time:		2020-02-18 14:34
	Author:		CraZYali
	E-Mail:		yms-chenziyang@outlook.com 
*/

#define REP(i, s, e) for (register int i(s), end_##i(e); i <= end_##i; i++)
#define DEP(i, s, e) for (register int i(s), end_##i(e); i >= end_##i; i--)
#define DEBUG fprintf(stderr, "Passing [%s] in Line %d\n", __FUNCTION__, __LINE__)

#define chkmax(a, b) (a < (b) ? a = (b) : a)
#define chkmin(a, b) (a > (b) ? a = (b) : a)

#include <cstring>
#include <vector>
#include <iostream>
#include <cstdio>

using namespace std;
const int maxn = 5e5 + 10, maxN = 2e7;

int bg[maxn], ne[maxn], to[maxn], e;
void add(int x, int y)
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
#include<cassert>
int n, sum[maxn], fa[maxn][20], dep[maxn];
char s[maxn];
long long res, ans[maxn], Min[maxn][20];

inline int min(int x, int y) {if (x < y) return x;return y;}
int lg[(1 << 19) + 1];
int qry(int x, int y)
{
	int res = 1e9;
	int delta = dep[x] - dep[y];
	for (int delta = dep[x] - dep[y]; delta; delta &= (delta - 1))
	{
		int i = lg[delta & -delta];
		chkmin(res, Min[x][i]);
		x = fa[x][i];
	}
	return res;
}
vector <int> shw[maxn + maxn];
#define show(x) shw[(x) + n]
void dfs(int x)
{
	dep[x] = dep[fa[x][0]] + 1;
	ans[x] = ans[fa[x][0]];
	Min[x][0] = sum[x] = (sum[fa[x][0]] + (s[x] == '(' ? 1 : -1));
	REP(i, 1, 19)
	{
		fa[x][i] = fa[fa[x][i-1]][i-1];
		Min[x][i] = min(Min[x][i-1], Min[fa[x][i-1]][i-1]);
		if (!fa[x][i]) break;
	}
	if (s[x] == ')')
	{
		int l = 0, r = (int)show(sum[x]).size() - 1;
		bool flag = 0;
		int X = x, cur = 1e9;
		DEP(i, 19, 0) if (fa[X][i] && min(cur, Min[X][i]) >= sum[x])
		{
			chkmin(cur, Min[X][i]);
			X = fa[X][i];
		}
		if (X == 1 && sum[1] >= sum[x]) X = 0;
		while (l < r)
		{
			int mid = l + r >> 1;
			if (dep[show(sum[x])[mid]] >= dep[X]) r = mid;
			else l = mid + 1;
		}
		if (r >= 0 && dep[show(sum[x])[r]] >= dep[X]) ans[x] += show(sum[x]).size() - r;
	}
	show(sum[x]).emplace_back(x);
	res ^= x * ans[x];
	for (int i = bg[x]; i; i = ne[i]) dfs(to[i]);
	show(sum[x]).pop_back();
}

int main()
{
#ifdef CraZYali
	file("5658");
#else
	file("brackets");
#endif
	n = read<int>();
	REP(i, 1, 19) lg[1 << i] = i;
	scanf("%s", s + 1);
	memset(Min, 127, sizeof Min);
	show(0).emplace_back(0);
	REP(i, 2, n) add(fa[i][0] = read<int>(), i);
	dfs(1);
	cout << res << endl;
	return 0;
}
