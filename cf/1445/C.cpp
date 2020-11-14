/*
	Problem:	C.cpp
	Time:		2020-11-01 19:18
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
		ans = ans * 10 + (c - 48);
		c = getchar();
	}
	return ans * flag;
}

#define file(FILE_NAME) freopen(FILE_NAME".in", "r", stdin), freopen(FILE_NAME".out", "w", stdout)

signed main()
{
#ifdef CraZYali
	file("C");
#endif
	register int T = read<int>();
	while (T--)
	{
		int p, q;
		scanf("%lld%lld", &p, &q);
		static pair <int, int> stk[100000 + 10];
		int top = 0;
		for (int i = 2; i * i <= q; i++) if (q % i == 0)
		{
			int k = 0;
			while (q % i == 0)
			{
				k++;
				q /= i;
			}
			stk[++top] = make_pair(i, k);
		}
		if (q > 1) stk[++top] = make_pair(q, 1);
		int x = 1;
		int z = p;
		REP(i, 1, top)
			while (z % stk[i].first == 0)
				z /= stk[i].first;
		int ans = 1;
		REP(i, 1, top) 
		{
			int x = 1;
			REP(j, 1, top) if (p % stk[j].first == 0)
			{
				int times = 0;
				int P = p;
				while (P % stk[j].first == 0)
				{
					P /= stk[j].first;
					x *= stk[j].first;
					times++;
					if (i == j && times >= stk[j].second)
					{
						x /= stk[j].first;
						break;
					}
				}
			}
			if (ans < x * z) ans = x * z;
		}
		printf("%lld\n", ans);
	}
	return 0;
}
