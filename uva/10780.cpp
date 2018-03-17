#define DREP(i, s, e) for(register int i = s; i >= e ;i--)
#define  REP(i, s, e) for(register int i = s; i <= e ;i++)

#define DEBUG fprintf(stderr, "Passing [%s] in Line %d\n", __FUNCTION__, __LINE__)
#define chkmax(a, b) a = max(a, b)
#define chkmin(a, b) a = min(a, b)

#include <algorithm>
#include <iostream>
#include <cstdlib>
#include <cstring>
#include <cstdio>
#include <bitset>
#include <vector>
#include <cmath>
#include <queue>
#include <map>
#include <set>

using namespace std;
const int maxn = 10010, maxm = 5010, inf = (((1 << 30) - 1) << 1) + 1;

template <typename T> T read()
{
	T ans(0), p(1);
	char c = getchar();
	while (!isdigit(c)) {
		if (c == '-') p = -1;
		c = getchar();
	}
	while (isdigit(c)) {
		ans = ans * 10 + c - 48;
		c = getchar();
	}
	return ans * p;
}
int m, n, k;

inline void divide(int x, int A[])
{
	for (register int i = 2; i * i <= x ; i++)
		if (x % i == 0)
		{
			A[i]++;
			x /= i;
			i--;
		}
	A[x]++;
}
int A[maxn], B[maxm];

int main()
{
#ifdef CraZYali
	freopen("10780.in", "r", stdin);
	freopen("10780.out", "w", stdout);
#endif
	register int T = read<int>();
	REP(Case, 1, T)
	{
		m = read<int>();
		n = read<int>();
		memset(A, 0, sizeof(A));
		memset(B, 0, sizeof(B));
		REP(i, 2, n) divide(i, A);
		divide(m, B);
		k = inf;
		REP(i, 1, m)
			if (B[i]) chkmin(k, A[i] / B[i]);
		printf("Case %d:\n", Case);
		if (!k) printf("Impossible to divide\n");
		else printf("%d\n", k);
	}

	return 0;
}
