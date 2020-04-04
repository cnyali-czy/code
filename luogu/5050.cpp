/*
 * File Name:	5050.cpp
 * Author	:	CraZYali
 * Time		:	2020.01.11 08:56
 * Email	:	yms-chenziyang@outlook.com
 */

#define DEP(i, s, e) for (register int i(s), end_##i(e); i >= end_##i; i--)
#define REP(i, s, e) for (register int i(s), end_##i(e); i <= end_##i; i++)
#define DEBUG fprintf(stderr, "Passing [%s] in Line %d\n", __FUNCTION__, __LINE__)

#define chkmax(a, b) (a < (b) ? a = (b) : a) 
#define chkmin(a, b) (a > (b) ? a = (b) : a) 

#include <cassert>
#include <cmath>
#include <algorithm>
#include <iostream>
#include <cstdio>
#include <vector>
#define i64 long long
using namespace std;
const int MOD = 998244353, g = 3, maxm = 64005;

inline int add(int x, int y) {return (x += y) >= MOD ? x - MOD : x;}
inline int sub(int x, int y) {return (x -= y) <    0 ? x + MOD : x;}
inline i64 mul(i64 x, int y) {return (x *= y) >= MOD ? x % MOD : x;}
inline void inc(int &x, int y) {x += y;if (x >= MOD) x -= MOD;}
inline void dec(int &x, int y) {x -= y;if (x <    0) x += MOD;}
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
int _R[1 << 25];

int WN[30], INVWN[30];

struct __init__
{
	__init__()
	{
		for (int i = 0; i < 30; i++)
		{
			WN[i] = power_pow(g, (MOD - 1) / (1 << i + 1));
			INVWN[i] = inv(WN[i]);
		}
	}
}__INIT__;

unsigned long long NTTtmp[1 << 20];
void NTT(Poly &a, int n, int flag)
{
	if (a.size() ^ n) a.resize(n);
	REP(i, 1, n - 1)
	{
		_R[i] = (_R[i >> 1] >> 1) | ((i & 1) ? (n >> 1) : 0);
		if (i < _R[i]) swap(a[i], a[_R[i]]);
	}
	REP(i, 0, n - 1) NTTtmp[i] = a[i];
	for (int ccc = 0, i = 1; i < n; ccc++, i <<= 1)
	{
		int wn = (flag > 0 ? WN[ccc] : INVWN[ccc]);
		for (int k = 0; k < n; k += i << 1)
			for (int l = 0, w = 1; l < i; l++, w = 1ll * w * wn % MOD)
			{
				unsigned long long x(NTTtmp[k + l]), y(w * NTTtmp[k + l + i] % MOD);
				NTTtmp[k + l] = x + y;
				NTTtmp[k + l + i] = MOD + x - y;
			}
	}
	REP(i, 0, n - 1) a[i] = NTTtmp[i] % MOD;
	if (flag < 0)
	{
		const i64 Invn = inv(n);
		REP(i, 0, n - 1) a[i] = a[i] * Invn % MOD;
	}
}

Poly Inv(const Poly &FF, int N)
{
	Poly A(1, inv(FF[0]));
	Poly F;
	for (int n = 2; n <= N; n <<= 1)
	{
		F.resize(n);
		REP(i, 0, n - 1) F[i] = FF[i];
		NTT(A, n + n, 1);
		NTT(F, n + n, 1);
		REP(i, 0, n + n - 1) A[i] = A[i] * (2ll + MOD - 1ll * A[i] * F[i] % MOD) % MOD;
		NTT(A, n + n, -1);
		A.resize(n);
	}
	return A;
}
Poly operator / (Poly A, Poly B)
{
	int n(A.size()), m(B.size());
	reverse(A.begin(), A.end());
	reverse(B.begin(), B.end());
	A.resize(n - m + 1);
	B.resize(n - m + 1);
	int l(1);
	while (l <= n - m + 1) l <<= 1;
	B.resize(l);
	B = Inv(B, l);
	NTT(A, l + l, 1);
	NTT(B, l + l, 1);
	REP(i, 0, l + l - 1) A[i] = 1ll * A[i] * B[i] % MOD;
	NTT(A, l + l, -1);
	A.resize(n - m + 1);
	reverse(A.begin(), A.end());
	return A;
}

Poly operator % (Poly A, Poly B)
{
	int n(A.size() - 1), m(B.size() - 1);
	Poly D = A / B;
	int l(1);
	while (l <= n + (n + m)) l <<= 1;
	NTT(A, l, 1);
	NTT(B, l, 1);
	NTT(D, l, 1);
	REP(i, 0, l - 1) dec(A[i], 1ll * B[i] * D[i] % MOD);
	NTT(A, l, -1);
	A.resize(m);
	return A;
}

Poly operator * (Poly A, Poly B)
{
	int l(1), n(A.size() - 1), m(B.size() - 1);
	while (l <= n + m) l <<= 1;
	NTT(A, l, 1);
	NTT(B, l, 1);
	REP(i, 0, l - 1) A[i] = 1ll * A[i] * B[i] % MOD;
	NTT(A, l, -1);
	A.resize(n + m + 1);
	return A;
}

int n, m;
Poly F, G;
int a[maxm];

int get(Poly f, int x)
{
	int res = 0;
	DEP(i, f.size() - 1, 0) res = add(f[i], mul(res, x));
	return res;
}

Poly Mul(int l, int r)
{
	if (l == r)
	{
		Poly res(2);
		res[0] = sub(0, a[l]);
		res[1] = 1;
		return res;
	}
	int mid = l + r >> 1;
	return Mul(l, mid) * Mul(mid + 1, r);
}

Poly QAQ[maxm * 2];

int rt, ls[maxm * 2], rs[maxm * 2], cur;
#define mid (l + r >> 1)
#define lson l, mid, ls[p]
#define rson mid + 1, r, rs[p]
void Init(int l, int r, int &p = rt)
{
	p = ++cur;
	if (l == r)
	{
		QAQ[p].resize(2);
		QAQ[p][0] = sub(0, a[l]);
		QAQ[p][1] = 1;
		return;
	}
	Init(lson);Init(rson);
	QAQ[p] = QAQ[ls[p]] * QAQ[rs[p]];
}
#undef mid
const int End = 250;
void work(const Poly &F, int l, int r, int p = rt)
{
	if (F.size() <= End)
	{
		REP(i, l, r) printf("%d\n", get(F, a[i]));
		return;
	}
	int mid = l + r >> 1;
	work(F % QAQ[ls[p]], l, mid, ls[p]);
	work(F % QAQ[rs[p]], mid + 1, r, rs[p]);
}

int main()
{
#ifdef CraZYali
	file("5050");
#endif
	cin >> n >> m;
	F.resize(n + 1);
	REP(i, 0, n) F[i] = read<int>();
	REP(i, 1, m) a[i] = read<int>();
	Init(1, m);
	work(F, 1, m);
	return 0;
}
