/*
 * File Name:	E.cpp
 * Author	:	CraZYali
 * Time		:	2020.01.12 13:47
 * Email	:	yms-chenziyang@outlook.com
 */

#define DEP(i, s, e) for (register int i(s), end_##i(e); i >= end_##i; i--)
#define REP(i, s, e) for (register int i(s), end_##i(e); i <= end_##i; i++)
#define DEBUG fprintf(stderr, "Passing [%s] in Line %d\n", __FUNCTION__, __LINE__)

#define chkmax(a, b) (a < (b) ? a = (b) : a) 
#define chkmin(a, b) (a > (b) ? a = (b) : a) 

#include <cassert>
#include <cstring>
#include <iostream>
#include <cstdio>

using namespace std;
const int maxn = 1 << 20, MOD = 998244353, Inv2 = MOD + 1 >> 1;

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

	int tmp2[maxn], tmp3[maxn];
	void getexp(int F[], int B[], int n, bool first = 0)
	{
		if (first)
		{
			int l(1);
			while (l <= n + n) l <<= 1;
			REP(i, n + 1, l - 1) F[i] = 0;
			getexp(F, B, l);
			return;
		}
		if (n == 1)
		{
			B[0] = 1;
			return;
		}
		getexp(F, B, n >> 1);
		REP(i, 0, n + n - 1) tmp2[i] = tmp3[i] = 0;
		copy(F, F + n, tmp2);
		//		puts("==============");
		//		REP(i, 0, n - 1) printf("%d%c", B[i], i == n - 1 ? '\n': ' ');
		getln(B, tmp3, 1 + (n >> 1));
		//		REP(i, 0, n - 1) printf("%d%c", tmp3[i], i == n - 1 ? '\n': ' ');
		//		puts("==============\n");
		NTT(tmp3, n + n, 1);
		NTT(tmp2, n + n, 1);
		NTT(B, n + n, 1);
		REP(i, 0, n + n - 1) B[i] = sub(B[i], mul(B[i], sub(tmp3[i], tmp2[i])));
		NTT(B, n + n, -1);
		//		cerr<<"B[0] = "<<B[0]<<endl;
		//		assert(B[0] == 1);
		REP(i, n, n + n - 1) B[i] = tmp2[i] = tmp3[i] = 0;
	}
}
using poly::NTT;
using poly::getln;
using poly::getexp;
using poly::getInv;

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

int n, m, F[maxn], ln[maxn], exp[maxn];

int main()
{
#ifdef CraZYali
	file("E");
#endif
	cin >> n >> m;
	const int qaq = MOD - 4;
	const int l = 1 << 17;
	F[0] = 1;
	REP(i, 1, n) F[read<int>()] = qaq;
	getln(F, ln, l);
	REP(i, 0, l) ln[i] = mul(ln[i], Inv2);
	getexp(ln, exp, l, 1);
	exp[0] = add(exp[0], 1);
	memset(F, 0, sizeof F);
	getInv(exp, F, l);
	REP(i, 1, m) printf("%d\n", mul(F[i], 2));

	return 0;
}
