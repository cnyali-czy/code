/*
	Problem:	4570.cpp
	Time:		2020-08-10 08:30
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
const int maxn = 1000 + 10;

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

int n, a[maxn], v[maxn];
namespace basis
{
	int p[70], v[70];
	void ins(int x, int orzjjs)
	{
		DEP(i, 61, 0) if (x >> i & 1)
			if (!p[i])
			{
				p[i] = x;
				v[i] = orzjjs;
				return;
			}
			else
			{
				if (orzjjs > v[i])
				{
					swap(x, p[i]);
					swap(orzjjs, v[i]);
				}
				x ^= p[i];
			}
	}
}
signed main()
{
#ifdef CraZYali
	file("4570");
#endif
	n = read<int>();
	REP(i, 1, n)
	{
		int a = read<int>(), v = read<int>();
		basis :: ins(a, v);
	}
	int ans = 0;
	REP(i, 0, 61) ans += basis :: v[i];
	cout << ans << endl;
	return 0;
}
