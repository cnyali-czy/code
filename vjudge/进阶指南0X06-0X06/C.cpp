#pragma GCC optimize(3,"Ofast","inline")
#define  REP(i, s, e) for (int i = s; i <= e; i++)
#define DREP(i, s, e) for (int i = s; i >= e; i--)
#define DEBUG fprintf(stderr, "Passing [%s] in Line %d\n", __FUNCTION__, __LINE__)

#define chkmax(a, b) a = max(a, b)
#define chkmin(a, b) a = min(a, b)

#include <iostream>
#include <cstdio>
#include <cmath>

using namespace std;
const int maxn = 100000 + 10;

template <typename T> T read()
{
	T ans = 0, p = 1;
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

int Min[maxn][20], n, q;
int get_min(int l, int r)
{
	int LOG = 0;
	while ((1 << (LOG + 1)) <= r - l + 1) LOG++;
	return min(Min[l][LOG], Min[r-(1<<LOG)+1][LOG]);
}

int main()
{
#ifdef CraZYali
	freopen("C.in", "r", stdin);
	freopen("C.out", "w", stdout);
#endif
	register int T = read<int>();
	while (T --> 0)
	{
		n = read<int>();
		REP(i, 1, n) Min[i][0] = read<int>();
		int LOG = log2(n);
		REP(j, 1, LOG)
			REP(i, 1, n)
			if (i + (1 << j) - 1 <= n) Min[i][j] = min(Min[i][j-1], Min[i+(1<<j-1)][j-1]);
		q = read<int>();
		while (q --> 0)
		{
			int l = read<int>(), r = read<int>();
			int now = Min[l][0];
			while (l + 1 <= r)
			{
				int L = l + 1, R = r, pos = r;
				while (L <= R)
				{
					int mid = L + R >> 1;
					if (get_min(l + 1, mid) <= now)
					{
						pos = mid;
						R = mid - 1;
					}
					else L = mid + 1;
				}
				now %= get_min(l + 1, pos);
				l = pos;
			}
			printf("%d\n", now);
		}
	}
	return 0;
}
