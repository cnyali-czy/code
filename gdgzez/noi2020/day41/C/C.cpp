/*
	Problem:	C.cpp
	Time:		2020-08-13 11:19
	Author:		CraZYali
	E-Mail:		yms-chenziyang@outlook.com 
*/

#define REP(i, s, e) for (register int i(s), end_##i(e); i <= end_##i; i++)
#define DEP(i, s, e) for (register int i(s), end_##i(e); i >= end_##i; i--)
#define DEBUG fprintf(stderr, "Passing [%s] in Line %d\n", __FUNCTION__, __LINE__)

#define chkmax(a, b) (a < (b) ? a = (b) : a)
#define chkmin(a, b) (a > (b) ? a = (b) : a)

#include <vector>
#include <iostream>
#include <cstdio>

using namespace std;
const int maxn = 5000 + 10;

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

int n, k, fa[maxn], ch[maxn][2], s[maxn], lnt, l[maxn], ans;

int c[maxn], d[maxn], dep[maxn], hvy[maxn];

int E[maxn], O[maxn], e, o, C, D;
int bstE[maxn], bstO[maxn];

void dfs(int x)
{
	if (!s[x])
	{
		C = c[x];
		D = d[x];
	}
	else dfs(ch[x][hvy[x]]);
}

pair <int, int> res[1 << 8][1 << 8];

void calc()
{
	REP(i, 0, n) bstE[i] = bstO[i] = 0;
	REP(i, 0, (1 << e) - 1)
	{
		REP(k, 0, e - 1)
			hvy[E[k]] = (i >> k) & 1;
		REP(j, 0, (1 << o) - 1)
		{
			REP(k, 0, o - 1)
				hvy[O[k]] = (j >> k) & 1;
			C = D = 0;
			dfs(1);
			chkmax(bstE[i], D);
			chkmax(bstO[j], C);
			res[i][j] = make_pair(C, D);
		}
	}
	REP(i, 0, (1 << e) - 1) REP(j, 0, (1 << o) - 1)
		if (res[i][j] == make_pair(bstO[j], bstE[i])) ans++;
}

void Dfs(int x)
{
	if (x == lnt) calc();
	else
	{
		x++;
		REP(i, 1, k) REP(j, 1, k)
		{
			c[l[x]] = i;
			d[l[x]] = j;
			Dfs(x);
		}
	}
}

int main()
{
#ifdef CraZYali
	file("C");
#endif
	n = read<int>();k = read<int>();
	REP(i, 2, n)
	{
		fa[i] = read<int>() + 1;
		ch[fa[i]][s[fa[i]]++] = i;
		dep[i] = dep[fa[i]] + 1;
	}
	REP(i, 1, n)
		if (!s[i]) l[++lnt] = i;
		else if (dep[i] & 1)	O[o++] = i;
		else					E[e++] = i;
	Dfs(0);
	cout << ans << endl;
	return 0;
}
