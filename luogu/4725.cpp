/*
 * File Name:	4725.cpp
 * Author	:	CraZYali
 * Time		:	2020.01.11 22:10
 * Email	:	yms-chenziyang@outlook.com
 */

#define DEP(i, s, e) for (register int i(s), end_##i(e); i >= end_##i; i--)
#define REP(i, s, e) for (register int i(s), end_##i(e); i <= end_##i; i++)
#define DEBUG fprintf(stderr, "Passing [%s] in Line %d\n", __FUNCTION__, __LINE__)

#define chkmax(a, b) (a < (b) ? a = (b) : a) 
#define chkmin(a, b) (a > (b) ? a = (b) : a) 

#include <iostream>
#include <cstdio>

using namespace std;
const int maxn = 1 << 20, MOD = 998244353;

inline int add() {return 0;}
	template <typename ...T>
int add(int arg, T... args)
{
	int res = arg + add(args...);
	if (res >= MOD) res -= MOD;
	return res;
}

inline int mul() {return 1;}
	template <typename ...T>
int mul(int arg, T... args)
{
	long long res = 1ll * arg * mul(args...);
	if (res >= MOD) res %= MOD;
	return res;
}

inline int sub(int x, int y)
{
	int res = x - y;
	if (res < 0) res += MOD;
	return res;
}

int qpow(int base, int b)
{
	int ans(1);
	while (b)
	{
		if (b & 1) ans = mul(ans, base);
		base = mul(base, base);
		b >>= 1;
	}
	return ans;
}
#define inv(x) qpow(x, MOD - 2)
int Wn[30][2];
struct _init_
{
	_init_()
	{
		REP(i, 0, 29)
		{
			Wn[i][0] = qpow(3, (MOD - 1) / (1 << i + 1));
			Wn[i][1] = inv(Wn[i][0]);
		}
	}
}_INIT_;

namespace poly
{
	int R[maxn];
	void NTT(int a[], int n, int flag)
	{
		REP(i, 1, n - 1)
		{
			R[i] = (R[i >> 1] >> 1) | (i & 1 ? (n >> 1) : 0);
			if (i < R[i]) swap(a[i], a[R[i]]);
		}
		for (int i = 1, ccc = 0; i < n; i <<= 1, ccc++)
		{
			int wn = Wn[ccc][flag < 0];
			for (int k = 0; k < n; k += i << 1)
				for (int l = 0, w = 1; l < i; l++, w = mul(w, wn))
				{
					int x(a[k + l]), y(mul(w, a[k + l + i]));
					a[k + l] = add(x, y);
					a[k + l + i] = sub(x, y);
				}
		}
		if (flag < 0)
		{
			const int Invn = inv(n);
			REP(i, 0, n - 1) a[i] = mul(a[i], Invn);
		}
	}

	int tmp[maxn];
	void getInv(int F[], int Inv[], int l)
	{
		if (l == 1) return void(Inv[0] = inv(F[0]));
		getInv(F, Inv, l >> 1);
		copy(F, F + l, tmp);
		REP(i, l, l + l - 1) tmp[i] = 0;
		NTT(tmp, l + l, 1);
		NTT(Inv, l + l, 1);
		REP(i, 0, l + l - 1) Inv[i] = sub(add(Inv[i], Inv[i]), mul(Inv[i], Inv[i], tmp[i]));
		NTT(Inv, l + l, -1);
		REP(i, l, l + l - 1) Inv[i] = tmp[i] = 0;
	}

	int f[maxn], Inv[maxn];
	void getln(int F[], int ln[], int n)
	{
		int l(1);
		while (l <= n + n) l <<= 1;
		REP(i, 0, l - 1) Inv[i] = 0;
		REP(i, 0, n - 1) f[i] = mul(i + 1, F[i + 1]);
		REP(i, n, l - 1) f[i] = 0;
		getInv(F, Inv, l >> 1);
		NTT(f, l, 1);
		NTT(Inv, l, 1);
		REP(i, 0, l - 1) ln[i] = mul(f[i], Inv[i]);
		NTT(ln, l, -1);
		DEP(i, n, 1) ln[i] = mul(ln[i-1], inv(i));
		ln[0] = 0;
	}
}
using poly::NTT;
using poly::getln;

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

int n, F[maxn], ln[maxn];

int main()
{
#ifdef CraZYali
	file("4725");
#endif
	n = read<int>() - 1;
	REP(i, 0, n) F[i] = read<int>();
	getln(F, ln, n);
	REP(i, 0, n) printf("%d%c", ln[i], i == n ? '\n' : ' ');
	return 0;
}
