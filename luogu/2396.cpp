#define  REP(i, s, e) for (register int i = s; i <= e; i++)
#define DREP(i, s, e) for (register int i = s; i >= e; i--)
#define DEBUG fprintf(stderr, "Passing [%s] in Line %d\n", __FUNCTION__, __LINE__)

#define chkmax(a, b) a = max(a, b)
#define chkmin(a, b) a = min(a, b)

#include <bits/stdc++.h>

using namespace std;
#define getchar getchar_unlocked
const int maxn = 25;

char c;
template <typename T> T read()
{
	T ans = 0, p = 1;
	c = getchar();
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

int n, m, b[maxn], LIM, dp[1 << maxn] = {1}, dis[1 << maxn];
const int MOD = 1e9 + 7;

int main()
{
#ifdef CraZYali
	freopen("2396.in", "r", stdin);
	freopen("2396.out", "w", stdout);
#endif
	n = read<int>();
	REP(i, 1, n) *(dis + (1 << (i - 1))) = read<int>();
	m = read<int>();
	REP(i, 1, m) *(b + i - 1) = read<int>();
	LIM = (1 << n) - 1;
	REP(i, 1, LIM)
	{
		*(dis + i) = *(dis + (i ^ (i & -i))) + *(dis + (i & -i));
		if (*(dis + i) == *b || *(dis + i) == *(b+1)) continue;
		for (register int j = i, k = j & -j;j;j ^= k, k = j & -j)
		{
			*(dp + i) += *(dp + (i ^ k));
			if (*(dp + i) >= MOD) *(dp + i) %= MOD;
		}
	}

	cout << *(dp+LIM) % MOD;
	return 0;
}
