/*
	Problem:	E.cpp
	Time:		2020-03-07 15:34
	Author:		CraZYali
	E-Mail:		yms-chenziyang@outlook.com 
*/

#define REP(i, s, e) for (register int i(s), end_##i(e); i <= end_##i; i++)
#define DEP(i, s, e) for (register int i(s), end_##i(e); i >= end_##i; i--)
#define DEBUG fprintf(stderr, "Passing [%s] in Line %d\n", __FUNCTION__, __LINE__)

#define chkmax(a, b) (a < (b) ? a = (b) : a)
#define chkmin(a, b) (a > (b) ? a = (b) : a)

#include <algorithm>
#include <cstring>
#include <iostream>
#include <cstdio>
#define i64 long long
using namespace std;
const int maxn = 1 << 20;//, MOD = 998244353;
#define MOD 998244353
inline int add(int x, int y) {x += y;return x >= MOD ? x - MOD : x;}
inline int sub(int x, int y) {x -= y;return x <    0 ? x + MOD : x;}
inline i64 mul(i64 x, int y) {x *= y;return x >= MOD ? x % MOD : x;}
inline void inc(int &x, int y) {x += y;if (x >= MOD) x -= MOD;}

inline int power_pow(int base, int b)
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

int n, a[maxn], b[maxn], cnt[maxn];
char s[maxn];
bool flag[maxn];

int Wn[40], InvWn[40];
struct __init__
{
	__init__()
	{
		REP(i, 0, 25)
		{
			Wn[i] = power_pow(3, (MOD - 1) / (1 << i + 1));
			InvWn[i] = inv(Wn[i]);
		}
	}
}__INIT__;

int R[maxn];
void NTT(int a[], int n, int flag)
{
	REP(i, 1, n - 1)
		if (i < R[i]) swap(a[i], a[R[i]]);
	for (int i = 1, ccc = 0; i < n; i <<= 1, ccc++)
	{
		int wn = flag > 0 ? Wn[ccc] : InvWn[ccc];
		for (int k = 0; k < n; k += i << 1)
			for (int l = 0, w = 1; l < i; l++, w = mul(w, wn))
			{
				int x(a[k + l]), y(mul(w, a[k + l + i]));
				a[k + l] = add(x, y);
				a[k + l + i] = sub(x, y);
			}
	}
	/*
	 * useless
	if (flag < 0)
	{
		const int invn = inv(n);
		REP(i, 0, n - 1) a[i] = mul(a[i], invn);
	}
	*/
}

int main()
{
#ifdef CraZYali
	file("E");
#endif
	register int T = read<int>();
	while (T--)
	{
		n = read<int>();
		scanf("%s", s + 1);
		int l = 1;
		while (l <= n + n) l <<= 1;
		REP(i, 1, l - 1) R[i] = (R[i >> 1] >> 1) | (i & 1 ? l >> 1 : 0);
		REP(i, 0, l - 1) a[i] = b[i] = 0;
		REP(i, 1, n)
		{
			a[n - i] = (s[i] == 'V');
			b[i] = (s[i] == 'K');
		}
		NTT(a, l, 1);NTT(b, l, 1);
		REP(i, 0, l - 1) a[i] = mul(a[i], b[i]);
		NTT(a, l, -1);
		REP(i, 1, n) cnt[i] = a[i + n];
		REP(i, 0, l - 1) a[i] = b[i] = 0;
		REP(i, 1, n)
		{
			a[n - i] = (s[i] == 'K');
			b[i] = (s[i] == 'V');
		}
		NTT(a, l, 1);NTT(b, l, 1);
		REP(i, 0, l - 1) a[i] = mul(a[i], b[i]);
		NTT(a, l, -1);
		REP(i, 1, n) cnt[i] += a[i + n];
		int ans = 0;
		REP(i, 1, n)
		{
			flag[i] = 1;
			for (register int j = i; j <= n; j += i) if (cnt[j])
			{
				flag[i] = 0;
				break;
			}
			ans += flag[i];
		}
		cout << ans << '\n';
		REP(i, 1, n) if (flag[i]) cout << i << ' ';
		cout << endl;
	}
	return 0;
}
