/*
	Problem:	C.cpp
	Time:		2020-02-24 00:30
	Author:		CraZYali
	E-Mail:		yms-chenziyang@outlook.com 
*/

#define REP(i, s, e) for (register int i(s), end_##i(e); i <= end_##i; i++)
#define DEP(i, s, e) for (register int i(s), end_##i(e); i >= end_##i; i--)
#define DEBUG fprintf(stderr, "Passing [%s] in Line %d\n", __FUNCTION__, __LINE__)

#define chkmax(a, b) (a < (b) ? a = (b) : a)
#define chkmin(a, b) (a > (b) ? a = (b) : a)

#include <set>
#include <iostream>
#include <cstdio>

using namespace std;
const int maxn = 200 + 5;

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

int n, a[maxn], b[maxn], vis[maxn];
set <int> S;

int main()
{
#ifdef CraZYali
	file("C");
#endif
	register int T = read<int>();
	while (T--)
	{
		n = read<int>();
		REP(i, 1, n + n) vis[i] = 0;
		bool flag = 1;
		REP(i, 1, n)
		{
			vis[b[i] = read<int>()]++;
			if (vis[b[i]] >= 2) flag = 0;
		}
		if (!flag) {puts("-1");continue;}
		S.clear();
		REP(i, 1, n + n) if (!vis[i]) S.emplace(i);
		REP(i, 1, n)
		{
			auto it = S.lower_bound(b[i]);
			if (it == S.end())
			{
				flag = 0;
				break;
			}
			a[i * 2 - 1] = b[i];
			a[i * 2] = *it;
			S.erase(it);
		}
		if (!flag) {puts("-1");continue;}
		else REP(i, 1, n + n) printf("%d%c", a[i], i == end_i ? '\n' : ' ');
	}
	return 0;
}
