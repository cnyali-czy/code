/*
 * File Name:	5277.cpp
 * Author	:	CraZYali
 * Time		:	2020.01.18 23:15
 * Email	:	yms-chenziyang@outlook.com
 */

#define DEP(i, s, e) for (register int i(s), end_##i(e); i >= end_##i; i--)
#define REP(i, s, e) for (register int i(s), end_##i(e); i <= end_##i; i++)
#define DEBUG fprintf(stderr, "Passing [%s] in Line %d\n", __FUNCTION__, __LINE__)

#define chkmax(a, b) (a < (b) ? a = (b) : a) 
#define chkmin(a, b) (a > (b) ? a = (b) : a) 

#include <cstring>
#include <iostream>
#include <cstdio>

using namespace std;
const int maxn = (1 << 21) + 5, MOD = 998244353, Inv2 = MOD + 1 >> 1;

int add() {return 0;}
template <typename ...T>
int add(int x, T... y)
{
	int res = x + add(y...);
	if (res >= MOD) res -= MOD;
	return res;
}

int sub(int x, int y)
{
	int res = x - y;
	if (res < 0) res += MOD;
	return res;
}

int mul() {return 1;}
template <typename ...T>
int mul(int x, T... y)
{
	long long res = (long long)x * mul(y...);
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

namespace poly
{
	int Wn[40], Invwn[40];
	struct __init__
	{
		__init__()
		{
			REP(i, 0, 30)
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
	void getInv(int F[], int B[], int n)
	{
		if (n == 1) return void(B[0] = inv(F[0]));
		getInv(F, B, n >> 1);
		copy(F, F + n, tmp);
		NTT(tmp, n + n, 1);
		NTT(B, n + n, 1);
		REP(i, 0, n + n - 1) B[i] = sub(add(B[i], B[i]), mul(B[i], B[i], tmp[i]));
		NTT(B, n + n, -1);
		REP(i, n, n + n - 1) tmp[i] = B[i] = 0;
	}
	int Inv[maxn];
}

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

int n, F[maxn], ln[maxn], Sqrt[maxn], Inv[maxn];

int main()
{
#ifdef CraZYali
	file("5205-new");
#endif
	cin >> n;n--;
	int l = 1;
	while (l <= n) l <<= 1;
	REP(i, 0, n) F[i] = read<int>();
	/*
	   poly::getLn(F, ln, l);
	   REP(i, 0, l - 1) F[i] = mul(F[i], Inv2);
	   poly::getExp(ln, Sqrt, l);
	   REP(i, 0, n) printf("%d%c", Sqrt[i], i == end_i ? '\n' : ' ');
	   */
	poly::getInv(F, Inv, l);
	REP(i, 0, n) printf("%d%c", Inv[i], i == n ? '\n' : ' ');
	return 0;
}
