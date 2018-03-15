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

inline int gcd(int a, int b) {return !b ? a : gcd(b, a % b);}

int main()
{
#ifdef CraZYali
	freopen("11889.in", "r", stdin);
	freopen("11889.out", "w", stdout);
#endif
	register int T = read<int>();
	while (T--)
	{
		register int A, B, C;
		A = read<int>();C = read<int>();
		if (C % A)
		{
			printf("NO SOLUTION\n");
			continue;
		}
		B = C / A;
		register int G = gcd(A, B), k(1);
		while (G ^ 1)
		{
			k *= G;
			A /= G;
			G = gcd(A, B);
		}
		printf("%d\n", B * k);
	}
	return 0;
}
