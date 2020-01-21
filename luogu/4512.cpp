/*
 * File Name:	4512.cpp
 * Author	:	CraZYali
 * Time		:	2020.01.10 21:57
 * Email	:	yms-chenziyang@outlook.com
 */

#define DEP(i, s, e) for (register int i(s), end_##i(e); i >= end_##i; i--)
#define REP(i, s, e) for (register int i(s), end_##i(e); i <= end_##i; i++)
#define DEBUG fprintf(stderr, "Passing [%s] in Line %d\n", __FUNCTION__, __LINE__)

#define chkmax(a, b) (a < (b) ? a = (b) : a) 
#define chkmin(a, b) (a > (b) ? a = (b) : a) 

#include <cmath>
#include <algorithm>
#include <iostream>
#include <cstdio>
#include <vector>

using namespace std;
const int MOD = 998244353, g = 3;

inline int add() {return 0;}
template <typename... T>
inline int add(const int& arg, const T&... args)
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
template <typename... T>
inline int mul(const int& arg, const T&... args)
{
	long long res = 1ll * arg * mul(args...);
	if (res >= MOD) res %= MOD;
	return res;
}

int power_pow(int base, int b)
{
	int ans = 1;
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

#define Poly vector <int>

void output(const Poly &A)
{
	REP(i, 0, A.size() - 1) printf("%d%c", A[i], i == end_i ? '\n' : ' ');
}
int _R[1 << 20];

int WN[30], INVWN[30];

struct __init__
{
	__init__()
	{
		for (int i = 0; i <= 20; i++)
		{
			WN[i] = power_pow(g, (MOD - 1) / (1 << i + 1));
			INVWN[i] = inv(WN[i]);
		}
	}
}__INIT__;

void NTT(Poly &a, int n, int flag)
{
	a.resize(n);
	REP(i, 1, n - 1)
	{
		_R[i] = (_R[i >> 1] >> 1) | ((i & 1) ? (n >> 1) : 0);
		if (i < _R[i]) swap(a[i], a[_R[i]]);
	}
	for (int ccc = 0, i = 1; i < n; ccc++, i <<= 1)
	{
		int wn = (flag > 0 ? WN[ccc] : INVWN[ccc]);
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

Poly Inv(Poly F, int n)
{
	if (n == 1) return Poly(1, inv(F[0]));
	F.resize(n);
	Poly A = Inv(F, n >> 1), B(n + n);
	NTT(A, n + n, 1);
	NTT(F, n + n, 1);
	REP(i, 0, n + n - 1) B[i] = sub(add(A[i], A[i]), mul(A[i], A[i], F[i]));
	NTT(B, n + n, -1);
	B.resize(n);
	return B;
}

Poly div(Poly A, Poly B)
{
	int n(A.size()), m(B.size());
	reverse(A.begin(), A.end());
	reverse(B.begin(), B.end());
	A.resize(n - m + 1);
	B.resize(n - m + 1);
	int l(1);
	while (l < n - m + 1) l <<= 1;
	B = Inv(B, l);
	NTT(A, l + l, 1);
	NTT(B, l + l, 1);
	REP(i, 0, l + l - 1) A[i] = mul(A[i], B[i]);
	NTT(A, l + l, -1);
	A.resize(n - m + 1);
	reverse(A.begin(), A.end());
	return A;
}

int n, m;
Poly A, B, D, R;

int main()
{
#ifdef CraZYali
	file("4512");
#endif
	cin >> n >> m;
	A.resize(n + 1);B.resize(m + 1);
	REP(i, 0, n) A[i] = read<int>();
	REP(i, 0, m) B[i] = read<int>();
	output(D = div(A, B));
	int N = 1;
	while (N <= (n + m) + m) N <<= 1;
	NTT(B, N, 1);
	NTT(D, N, 1);
	R.resize(N, 0);
	REP(i, 0, N - 1) R[i] = mul(D[i], B[i]);
	NTT(R, N, -1);
	R.resize(m);
	REP(i, 0, m - 1) R[i] = sub(A[i], R[i]);
	output(R);
	
	return 0;
}
