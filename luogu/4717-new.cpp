#define REP(i, s, e) for (register int i = (s), end_##i = (e); i <= end_##i; i++)
#define DEP(i, s, e) for (register int i = (s), end_##i = (e); i >= end_##i; i--)
#define DEBUG fprintf(stderr, "Passing [%s] in Line %d\n", __FUNCTION__, __LINE__)

#define chkmax(a, b) (a < (b) ? a = (b) : a)
#define chkmin(a, b) (a > (b) ? a = (b) : a)

#include <algorithm>
#include <iostream>
#include <cassert>
#include <cstring>
#include <cstdlib>
#include <cstdio>
#include <vector>
#include <cmath>

using namespace std;
const int maxn = 17;

template <typename T> T read()
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

void file(string s)
{
	freopen((s + ".in").c_str(), "r", stdin);
	freopen((s + ".out").c_str(), "w", stdout);
}

int n;
int a[1 << maxn], b[1 << maxn], c[1 << maxn], ta[1 << maxn], tb[1 << maxn];
#define i64 long long
const int flag_or = 0, flag_and = 1, flag_xor = 2;
const int MOD = 998244353, inv2 = MOD + 1 >> 1;
namespace FWT
{
	inline int add(int x, int y) {return (x += y) >= MOD ? x - MOD : x;}
	inline int sub(int x, int y) {return (x -= y) <    0 ? x + MOD : x;}
	inline void inc(int &x, int y) {x += y;if (x >= MOD) x -= MOD;}
	inline void dec(int &x, int y) {x -= y;if (x <    0) x += MOD;}
	void fwt(int a[], int n, int flag, int opt)
	{
		const int N = 1 << n;
		if (flag == flag_or)
		{
			REP(i, 0, n - 1)
			{
				const int i2 = 1 << i;
				for (int j = 0; j < N; j += i2 + i2)
					REP(k, 0, i2 - 1)
						if (opt == 1)	inc(a[j + k + i2], a[j + k]);
						else			dec(a[j + k + i2], a[j + k]);
			}
		}
		if (flag == flag_and)
		{
			REP(i, 0, n - 1)
			{
				const int i2 = 1 << i;
				for (int j = 0; j < N; j += i2 + i2)
					REP(k, 0, i2 - 1)
						if (opt == 1)	inc(a[j + k], a[j + k + i2]);
						else			dec(a[j + k], a[j + k + i2]);
			}
		}
		if (flag == flag_xor)
		{
			REP(i, 0, n - 1)
			{
				const int i2 = 1 << i;
				for (int j = 0; j < N; j += i2 + i2)
					REP(k, 0, i2 - 1)
					{
						int x(a[j + k]), y(a[j + k + i2]);
						a[j + k] = opt == 1 ? add(x, y) : 1ll * inv2 * add(x, y) % MOD;
						a[j + k + i2] = opt == 1 ? sub(x, y) : 1ll * inv2 * sub(x, y) % MOD;
					}
			}
		}
	}
}

int main()
{
#ifdef CraZYali
	file("4717-new");
#endif
	n = read<int>();
	const int N = 1 << n;
	REP(i, 0, N - 1) a[i] = read<int>();
	REP(i, 0, N - 1) b[i] = read<int>();
	copy(a, a + N, ta);FWT::fwt(ta, n, flag_or, 1);
	copy(b, b + N, tb);FWT::fwt(tb, n, flag_or, 1);
	REP(i, 0, N - 1) c[i] = 1ll * ta[i] * tb[i] % MOD;
	FWT::fwt(c, n, flag_or, -1);
	REP(i, 0, N - 1) printf("%d%c", c[i], i == end_i ? '\n' : ' ');
	copy(a, a + N, ta);FWT::fwt(ta, n, flag_and, 1);
	copy(b, b + N, tb);FWT::fwt(tb, n, flag_and, 1);
	REP(i, 0, N - 1) c[i] = 1ll * ta[i] * tb[i] % MOD;
	FWT::fwt(c, n, flag_and, -1);
	REP(i, 0, N - 1) printf("%d%c", c[i], i == end_i ? '\n' : ' ');
	copy(a, a + N, ta);FWT::fwt(ta, n, flag_xor, 1);
	copy(b, b + N, tb);FWT::fwt(tb, n, flag_xor, 1);
	REP(i, 0, N - 1) c[i] = 1ll * ta[i] * tb[i] % MOD;
	FWT::fwt(c, n, flag_xor, -1);
	REP(i, 0, N - 1) printf("%d%c", c[i], i == end_i ? '\n' : ' ');
	return 0;
}
