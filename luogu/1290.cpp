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

int m, n, k;
bool play(int a, int b)
{
	if (!b) return 0;
	if (a / b == 1) return !play(b, a % b);
	return 1;
}

int main()
{
#ifdef CraZYali
	freopen("1290.in", "r", stdin);
	freopen("1290.out", "w", stdout);
#endif
	register int T = read<int>();
	while (T --> 0)
	{
		int a, b;
		a = read<int>();
		b = read<int>();
		if (!play(max(a, b), min(a, b)))	printf("Ollie wins\n");
		else 								printf("Stan wins\n");
	}


	return 0;
}
