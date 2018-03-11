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

int n, k, ans;

int main()
{
	freopen("zgl.out", "w", stdout);
	REP(N, 1, 100)
	{
		REP(K, 1, N - 1)
		{
			ans = 0;
			n = N;
			k = K;
			printf("[n, k] = [%d, %d]\n", n, k);
			REP(j, 1, n)
			{
				int tans = 0;
				REP(i, k, n)
					if ((i + j) % j >= k) printf("(%d, %d)\n", i, j);
			}
			puts("-------------");
		}
	}
	return 0;
}
