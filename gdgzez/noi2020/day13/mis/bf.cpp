/*
	Problem:	mis.cpp
	Time:		2020-06-13 09:49
	Author:		CraZYali
	E-Mail:		yms-chenziyang@outlook.com 
*/

#define REP(i, s, e) for (register int i(s), end_##i(e); i <= end_##i; i++)
#define DEP(i, s, e) for (register int i(s), end_##i(e); i >= end_##i; i--)
#define DEBUG fprintf(stderr, "Passing [%s] in Line %d\n", __FUNCTION__, __LINE__)

#define chkmax(a, b) (a < (b) ? a = (b) : a)
#define chkmin(a, b) (a > (b) ? a = (b) : a)

#include <algorithm>
#include <iostream>
#include <cstdio>
#include <vector>

using namespace std;
const int maxn = 400 + 10;
#define i64 long long

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

int n, c[maxn], d[maxn];
i64 t[maxn];
vector <int> G[maxn];
bool vis[maxn];
int id[maxn];

int main()
{
	freopen("mis.in", "r", stdin);
	freopen("bf.out", "w", stdout);
	n = read<int>();
	REP(i, 1, n) d[i] = read<int>();
	REP(i, 2, n)
	{
		c[i] = read<int>();
		G[i].emplace_back(c[i]);
		G[c[i]].emplace_back(i);
	}
	REP(i, 1, n) id[i] = i;
	bool first = 1;
	i64 ans;
	do
	{
		REP(i, 1, n) vis[i] = 0, t[i] = d[i];
		i64 res = 0;
		REP(i, 1, n)
		{
			int x = id[i];
			res += t[x];
			vis[x] = 1;
			for (int y : G[x]) if (!vis[y]) t[y] += t[x];
		}
		if (res == 716) REP(i, 1, n) printf("%d%c",id[i],i==n?'\n': ' ');
		if (first) ans = res;
		else  chkmax(ans, res);
		first = 0;
	}while (next_permutation(id + 1, id + 1 + n));
	cout << ans << endl;
	return 0;
}
