/*
	Problem:	3366.cpp
	Time:		2020-07-25 20:52
	Author:		CraZYali
	E-Mail:		yms-chenziyang@outlook.com 
*/

#define REP(i, s, e) for (register int i(s), end_##i(e); i <= end_##i; i++)
#define DEP(i, s, e) for (register int i(s), end_##i(e); i >= end_##i; i--)
#define DEBUG fprintf(stderr, "Passing [%s] in Line %d\n", __FUNCTION__, __LINE__)

#define chkmax(a, b) (a < (b) ? a = (b) : a)
#define chkmin(a, b) (a > (b) ? a = (b) : a)

#include <iostream>
#include <cstdio>

using namespace std;
const int maxn = 5000 + 10, maxm = 2e5 + 10;

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

int n, m, fa[maxn], u[maxm], v[maxm], w[maxm], vis[maxm], Min_id[maxn];
int find(int x) {return fa[x] == x ? fa[x] : fa[x] = find(fa[x]);}
void uni(int x, int y) {fa[find(x)] = find(y);}

int main()
{
#ifdef CraZYali
	file("3366");
#endif
	n = read<int>();m = read<int>();
	REP(i, 1, n) fa[i] = i;
	REP(i, 1, m)
	{
		u[i] = read<int>();v[i] = read<int>();w[i] = read<int>();
		uni(u[i], v[i]);
	}
	REP(i, 1, n) if (find(i) ^ find(1)) return 0 * puts("orz");
	int ans = 0;
	REP(i, 1, n) fa[i] = i;
	int N = n;
	w[0] = 1919810;
	while (N > 1)
	{
		REP(i, 1, n) Min_id[i] = 0;
		REP(i, 1, m) if (!vis[i])
		{
			int x = find(u[i]), y = find(v[i]), z = w[i];
			if (x == y) continue;
			if (w[Min_id[x]] > z) Min_id[x] = i;
			if (w[Min_id[y]] > z) Min_id[y] = i;
		}
		REP(i, 1, n) if (i == fa[i] && Min_id[i] && !vis[Min_id[i]])
		{
			int x = find(u[Min_id[i]]), y = find(v[Min_id[i]]);
			if (x == y) continue;
			N--;
			fa[x] = y;
			ans += w[Min_id[i]];
			vis[Min_id[i]] = 1;
		}
	}
	cout << ans << endl;
	return 0;
}
