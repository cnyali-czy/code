//test
/*
 * File Name:	mmt.cpp
 * Author	:	CraZYali
 * Year		:	2019.09.28 19:31
 * Email	:	yms-chenziyang@outlook.com
 */

#define DREP(i, s, e) for (register int i(s), end_##i(e); i >= end_##i; i--)
#define  REP(i, s, e) for (register int i(s), end_##i(e); i <= end_##i; i++)
#define DEBUG fprintf(stderr, "Passing [%s] in Line %d\n", __FUNCTION__, __LINE__)

#define chkmax(a, b) a = max(a, (b))
#define chkmin(a, b) a = min(a, (b))

#include <iostream>
#include <cstdio>
#include <cmath>

using namespace std;
const int maxn = 1e5 + 10, MOD = 123456789;

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

int n, a[maxn], b[maxn], c[maxn];

int main()
{
#ifdef CraZYali
	file("mmt");
#endif
	cin >> n;
	REP(i, 1, n) a[i] = read<int>();
	REP(i, 0, n - 1) b[i] = read<int>();
	REP(i, 1, sqrt(n))
		REP(j, 0, i - 1)
		{
			long long now(-1);
			int A, l, r;
			for (int k(j + i); k <= n; k += i)
			{
				if (k / (k / i) != i) continue;
				if (now == -1)
				{
					l = r = k / i;
					A = k % r;
					now = 1ll * a[i] * b[A] % MOD;
				}
				else
				{
					r++;
					if (k / l != i) l++;
					else
					{
						A = k % l;
						(now += 1ll * a[i] * b[A] % MOD) %= MOD;
					}
				}
				(c[k] += now) %= MOD;
			}
		}
	int siz = sqrt(n);
	REP(i, 1, n)
		REP(j, 1, i)
			if (i / j <= siz) break;
			else (c[i] += 1ll * a[i / j] * b[i % j] % MOD) %= MOD;
	REP(i, 1, n)
		printf("%d\n", (c[i] + MOD) % MOD);
	return 0;
}
