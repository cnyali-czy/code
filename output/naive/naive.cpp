/*
	Problem:	naive.cpp
	Time:		2020-09-28 15:36
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
#define i64 long long
using namespace std;
const int maxn = 5e4 + 10;
const i64 inf = 1e15;

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

int n, k;
int p[maxn];

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
	int y = 0;
	while (x > 0)
	{
		y += s[x];
		x &= (x - 1);
	}
}
i64 f[maxn], g[maxn];

int l, r;
i64 cur;
i64 w(int L, int R)
{
	while (r < R)
	{
		++r;
		cur += sum(p[r]);
		add(p[r], 1);
	}
	while (l > L)
	{
		--l;
		cur += r - l - sum(p[l]);
		add(p[l], 1);
	}
	while (r > R)
	{
		add(p[r], -1);
		cur -= sum(p[r]);
		r--;
	}
	while (l < L)
	{
		add(p[l], -1);
		cur -= r - l - sum(p[l]);
		l++;
	}
	return cur;
}

int main()
{
	file("naive");
	n = read<int>();k = read<int>();
	REP(i, 1, n) p[i] = read<int>();
	REP(i, 1, n) f[i] = inf;
	l = 1;
	REP(i, 1, k)
	{
		swap(f, g);
		solve(1, n, 1, n);
	}
	cout << f[n] << endl;
	return 0;
}
