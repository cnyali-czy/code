#define  REP(i, s, e) for (register int i(s), end_##i(e); i <= end_##i; i++)
#define DREP(i, s, e) for (register int i(s), end_##i(e); i >= end_##i; i--)

#include <iostream>
#include <cstdio>
using namespace std;

namespace run
{
	const int maxn = 4e5 + 10;
	int T, n, p[maxn];
	int main()
	{
		cin >> T;
		while (T--)
		{
			scanf("%d", &n);
			REP(i, 1, n) scanf("%d", p + i);
			int g(0), b(0), s(0);
			REP(i, 1, n - 1)
				if (p[i] ^ p[i+1])
				{
					g = i;
					break;
				}
			if (!g)
			{
				puts("0 0 0");
				continue;
			}
			REP(i, g + 1, n - 1)
				if (p[i] ^ p[i+1] && i - g > g)
				{
					s = i - g;
					break;
				}
			if (!s)
			{
				puts("0 0 0");
				continue;
			}
			REP(i, g + s, n / 2)
				if (p[i] ^ p[i+1]) b = i - g - s;
			if (g >= b) puts("0 0 0");
			else printf("%d %d %d\n", g, s, b);
		}
		return 0;
	}
}

int main()
{
#ifdef CraZYali
	freopen("A.in", "r", stdin);
	freopen("A.out", "w", stdout);
#endif
	return run::main();
}
