/*
 * File Name:	3949.cpp
 * Author	:	CraZYali
 * Time		:	2020.01.18 19:24
 * Email	:	yms-chenziyang@outlook.com
 */

#define DEP(i, s, e) for (register int i(s), end_##i(e); i >= end_##i; i--)
#define REP(i, s, e) for (register int i(s), end_##i(e); i <= end_##i; i++)
#define DEBUG fprintf(stderr, "Passing [%s] in Line %d\n", __FUNCTION__, __LINE__)

#define chkmax(a, b) (a < (b) ? a = (b) : a) 
#define chkmin(a, b) (a > (b) ? a = (b) : a) 

#include <vector>
#include <cstring>
#include <iostream>
#include <cstdio>
#define int long long 
using namespace std;
const int maxn = 10000 + 10;

template <typename T> inline T read()
{
	T ans(0), flag(1);
	char c(getchar());
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

#define file(FILE_NAME) freopen(FILE_NAME".in", "r", stdin), freopen(FILE_NAME".out", "w", stdout);
int n, B, p[70];

inline void insert(int x)
{
	DEP(i, 62, 0) if (x & (1ll << i))
		if (!p[i])
		{
			p[i] = x;
			B++;
			DEP(k, i - 1, 0)	if (p[k] && (p[i] & (1ll << k))) p[i] ^= p[k];
			REP(k, i + 1, 62)	if (p[k] & (1ll << i)) p[k] ^= p[i];
			return;
		}
		else x ^= p[i];
}

signed main()
{
#ifdef CraZYali
	file("3949");
#endif
	REP(Case, 1, read<int>())
	{
		memset(p, 0, sizeof p);
		B = 0;
		REP(i, 1, n = read<int>()) insert(read<int>());
		bool flag = B < n;
		int tot = (1ll << B);
		printf("Case #%d:\n", Case);
		vector <int> v(B, 0);B = 0;
		REP(i, 0, 62) if (p[i]) v[B++] = p[i]; 
		REP(c, 1, read<int>())
		{
			int x = read<int>() - flag;
			if (x >= tot) puts("-1");
			else
			{
				int ans = 0;
				REP(i, 0, B - 1) if (x & (1ll << i)) ans ^= v[i];
				printf("%lld\n", ans);
			}
		}
	}
	return 0;
}
