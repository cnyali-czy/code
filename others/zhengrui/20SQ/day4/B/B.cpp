/*
	Problem:	B.cpp
	Time:		2020-08-07 22:52
	Author:		CraZYali
	E-Mail:		yms-chenziyang@outlook.com 
*/

#define REP(i, s, e) for (register int i(s), end_##i(e); i <= end_##i; i++)
#define DEP(i, s, e) for (register int i(s), end_##i(e); i >= end_##i; i--)
#define DEBUG fprintf(stderr, "Passing [%s] in Line %d\n", __FUNCTION__, __LINE__)

#include <iostream>
#include <cstdio>
#include <algorithm>

#define i64 long long
using namespace std;
const int maxn = 3e5 + 10;
const i64 inf = 1e18;

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

int n, x;
int a[maxn];
i64 dp[maxn];

inline bool chkmin(i64 &x, i64 y) {if (x > y) {x = y;return 1;}return 0;}
#define val first
#define f second

int s[maxn];
void add(int x, int y)
{
	while (x <= n)
	{
		s[x] += y;
		x += x & -x;
	}
}
int sum(int x)
{
	int res = 0;
	while (x > 0)
	{
		res += s[x];
		x &= (x - 1);
	}
	return res;
}

int cl = 1, cr = 1;
i64 nxd;

i64 calc(int l, int r)
{
	while (cr < r)
	{
		cr++;
		add(a[cr], 1);
		nxd += cr - cl + 1 - sum(a[cr]);
	}
	while (cl > l)
	{
		cl--;
		nxd += sum(a[cl]);
		add(a[cl], 1);
	}
	while (cr > r)
	{
		nxd -= cr - cl + 1 - sum(a[cr]);
		add(a[cr], -1);
		cr--;
	}
	while (cl < l)
	{
		add(a[cl], -1);
		nxd -= sum(a[cl]);
		cl++;
	}
	return nxd;
}

void solve(int l, int r, int L, int R)
{
	if (l > r || L > R) return;
	int mid = L + R >> 1;
	int bst = 0;
	i64 Min = inf;
	REP(j, l, r)
	{
		i64 tmp = dp[j - 1] + x + calc(j, mid);
		if (chkmin(Min, tmp)) bst = j;
	}
	chkmin(dp[mid], Min);
	solve(l, bst, L, mid - 1);
	solve(bst, r, mid + 1, R);
}

void cdq(int l, int r)
{
	if (l == r)
	{
		chkmin(dp[l], dp[l - 1] + x);
		return;
	}
	int mid = l + r >> 1;
	cdq(l, mid);

	solve(l, mid, mid + 1, r);

	cdq(mid + 1, r);
}

int main()
{
#ifdef CraZYali
	file("B");
#endif
	n = read<int>();x = read<int>();
	REP(i, 1, n)
	{
		a[i] = read<int>();
		dp[i] = inf;
	}
	add(a[1], 1);
	cdq(1, n);
	cout << dp[n] << endl;
	return 0;
}
