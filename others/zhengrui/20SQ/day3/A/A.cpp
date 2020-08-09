/*
	Problem:	A.cpp
	Time:		2020-08-05 19:39
	Author:		CraZYali
	E-Mail:		yms-chenziyang@outlook.com 
*/
#pragma GCC optimize(3)
#define REP(i, s, e) for (register int i(s), end_##i(e); i <= end_##i; i++)
#define DEP(i, s, e) for (register int i(s), end_##i(e); i >= end_##i; i--)
#define DEBUG fprintf(stderr, "Passing [%s] in Line %d\n", __FUNCTION__, __LINE__)

#include <ctime>
#include <iostream>
#include <cstdio>
#include <random>
#define i64 long long
using namespace std;
const int maxn = 2e5 + 10;

inline i64 mul(i64 a, i64 b, const i64 p)
{
	i64 res = (a * b - (i64)((long double)a / p * b) * p) % p;
	if (res < 0) res += p;
	return res;
}
i64 MOD;
const int w = 32000;
i64 pre1[w + 5], pre2[w + 5];
inline i64 pow2(int b)
{
	return mul(pre1[b % w], pre2[b / w], MOD);
}
#ifndef CraZYali
#define getchar getchar_unlocked
#endif
	template <typename T>
inline T read()
{
	T ans = 0;
	char c = getchar();
	while (!isdigit(c)) c = getchar();
	while (isdigit(c))
	{
		ans = ans * 10 + c - 48;
		c = getchar();
	}
	return ans;
}

#define file(FILE_NAME) freopen(FILE_NAME".in", "r", stdin), freopen(FILE_NAME".out", "w", stdout)

int n, a[maxn];
i64 s[maxn], pa[maxn];
i64 ans;

//__gnu_pbds :: tree <int, int> cnt;

inline void chkmax(int &x, int y) {if (x < y) x = y;}
inline void chkmin(int &x, int y) {if (x > y) x = y;}

int lg[maxn];

//void cdq(int l, int r)

mt19937 hh;
inline i64 randint(i64 l, i64 r)
{
	auto res = hh();
	if (res < 0) res = -res;
	return res % (r - l + 1) + l;
}

namespace miller
{
	i64 power_pow(i64 base, i64 b, const i64 p)
	{
		i64 ans = 1;
		while (b)
		{
			if (b & 1) ans = mul(ans, base, p);
			base = mul(base, base, p);
			b >>= 1;
		}
		return ans;
	}
	int totst[] = {2, 3, 13, 17, 19, 23};
	bool miller_rabin(i64 n)
	{
		if (n < 3) return n == 2;
		if (!(n & 1)) return 0;
		i64 a = n - 1, b = 0;
		while (!(a & 1)) a >>= 1, b++;
		for (int x : totst)
		{
			if (n == x) return 1;
			i64 v = power_pow(x, a, n);
			if (v == 1 || v == n - 1) continue;
			REP(i, 0, b)
			{
				if (v == n - 1) break;
				if (i == b) return 0;
				v = mul(v, v, n);
			}
		}
		return 1;
	}
}

void init(i64 l, i64 r)
{
	while (!miller :: miller_rabin(MOD)) MOD = randint(l, r);
	const i64 mod = MOD;
	pre1[0] = 1;
	REP(i, 1, w) pre1[i] = 2 * pre1[i - 1] % mod;
	pre2[0] = 1;
	REP(i, 1, w) pre2[i] = mul(pre1[w], pre2[i - 1], mod);
	REP(i, 1, n) s[i] = (s[i - 1] + (pa[i] = pow2(a[i]))) % mod;
}
namespace hash_table
{
	const int mod = 400009;//2333323;//11100013;//2e7 + 3;
	int bg[mod], e;
	struct Edge
	{
		int ne, w;
		i64 to;
	}E[mod];
	inline int &add(int x, i64 y)
	{
		e++;
		E[e].to = y;
		E[e].ne = bg[x];
		bg[x] = e;
		E[e].w = 0;
		return E[e].w;
	}
	bool vis[mod];
	int stk[mod], top;
	int &get(i64 x)
	{
		int h = x % mod;
		if (!vis[h]) vis[stk[top++] = h] = 1;
		for (int i = bg[h]; i; i = E[i].ne) if (E[i].to == x) return E[i].w;
		return add(h, x);
	}
	int qry(i64 x)
	{
		int h = x % mod;
		if (!vis[h]) return 0;
		for (int i = bg[h]; i; i = E[i].ne) if (E[i].to == x) return E[i].w;
		return 0;
	}
	void clear()
	{
		REP(i, 0, top - 1)
		{
			vis[stk[i]] = 0;
			bg[stk[i]] = 0;
		}
		e = 0;
		top = 0;
	}
}
const int B = 20;
void cdq(int l, int r)
{
	const i64 MOD = ::MOD;
	if (l == r) {ans++;return;}
	int mid = l + r >> 1;
	cdq(l, mid);
	register int i, j, Max, Min;

	hash_table :: clear();
	//cnt.clear();
	Max = 0;Min = 1e9;
	for (i = mid + 1, j = mid + 1; j <= r; j++)
	{
		chkmax(Max, a[j]);
		chkmin(Min, a[j]);
		while (l < i && a[i - 1] <= Max)
		{
			i--;
			hash_table :: get(s[i - 1])++;
		}
		if (Max - Min > j - i - 1) continue;
		if (i <= mid)
		{
			i64 t = pow2(Max + 1);
			REP(x, Max + 1, Max + lg[j - i + 1])
			{
				ans += hash_table :: qry((s[j] + MOD - t) % MOD);
				t = 2 * t % MOD;
			}
		}
	}

	hash_table :: clear();
	//cnt.clear();
	Max = 0;Min = 1e9;
	for (i = mid, j = mid; l <= i; i--)
	{
		chkmax(Max, a[i]);
		chkmin(Min, a[i]);
		while (j < r && a[j + 1] < Max)
		{
			j++;
			hash_table :: get(s[j])++;
		}
		if (Max - Min > j - i - 1) continue;
		i64 tmp = 0;
		if (j > mid)
		{
			i64 t = pow2(Max + 1);
			REP(k, Max + 1, Max + lg[j - i + 1])
			{
				ans += hash_table :: qry((s[i - 1] + t) % MOD);
				t = 2 * t % MOD;
			}
		}
	}
	cdq(mid + 1, r);
}
signed main()
{
#ifdef CraZYali
	file("A");
#endif
	n = read<int>();
	REP(i, 1, n) a[i] = read<int>();
	REP(i, 2, n) lg[i] = lg[i >> 1] + 1;
	hh = mt19937(time(0));

	init(5e17, 1e18);
	cerr << clock() * 1. / CLOCKS_PER_SEC << endl;

	cdq(1, n);
	cout << (long long)ans << endl;
	cerr << clock() * 1. / CLOCKS_PER_SEC << endl;
	return 0;
}
