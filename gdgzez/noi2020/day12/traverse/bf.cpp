/*
	Problem:	traverse.cpp
	Time:		2020-06-12 10:24
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
#define int long long
using namespace std;
const int maxn = 1e5 + 10;

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

int sa[maxn], sd[maxn], sk[maxn], t[maxn], k, ccc[maxn];
int work(int n, int d[])
{
	REP(i, 1, n) sa[i] = sa[i - 1] + t[i], sd[i] = sd[i - 1] + d[i];
	int kk = k;
	int End = n;
	REP(i, 1, n - 1)
	{
		sk[i] = sk[i - 1];
		if (sk[i] + sa[i] < sd[i])
		{
			int delta = sd[i] - sk[i] - sa[i];
			sk[i] += delta;
		}
		if (sk[i] > k) {End = i;break;}
		ccc[i] = max(ccc[i - 1], sa[i] + sk[i] - sd[i - 1]);
	}
	DEP(i, End, 1) if (sa[i] - sd[i - 1] + k >= ccc[i - 1]) return i;
	return 1;
}
int n, d[maxn], a[maxn];

signed main()
{
#ifdef CraZYali
	file("traverse");
#endif
	n = read<int>();k = read<int>();
	REP(i, 1, n - 1) d[i] = read<int>();
	REP(i, 1, n) a[i] = read<int>();
	int ans = 1;
	REP(i, 1, n)
	{
		REP(j, 1, n - i + 1) t[j] = a[i + j - 1];
		int x = work(n - i + 1, d + i - 1);
		if (ans < x) ans = x;
	}
	cout << ans << endl;
	return 0;
}
