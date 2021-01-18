/*
	Problem:	C.cpp
	Time:		2021-01-10 12:28
	Author:		CraZYali
	E-Mail:		yms-chenziyang@outlook.com 
*/

#define REP(i, s, e) for (register int i(s), end_##i(e); i <= end_##i; i++)
#define DEP(i, s, e) for (register int i(s), end_##i(e); i >= end_##i; i--)
#define DEBUG fprintf(stderr, "Passing [%s] in Line %d\n", __FUNCTION__, __LINE__)

#define chkmax(a, b) (a < (b) ? a = (b) : a)
#define chkmin(a, b) (a > (b) ? a = (b) : a)

#include <map>
#include <vector>
#include <iostream>
#include <cstdio>

using namespace std;
const int maxn = 2e5 + 10, maxm = 5e5 + 10;

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

int n, m, q, k, spj[maxn];
int u[maxm], v[maxm];

int fa[maxn], siz[maxn];
int find(int x) {return fa[x] == x ? fa[x] : fa[x] = find(fa[x]);}
void uni(int x, int y)
{
	x = find(x);y = find(y);
	if (x == y) return;
	fa[x] = y;siz[y] += siz[x];
}
vector <int> Qry[maxm];
int Ans[5005][2005];

int main()
{
#ifdef CraZYali
	file("C");
#endif
	n = read<int>();m = read<int>();q = read<int>();
	REP(i, 1, m)
	{
		u[i] = read<int>();
		v[i] = read<int>();
	}
	REP(i, 1, q)
	{
		Qry[i].resize(read<int>());
		REP(j, 0, (int)Qry[i].size() - 1) Qry[i][j] = read<int>();
	}
	REP(ban, 1, n)
	{
		REP(i, 1, n) siz[fa[i] = i] = 1;
		REP(i, 1, m) if (u[i] ^ ban && v[i] ^ ban)
			uni(u[i], v[i]);
		static int res[maxn];
		REP(i, 1, q)
		{
			for (auto l : Qry[i]) 
				REP(c, 1, n) if (c ^ ban)
					if (find(c) == find(l)) Ans[i][c]++;
		}
	}
	REP(i, 1, q)
	{
		int ans = 0;
		REP(j, 1, n) ans = max(ans, Ans[i][j]);
		printf("%d\n", ans);
	}
	return 0;
}
