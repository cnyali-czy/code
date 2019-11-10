//test
/*
 * File Name:	B.cpp
 * Author	:	CraZYali
 * Year		:	2019.11.09 22:31
 * Email	:	yms-chenziyang@outlook.com
 */

#define DREP(i, s, e) for (register int i(s), end_##i(e); i >= end_##i; i--)
#define  REP(i, s, e) for (register int i(s), end_##i(e); i <= end_##i; i++)
#define DEBUG fprintf(stderr, "Passing [%s] in Line %d\n", __FUNCTION__, __LINE__)

#define chkmax(a, b) (a < (b) ? a = (b) : a) 
#define chkmin(a, b) (a > (b) ? a = (b) : a) 

#include <iostream>
#include <cstdio>
#include <set>

using namespace std;

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

namespace run
{
	const int maxn = 1e6 + 10;

	int q, top;
	long long n, h[maxn], w[maxn], s;

	long long calc(const long long h, const long long w)
	{
		return h * (h + 1) / 2 + (n - w) * h;
	}

	int main()
	{
		cin >> n >> q;
		while (q--)
		{
			long long p(read<long long>());
			if (p > 0)
			{
				while (top && p + h[top] >= w[top])
				{
					s -= calc(h[top], w[top]);
					p += h[top--];
				}
				++top;
				h[top] = w[top] = min(p, n);
				s += calc(h[top], w[top]);
			}
			else
			{
				while (top && p + h[top] <= 0)
				{
					s -= calc(h[top], w[top]);
					p += h[top];
					top--;
				}
				if (top)
				{
					s -= calc(h[top], w[top]);
					s += calc(h[top] += p, w[top]);
				}
			}
			printf("%lld\n", s);
		}
		return 0;
	}
}

int main()
{
#ifdef CraZYali
	file("B");
#endif
	return run::main();
}
