#define  REP(i, s, e) for (register int i(s), end_##i(e); i <= end_##i; i++)
#define DREP(i, s, e) for (register int i(s), end_##i(e); i >= end_##i; i--)

#include <iostream>
#include <cstdio>

using namespace std;

namespace run
{
	using namespace std;

	int main()
	{
		int a, b, c, d;
		cin >> a >> b >> c >> d;
		if (a >= b + 2 || d >= c + 2)
		{
			puts("NO");
			return 0;
		}
		if (a == b + 1 && !c && !d)
		{
			puts("YES");
			printf("0");
			REP(i, 1, b) printf(" 1 0");
		}
		else if (d == c + 1 && !a && !b)
		{
			puts("YES");
			printf("3");
			REP(i, 1, c) printf(" 2 3");
		}
		else
		{
			b -= a;
			c -= d;

			if (b >= 0 && c >= 0 && abs(b - c) < 2)
				if (b > c)
				{
					puts("YES");
					printf("1");
					REP(i, 1, a) printf(" 0 1");
					REP(i, 1, c) printf(" 2 1");
					REP(i, 1, d) printf(" 2 3");
				}
				else
				{
					puts("YES");
					REP(i, 1, a) printf("0 1 ");
					REP(i, 1, b) printf("2 1 ");
					REP(i, 1, d) printf("2 3 ");
					if (b < c) printf("2");
			}
			else puts("NO");
		}
		return 0;
	}
}
int main()
{
#ifdef CraZYali
	freopen("B.in", "r", stdin);
	freopen("B.out", "w", stdout);
#endif
	return run::main();
	int a, b, c, d;
	cin >> a >> b >> c >> d;
	if (b == a)
	{
		int qaq = b - a;
		int qaq2 = b - a + 1;
		if (c >= qaq2)
		{
			int qaqaq2 = c - (b - a + 1);
			if (d == qaqaq2 + 1 || d == qaqaq2)
			{
				puts("YES");
				REP(i, 1, a) printf("0 1 ");
				REP(i, 1, b - a) printf("2 1 ");
				if (c) printf("2 ");
				REP(i, 1, d) printf("3 2 ");
				if (d == qaqaq2 + 1) printf("3");
				return 0;
			}
		}
	}
	if (b == a + 1)
	{
		int qaq2 = b - a + 2;
		if (c >= qaq2)
		{
			int qaqaq2 = c - (b - a);
			if (d == qaqaq2 || d == qaqaq2 + 1)
			{
				puts("YES");
				REP(i, 1, a) printf("1 0 ");
				if (b) printf("1 ");
				REP(i, 1, b - a - 1) printf("2 1 ");
				printf("2 ");
				REP(i, 1, d) printf("3 2 ");
				if (d == qaqaq2 + 1) printf("3");
			}

		}
	}
	puts("NO");
	return 0;
}
