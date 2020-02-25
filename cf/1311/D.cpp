/*
	Problem:	D.cpp
	Time:		2020-02-24 22:54
	Author:		CraZYali
	E-Mail:		yms-chenziyang@outlook.com 
*/

#define REP(i, s, e) for (register int i(s), end_##i(e); i <= end_##i; i++)
#define DEP(i, s, e) for (register int i(s), end_##i(e); i >= end_##i; i--)
#define DEBUG fprintf(stderr, "Passing [%s] in Line %d\n", __FUNCTION__, __LINE__)

#define chkmax(a, b) (a < (b) ? a = (b) : a)
#define chkmin(a, b) (a > (b) ? a = (b) : a)

#include <ctime>
#include <cmath>
#include <iostream>
#include <cstdio>
#define int long long

using namespace std;

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

signed main()
{
#ifdef CraZYali
	file("D");
#endif
	register int T = read<int>();
	while (T--)
	{
		int a(read<int>()), b(read<int>()), c(read<int>()), ans = 1e9, ansa, ansb, ansc;
		REP(ta, 1, 30000)
		{
			int res = abs(a - ta);
			if (res >= ans) continue;
			REP(kb, 1, 114514)
			{
				long long tb = ta * kb;
				if (tb > 30000) break;
				res += abs(b - tb);
				if (res < ans)
					REP(kc, 1, 114514)
					{
						int tc = tb * kc;
						if (tc > 30000) break;
						res += abs(tc - c);
						if (res < ans)
						{
							ans = res;
							ansa = ta;
							ansb = tb;
							ansc = tc;
						}
						else if (tc >= c)
						{
							res -= abs(tc - c);
							break;
						}
						res -= abs(tc - c);
					}
				else if (tb >= b)
				{
					res -= abs(b - tb);
					break;
				}
				res -= abs(b - tb);
			}
		}
		cout << ans << '\n' << ansa << ' ' << ansb << ' ' << ansc << '\n';
	}
#ifdef CraZYali
	cerr<<clock()*1./CLOCKS_PER_SEC<<endl;
#endif
	return 0;
}
