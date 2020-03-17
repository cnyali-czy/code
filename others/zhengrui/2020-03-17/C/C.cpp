/*
	Problem:	C.cpp
	Time:		2020-03-17 10:15
	Author:		CraZYali
	E-Mail:		yms-chenziyang@outlook.com 
*/

#define REP(i, s, e) for (register int i(s), end_##i(e); i <= end_##i; i++)
#define DEP(i, s, e) for (register int i(s), end_##i(e); i >= end_##i; i--)
#define DEBUG fprintf(stderr, "Passing [%s] in Line %d\n", __FUNCTION__, __LINE__)

#define chkmax(a, b) (a < (b) ? a = (b) : a)
#define chkmin(a, b) (a > (b) ? a = (b) : a)

#include <vector>
#include <iostream>
#include <cstdio>
#define i64 long long
#define MOD 998244353
#define inv3 332748118
using namespace std;
const int maxn = 1e6 + 10;

int bg[maxn], ne[maxn], to[maxn], e;
inline void Add(int x, int y)
{
	e++;
	to[e] = y;
	ne[e] = bg[x];
	bg[x] = e;
}

inline int add(int x, int y) {x += y;return x >= MOD ? x - MOD : x;}
inline int sub(int x, int y) {x -= y;return x <    0 ? x + MOD : x;}
inline i64 mul(i64 x, int y) {x *= y;return x >= MOD ? x % MOD : x;}
inline void inc(int &x, int y) {x += y;if (x >= MOD) x -= MOD;}

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
		ans = ans * 10 + c - 48;
		c = getchar();
	}
	return ans * flag;
}

#define file(FILE_NAME) freopen(FILE_NAME".in", "r", stdin), freopen(FILE_NAME".out", "w", stdout)

int n, k, s;
bool w[maxn];
#define poly vector <int>
poly v[maxn], basic;

int R[1 << 21];
void NTT(poly &a, int n, int flag)
{
	if (a.size() < n) a.resize(n);
	REP(i, 1, n - 1)
	{
		R[i] = (R[i >> 1] >> 1) | (i & 1 ? n >> 1 : 0);
		if (i < R[i]) swap(a[i], a[R[i]]);
	}
	for (int i = 1; i < n; i <<= 1)
	{
		int wn = power_pow(flag > 0 ? 3 : inv3, (MOD - 1) / (i << 1));
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
		const int invn = inv(n);
		REP(i, 0, n - 1) a[i] = mul(a[i], invn);
	}
}

poly operator * (poly A, poly B)
{
	if (!A.size() || !B.size()) return poly(1, 0);
	int l = 1, n = A.size() - 1, m = B.size() - 1;
	while (l <= n + m) l <<= 1;
	poly res(l);
	NTT(A, l, 1);NTT(B, l, 1);
	REP(i, 0, l - 1) res[i] = mul(A[i], B[i]);
	NTT(res, l, -1);
	res.resize(min(s + 1, n + m + 1));
	return res;
/*	
	REP(i, 0, A.size() - 1) if (A[i])
		REP(j, 0, B.size() - 1)
		if (i + j <= s) inc(res[i + j], mul(A[i], B[j]));
		else break;
	for (auto i : A) printf("%d ", i);puts("");
	for (auto i : B) printf("%d ", i);puts("");
	for (auto i : res) printf("%d ", i);puts("\n----------");
	return res;
*/
}
poly operator *=(poly &A, poly B)
{
	if (!A.size() || !B.size()) return poly(1, 0);
	int l = 1, n = A.size() - 1, m = B.size() - 1;
	while (l <= n + m) l <<= 1;
	NTT(A, l, 1);NTT(B, l, 1);
	REP(i, 0, l - 1) A[i] = mul(A[i], B[i]);
	NTT(A, l, -1);
	A.resize(min(s + 1, n + m + 1));
	return A;
}

void dfs(int x)
{
	poly Sum;
	Sum.emplace_back(1);
	for (int i = bg[x]; i; i = ne[i])
	{
		dfs(to[i]);
		Sum *= v[to[i]];
	}
	if (w[x])
	{
		v[x].resize((Sum.size() - 1) * 2 + 1);
		REP(i, 0, Sum.size() - 1) v[x][i * 2] = Sum[i];
		if (v[x].size() > s + 1) v[x].resize(s + 1);
	}
	else v[x] = Sum * basic;
//	printf("node %d\n", x);
//	for (auto i : Sum) printf("%d ", i);puts("");
//	for (auto i : v[x]) printf("%d ", i);puts("\n----------");
}

int main()
{
#ifdef CraZYali
	file("C");
#endif
	n = read<int>();k = read<int>();s = read<int>();
	REP(i, 0, min(s, k)) basic.emplace_back(1);
	REP(i, 2, n) Add(read<int>(), i);
	REP(i, 1, n) w[i] = read<int>();
	dfs(1);
	int ans = 0;
	v[1].resize(s + 1);
	REP(i, 0, s) ans ^= v[1][i];
	cout << ans << '\n';
	return 0;
}
