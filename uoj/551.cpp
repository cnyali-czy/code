/*
	Problem:	551.cpp
	Time:		2021-06-29 20:07
	Author:		CraZYali
	E-Mail:		yms-chenziyang@outlook.com 
*/

#define REP(i, s, e) for (register int i(s), end_##i(e); i <= end_##i; i++)
#define DEP(i, s, e) for (register int i(s), end_##i(e); i >= end_##i; i--)
#define DEBUG fprintf(stderr, "Passing [%s] in Line %d\n", __FUNCTION__, __LINE__)

#define chkmax(a, b) (a < (b) ? a = (b) : a)
#define chkmin(a, b) (a > (b) ? a = (b) : a)

#include <cstring>
#include <algorithm>
#include <iostream>
#include <cstdio>
#define i64 long long
#define u64 unsigned i64

using namespace std;
const int maxv = 65000 + 10, MOD = 998244353;

	template <typename T>
inline T read()
{
	T ans = 0, flag = 1;
	char c = getchar();
	while (!isdigit(c))
	{
		if (c == '-') flag = -1;
		c = getchar();
	}
	while (isdigit(c))
	{
		ans = ans * 10 + (c - 48);
		c = getchar();
	}
	return ans * flag;
}

#define file(FILE_NAME) freopen(FILE_NAME".in", "r", stdin), freopen(FILE_NAME".out", "w", stdout)

i64 power_pow(i64 base, int b)
{
	i64 ans = 1;
	while (b)
	{
		if (b & 1) (ans *= base) %= MOD;
		if (b >>= 1) (base *= base) %= MOD;
	}
	return ans;
}
#define inv(x) power_pow(x, MOD - 2)

int POOL[20000000], *CUR = POOL;
inline int* newpoly(int d)
{
//	REP(i, 0, d) CUR[i] = 0;
	CUR += d + 1;
	return CUR - (d + 1);
}

namespace Poly
{
	const int maxn = 1 << 20;
	int ibin2[30];
	struct __init__
	{
		__init__()
		{
			ibin2[0] = 1;ibin2[1] = (MOD + 1 >> 1);
			REP(i, 2, 29) ibin2[i] = 1ll * ibin2[i - 1] * ibin2[1] % MOD;
		}
	}__INIT__;
	void NTT(int *f, int n, int flg)
	{
		static int R[maxn];
		static u64 a[maxn];
		REP(i, 0, n - 1) a[i] = f[i];
		if (flg < 0) reverse(a + 1, a + n);
		REP(i, 1, n - 1)
		{
			R[i] = (R[i >> 1] >> 1) | ((i & 1) ? (n >> 1) : 0);
			if (i < R[i]) swap(a[i], a[R[i]]);
		}
		
		static bool vis[30];
		static int pool[maxn << 1 | 10], *cur = pool, *w[30];

		int c = 0;
		for (int i = 1; i < n; i <<= 1, c++)
		{
			if (!vis[c])
			{
				vis[c] = 1;
				w[c] = cur;cur += i;

				i64 wn = power_pow(3, MOD - 1 >> (c + 1));
				w[c][0] = 1;
				REP(l, 1, i - 1) w[c][l] = w[c][l - 1] * wn % MOD;
			}
			for (int k = 0; k < n; k += i + i)
				for (int l = 0; l < i; l++)
				{
					u64 x = a[k + l], y = a[k + l + i] * w[c][l] % MOD;
					a[k + l] = x + y;
					a[k + l + i] = x + MOD - y;
				}
		}
		REP(i, 0, n - 1) f[i] = a[i] % MOD, a[i] = 0;
		if (flg < 0)
		{
			i64 in = ibin2[c];
			REP(i, 0, n - 1) f[i] = f[i] * in % MOD;
		}
	}
}
using Poly :: NTT;

int n, m, q, mv;
int g[10][10][65536];
int f[10][10][65536];

const u64 LIM = 17e18;
inline void reduce(int &x) {x += x >> 31 & MOD;}

int* mem[10][10][20];
bool vis[20];

void init_G(int l, int r)
{
	if (l == r) return;
	int mid = l + r >> 1;

	init_G(l, mid);

	int len = 1, c = 0;
	while (len <= ((r - l) + 0 * (mid - l))) len <<= 1, c++;

	if (!vis[c])
	{
		REP(i, 1, n) REP(j, 1, n)
		{
			mem[i][j][c] = newpoly(len - 1);
			REP(l, 0, r - l + 1) mem[i][j][c][l] = g[i][j][l];
			NTT(mem[i][j][c], len, 1);
		}
		vis[c] = 1;
	}

	init_G(mid + 1, r);
}
void cdq(int l, int r)
{
	if (l == r) return;
	int mid = l + r >> 1;

	cdq(l, mid);

	int len = 1, c = 0;
	while (len <= ((r - l) + 0 * (mid - l))) len <<= 1, c++;

	int *F[10][10], *G[10][10];
	REP(i, 1, n) REP(j, 1, n)
	{
		F[i][j] = newpoly(len - 1);
		REP(k, l, mid) F[i][j][k - l] = f[i][j][k];
		NTT(F[i][j], len, 1);
		G[i][j] = mem[i][j][c];
	}

	static u64 T[10][10][65536];

	REP(i, 1, n) REP(k, 1, n) REP(j, 1, n)
		REP(l, 0, len - 1)
		{
			T[i][j][l] += (u64)F[i][k][l] * G[k][j][l];
			if (T[i][j][l] >= LIM) T[i][j][l] %= MOD;
		}
	REP(i, 1, n) REP(j, 1, n)
	{
		static int t[65536];
		REP(l, 0, len - 1) t[l] = T[i][j][l] % MOD, T[i][j][l] = 0;
		NTT(t, len, -1);
		REP(k, mid + 1, r) reduce(f[i][j][k] += t[k - l] - MOD);
	}
	CUR -= len * n * n;
	memset(CUR, 0, sizeof (int) * (len * n * n));

	cdq(mid + 1, r);
}
int main()
{
#ifdef CraZYali
	file("551");
#endif
	n = read<int>();m = read<int>();q = read<int>();mv = read<int>();
	int l = 1;while (l <= mv) l <<= 1;mv = l - 1;

	REP(i, 1, m)
	{
		int x = read<int>(), y = read<int>(), z = read<int>();
		g[x][y][z]++;
	}
	REP(i, 1, n) f[i][i][0] = 1;
	init_G(0, mv);
	cdq(0, mv);
	while (q--)
	{
		int x = read<int>(), y = read<int>(), d = read<int>();
		printf("%d\n", f[x][y][d]);
	}
	return 0;
}
