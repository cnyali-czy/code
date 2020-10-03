/*
	Problem:	C.cpp
	Time:		2020-09-30 20:30
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
const int maxn = 1e5 + 10, inf = 1e18 + 1;

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

int n, q, a[maxn];
int l, r, k;

int getmin(int l, int r)
{
	if (l > r) return inf;
	int ans = a[l];
	REP(i, l + 1, r) ans = min(ans, a[i]);
	return ans;
}

namespace bf
{
	bool judge(int x)
	{
		static int stk[maxn], top;
		int s = 0;
		top = 0;
		REP(i, l, r) if (a[i] <= x / 2)
		{
			s++;
			stk[++top] = i;
		}
		REP(i, 2, top)
		{
			int qaq = getmin(stk[i - 1] + 1, stk[i] - 1);
			if (max(a[stk[i - 1]], a[stk[i]]) + qaq <= x) s++;
		}
		int Min = min(getmin(l, stk[1] - 1), getmin(stk[top] + 1, r));
		if (Min + max(a[stk[1]], a[stk[top]]) <= x) s++;
		return s >= k;
	}
	void work()
	{
		while (q--)
		{
			l = read<int>();r = read<int>();k = read<int>();
			int L = getmin(l, r) << 1, R = 2e9 + 114514, ans = R + 1;
			while (L <= R)
			{
				int mid = L + R >> 1;
				if (judge(mid))
				{
					ans = mid;
					R = mid - 1;
				}
				else L = mid + 1;
			}
			printf("%lld\n", ans);
		}
	}
}

signed main()
{
#ifdef CraZYali
	file("C");
#endif
	n = read<int>();q = read<int>();
	REP(i, 1, n) a[i] = read<int>();
	bf :: work();
	return 0;
}
