/*
	Problem:	A.cpp
	Time:		2020-08-06 23:38
	Author:		CraZYali
	E-Mail:		yms-chenziyang@outlook.com 
*/

#define REP(i, s, e) for (register int i(s), end_##i(e); i <= end_##i; i++)
#define DEP(i, s, e) for (register int i(s), end_##i(e); i >= end_##i; i--)
#define DEBUG fprintf(stderr, "Passing [%s] in Line %d\n", __FUNCTION__, __LINE__)

#include <iostream>
#include <cstdio>
#include <cstring>
#include <vector>
#define int long long

using namespace std;
const int maxn = 5e5 + 10;

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

int n, a[maxn], fa[maxn];
vector <int> G[maxn];

int ans, Ans[maxn], tot;
int ch[maxn * 65][2], rt, cur;
bool t[maxn];

bool in(int x, int i) {return x >> i & 1;}
void insert(int &p, int val, int dep)
{
	if (!p) p = ++cur;
	if (dep == -1) return;
	insert(ch[p][in(val, dep)], val, dep - 1);
}
int query(int p, int val, int dep)
{
	if (dep == -1) return 0;
	bool flag = in(val, dep);
	if (ch[p][!flag])	return query(ch[p][!flag], val, dep - 1) + (1ll << dep);
	else				return query(ch[p][ flag], val, dep - 1);
}
inline bool chkmax(int &x, int y) {if (x < y) {x = y;return 1;}return 0;}
void dfs(int x)
{
	if (t[x]) Ans[x] = ans;
	for (auto y : G[x]) if (!t[y]) dfs(y);
	insert(rt, a[x], 61);
	chkmax(ans, query(rt, a[x], 61));
	for (auto y : G[x]) if ( t[y]) dfs(y);
}
void clear()
{
	REP(i, 1, cur) ch[i][0] = ch[i][1] = 0;
	cur = rt = 0;
}

signed main()
{
#ifdef CraZYali
	file("A");
#endif
	n = read<int>();
	REP(i, 2, n)
		G[fa[i] = read<int>()].emplace_back(i);
	int A, B;
	REP(i, 1, n)
	{
		insert(rt, a[i] = read<int>(), 61);
		int tmp = query(rt, a[i], 61);
		if (chkmax(tot, tmp)) A = i;
	}
	memset(Ans, -1, sizeof Ans);
	REP(i, 1, n)
		if ((a[A] ^ a[i]) == tot) B = i;

	memset(t, 0, sizeof t);ans = 0;
	for (int x = A; x; x = fa[x]) t[x] = 1;
	clear();dfs(1);

	
	memset(t, 0, sizeof t);ans = 0;
	for (int x = B; x; x = fa[x]) t[x] = 1;
	clear();dfs(1);

	REP(i, 1, n) printf("%lld\n", Ans[i] == -1 ? tot : Ans[i]);
	return 0;
}
