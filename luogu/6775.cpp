/*
	Problem:	6775.cpp
	Time:		2020-08-30 18:58
	Author:		CraZYali
	E-Mail:		yms-chenziyang@outlook.com 
*/

#define REP(i, s, e) for (register int i(s), end_##i(e); i <= end_##i; i++)
#define DEP(i, s, e) for (register int i(s), end_##i(e); i >= end_##i; i--)
#define DEBUG fprintf(stderr, "Passing [%s] in Line %d\n", __FUNCTION__, __LINE__)

#define chkmax(a, b) (a < (b) ? a = (b) : a)
#define chkmin(a, b) (a > (b) ? a = (b) : a)

#include <cassert>
#include <algorithm>
#include <iostream>
#include <cstdio>

using namespace std;
const int maxn = 500 + 5, maxm = 5000 + 10;

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

int n, m, k, a[maxn];
bool flag;

bool t[maxm];
int I[maxm], X[maxm], J[maxm], Y[maxm];

void output(int End = m)
{
	REP(i, 1, End)
		if (t[i]) printf("%d %d %d %d\n", I[i], X[i], J[i], Y[i]);
		else printf("%d %d\n", I[i], X[i]);
}

void dfs(int x)
{
	if (flag) return;
//	REP(i, 1, n) printf("%d%c", a[i], i == end_i ? '\n' : ' ');
//	output(x);puts("");
	if (x == m)
	{
		flag = 1;
		output();
	}
	else
	{
		x++;
		int Min = 0;
		REP(i, 1, n) if (a[i] && (!Min || a[i] < a[Min])) Min = i;
		if (a[Min] > k) return;
		if (a[Min] == k)
		{
			t[x] = 0;
			I[x] = Min;
			X[x] = k;
			a[Min] = 0;
			dfs(x);
			if (flag) return;
			a[Min] = k;
		}
		REP(i, 1, n) if (i != Min && a[i] && a[i] + a[Min] >= k)
		{
			t[x] = 1;
			I[x] = Min;
			J[x] = i;
			X[x] = a[Min];a[Min] -= X[x];
			Y[x] = k - X[x];a[i] -= Y[x];
			dfs(x);
			if (flag) return;
			a[Min] += X[x];a[i] += Y[x];
/*
			if (a[i] > k) continue;
			Y[x] = a[i];a[i] -= Y[x];
			X[x] = k - Y[x];a[Min] -= X[x];
			dfs(x);
			if (flag) return;
			a[Min] += X[x];a[i] += Y[x];
			*/
		}
	}
}

namespace shit
{
	void work()
	{
		int N = 0;
		REP(i, 1, n)
			while (a[i] >= k)
			{
				++N;
				if (N > m) goto gg;
				I[N] = i;
				X[N] = k;
				a[i] -= k;
			}
		while (1)
		{
			int Min = 0, Max = 0;
			REP(i, 1, n) if (a[i] && (!Min || a[i] < a[Min])) Min = i;
			REP(i, 1, n) if (a[i] && (!Max || a[i] > a[Max]) && Max != Min) Max = i;
			++N;
			if (N > m) goto gg;
			if (a[Min] + a[Max] < k) goto gg;
			I[N] = Min;J[N] = Max;
			X[N] = a[Min];Y[N] = k - a[Min];
			a[Min] -= X[N];a[Max] -= Y[N];
		}
		if (N == m) output();
		
gg:		puts("-1");
	}
}

int main()
{
#ifdef CraZYali
	file("6775");
#endif
	register int T = read<int>();
	REP(Case, 1, T)
	{
		n = read<int>();
		m = read<int>();
		k = read<int>();
		REP(i, 1, n) a[i] = read<int>();
		if (m > n - 2)
		{
			shit :: work();
			continue;
		}
		flag = 0;
		dfs(0);
		if (!flag) puts("-1");
	}
	return 0;
}
