#define  REP(i, s, e) for(register int i = s; i <= e ;i++)
#define DREP(i, s, e) for(register int i = s; i >= e ;i--)

#define DEBUG fprintf(stderr, "Passing [%s] in LINE %d\n", __FUNCTION__, __LINE__)
#define chkmin(a, b) a = min(a, b)
#define chkmax(a, b) a = max(a, b)

#include <bits/stdc++.h>

using namespace std;

template <typename T> T read()
{
	T ans(0), p(1);
	char c = getchar();
	while (!isdigit(c))
	{
		if (c == '-') p = -1;
		c = getchar();
	}
	while (isdigit(c))
	{
		ans = ans * 10 + c - 48;
		c = getchar();
	}
	return ans * p;
}

int a0, a1, b0, b1, A, B;

int gcd(int a, int b) {return !b ? a : gcd(b, a % b);}

int main()
{
#ifdef CraZYali
	freopen("1072.in", "r", stdin);
	freopen("1072.out", "w", stdout);
#endif
	register int T = read<int>();
	while (T --> 0)
	{
		a0 = read<int>();
		a1 = read<int>();
		b0 = read<int>();
		b1 = read<int>();
		A = a0 / a1;
		B = b1 / b0;
		register int ans = 0;
		for (register int x = 1; x * x <= b1 ;x++)
			if (b1 % x == 0)
			{
				if (x % a1 == 0 && gcd(x / a1, A) == 1 && gcd(b1 / x, B) == 1) ans++;
				register int y = b1 / x;
				if (x == y) continue;
				if (y % a1 == 0 && gcd(y / a1, A) == 1 && gcd(b1 / y, B) == 1) ans++;
			}
		printf("%d\n", ans);
	}

	return 0;
}
