/*
 * File Name:	4512-new.cpp
 * Author	:	CraZYali
 * Time		:	2020.01.11 11:06
 * Email	:	yms-chenziyang@outlook.com
 */

#define DEP(i, s, e) for (register int i(s), end_##i(e); i >= end_##i; i--)
#define REP(i, s, e) for (register int i(s), end_##i(e); i <= end_##i; i++)
#define DEBUG fprintf(stderr, "Passing [%s] in Line %d\n", __FUNCTION__, __LINE__)

#define chkmax(a, b) (a < (b) ? a = (b) : a) 
#define chkmin(a, b) (a > (b) ? a = (b) : a) 

#include <algorithm>
#include <iostream>
#include <cstdio>

using namespace std;
const int maxn = 1 << 22, MOD = 998244353;

inline int add() {return 0;}
	template <typename ...T>
inline int add(int arg, T... args)
{
	int res = arg + add(args...);
	if (res >= MOD) res -= MOD;
	return res;
}

inline int sub(int x, int y)
{
	int res = x - y;
	if (res < 0) res += MOD;
	return res;
}

inline int mul() {return 1;}
	template <typename ...T>
inline int mul(int arg, T... args)
{
	long long res = 1ll * arg * mul(args...);
	if (res >= MOD) res %= MOD;
	return res;
}

int power_pow(int base, int b)
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
#define inv(x) power_pow(x, MOD - 2)

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

namespace poly
{
	int Wn[30], Invwn[30];
	struct __init__
	{
		__init__()
		{
			REP(i, 0, 29)
			{
				Wn[i] = power_pow(3, (MOD - 1) / (1 << i + 1));
				Invwn[i] = inv(Wn[i]);
			}
		}
	}__INIT__;

	int R[maxn];
	void NTT(int a[], int n, int flag)
	{
		REP(i, 1, n - 1)
		{
			R[i] = (R[i >> 1] >> 1) | (i & 1 ? (n >> 1) : 0);
			if (i < R[i]) swap(a[i], a[R[i]]);
		}
		for (int i = 1, ccc = 0; i < n; ccc++, i <<= 1)
		{
			int wn = (flag > 0 ? Wn[ccc] : Invwn[ccc]);
			for (int k = 0; k < n; k += i << 1)
				for (int l = 0, w = 1; l < i; l++, w = mul(w, wn))
				{
					int x(a[k + l]), y(mul(a[k + l + i], w));
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
	void getInv(const int F[], int Inv[], int n)
	{
		if (!n) return void(Inv[0] = inv(F[0]));
		getInv(F, Inv, n >> 1);
		copy(F, F + n, tmp);
		NTT(tmp, n + n, 1);
		NTT(Inv, n + n, 1);
		REP(i, 0, n + n - 1) Inv[i] = sub(add(Inv[i], Inv[i]), mul(Inv[i], Inv[i], tmp[i]));
		NTT(Inv, n + n, -1);
		REP(i, n, n + n - 1) tmp[i] = Inv[i] = 0;
	}

	int A[maxn], B[maxn], C[maxn];
	void div(int a[], int b[], int n, int m, int D[], int R[])
	{
		copy(a, a + n + 1, A);
		copy(b, b + m + 1, B);
		reverse(A, A + n + 1);
		reverse(B, B + m + 1);
		REP(i, n - m + 1, max(n, m)) A[i] = B[i] = 0;
		int l(1);
		while (l <= n - m) l <<= 1;
		REP(i, m + 1, l - 1) B[i] = 0;
		getInv(B, C, l);
		NTT(C, l + l, 1);
		NTT(A, l + l, 1);
		REP(i, 0, l + l - 1) D[i] = mul(A[i], C[i]);
		NTT(D, l + l, -1);
		reverse(D, D + n - m + 1);
		REP(i, n - m + 1, l + l - 1) D[i] = 0;
		copy(b, b + m + 1, B);
		l = 1;
		while (l <= n) l <<= 1;
		NTT(B, l, 1);
		NTT(D, l, 1);
		REP(i, 0, l - 1) R[i] = mul(B[i], D[i]);
		NTT(R, l, -1);
		NTT(D, l, -1);
		REP(i, 0, n - 1) R[i] = sub(a[i], R[i]);
	}
}
int n, m, A[maxn], B[maxn], D[maxn], R[maxn];

int main()
{
#ifdef CraZYali
	file("4512-new");
#endif
	cin >> n >> m;
	REP(i, 0, n) A[i] = read<int>();
	REP(i, 0, m) B[i] = read<int>();
	poly::div(A, B, n, m, D, R);
	REP(i, 0, n - m) printf("%d%c", D[i], i == end_i ? '\n' : ' ');
	REP(i, 0, m - 1) printf("%d%c", R[i], i == end_i ? '\n' : ' ');
	return 0;
}
