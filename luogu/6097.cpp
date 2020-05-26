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
const int maxn = 20;

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
int a[1 << maxn], b[1 << maxn], A[maxn + 1][1 << maxn], B[maxn + 1][1 << maxn], cnt[1 << maxn], C[maxn + 1][1 << maxn], t[1 << maxn];
#define i64 long long
const int MOD = 1e9 + 9, inv2 = MOD + 1 >> 1;
inline int add(int x, int y) {return (x += y) >= MOD ? x - MOD : x;}
inline int sub(int x, int y) {return (x -= y) <    0 ? x + MOD : x;}
inline void inc(int &x, int y) {x += y;if (x >= MOD) x -= MOD;}
inline void dec(int &x, int y) {x -= y;if (x <    0) x += MOD;}
void fwt(int a[], int n, int opt)
{
	const int N = 1 << n;
	REP(i, 0, n - 1)
	{
		const int i2 = 1 << i;
		for (int j = 0; j < N; j += i2 + i2)
			REP(k, 0, i2 - 1)
				if (opt == 1)	inc(a[j + k + i2], a[j + k]);
				else			dec(a[j + k + i2], a[j + k]);
	}
}

int main()
{
#ifdef CraZYali
	file("6097");
#endif
	n = read<int>();
	const int N = 1 << n;
	REP(i, 0, N - 1) cnt[i] = cnt[i >> 1] + (i & 1);
	REP(i, 0, N - 1) A[cnt[i]][i] = read<int>();
	REP(i, 0, N - 1) B[cnt[i]][i] = read<int>();
	REP(i, 0, n)
	{
		fwt(A[i], n, 1);
		fwt(B[i], n, 1);
	}
	REP(u, 0, n)
		REP(v, 0, n - u)
		REP(i, 0, N - 1) inc(C[u + v][i], 1ll * A[u][i] * B[v][i] % MOD);
	REP(u, 0, n) fwt(C[u], n, -1);
	REP(i, 0, N - 1) printf("%d%c", C[cnt[i]][i], i == end_i ? '\n' : ' ');
	return 0;
}
