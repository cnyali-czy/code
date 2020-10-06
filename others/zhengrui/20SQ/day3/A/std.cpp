/*
	Problem:	A.cpp
	Time:		2020-08-05 19:39
	Author:		CraZYali
	E-Mail:		yms-chenziyang@outlook.com 
*/
#pragma GCC optimize(3)
#pragma GCC target("avx")
#define REP(i, s, e) for (register int i(s), end_##i(e); i <= end_##i; i++)
#define DEP(i, s, e) for (register int i(s), end_##i(e); i >= end_##i; i--)
#define DEBUG fprintf(stderr, "Passing [%s] in Line %d\n", __FUNCTION__, __LINE__)

#include <bits/stdc++.h>
#include <bits/extc++.h>
#define int long long
using namespace std;
const int maxn = 2e5 + 10;

int mul(int a, int b, const int p)
{
	int res = (a * b - (int)((long double)a / p * b) * p) % p;
	if (res < 0) res += p;
	return res;
}
int MOD;
const int w = 32000;
int pre1[w + 5], pre2[w + 5];
inline int pow2(int b) {return mul(pre1[b % w], pre2[b / w], MOD);}

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

int n, a[maxn], s[maxn];
int ans;

__gnu_pbds :: tree <int, int> cnt;

inline void chkmax(int &x, int y) {if (x < y) x = y;}
inline void chkmin(int &x, int y) {if (x > y) x = y;}

int lg[maxn];
const __int128 Two = 2;

int head, tail;
pair <int, int> q[maxn * 21];

//void cdq(int l, int r)

mt19937 hh;
inline int randint(int l, int r) {return (__int128)hh() * hh() % (r - l + 1) + l;}

bool isprime(int x)
{
	if (x <= 2) return x == 2;
	for (int i = 2; i * i <= x; i++) if (x % i == 0) return 0;
	return 1;
}
namespace miller
{
	int power_pow(int base, int b, const int p)
	{
		int ans = 1;
		while (b)
		{
			if (b & 1) ans = mul(ans, base, p);
			base = mul(base, base, p);
			b >>= 1;
		}
		return ans;
	}
	int totst[] = {2, 3, 13, 17, 19, 23};
	bool miller_rabin(int n)
	{
		if (n < 3) return n == 2;
		if (!(n & 1)) return 0;
		int a = n - 1, b = 0;
		while (!(a & 1)) a >>= 1, b++;
		for (int x : totst)
		{
			if (n == x) return 1;
			int v = power_pow(x, a, n);
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

void init(int l, int r)
{
	while (!miller :: miller_rabin(MOD)) MOD = randint(l, r);
	const int mod = MOD;
	pre1[0] = 1;
	REP(i, 1, w) pre1[i] = 2 * pre1[i - 1] % mod;
	pre2[0] = 1;
	REP(i, 1, w) pre2[i] = (__int128)pre1[w] * pre2[i - 1] % mod;
	REP(i, 1, n) s[i] = (s[i - 1] + pow2(a[i])) % mod;
}
signed main()
{
	freopen("A.in", "r", stdin);
	freopen("std.out","w",stdout);
	n = read<int>();
	REP(i, 1, n) a[i] = read<int>();
	REP(i, 2, n) lg[i] = lg[i >> 1] + 1;
	hh = mt19937(114514);//time(0));

	init(5e17, 1e18);

	q[0] = make_pair(1, n);
	while (head <= tail)
	{
		int l = q[head].first, r = q[head].second;
		head++;
		if (l == r)
		{
			ans++;
			continue;
		}
		const int MOD = ::MOD;
		int mid = l + r >> 1;
		int i, j, Max;

		cnt.clear();Max = 0;
		for (i = mid + 1, j = mid + 1; j <= r; j++)
		{
			chkmax(Max, a[j]);
			while (l < i && a[i - 1] <= Max)
			{
				i--;
				cnt[s[i - 1]]++;
			}
			int t = pow2(Max);
			int tmp = 0;
			REP(x, Max, Max + lg[j - i + 1])
			{
				int val = (s[j] + MOD - t) % MOD;
				cout << val << ' '<< cnt[val] << endl;
				auto it = cnt.find(val);
				if (it != cnt.end()) tmp += it -> second;
				t = 2 * t % MOD;
			}
			ans += tmp;
		}
		cout << endl;

		cnt.clear();Max = 0;
		for (i = mid, j = mid; l <= i; i--)
		{
			chkmax(Max, a[i]);
			while (j < r && a[j + 1] < Max)
			{
				j++;
				cnt[s[j]]++;
			}
			int tmp = 0;
			if (j > mid)
			{
				int t = pow2(Max);
				REP(k, Max, Max + lg[j - i + 1])
				{
					int val = (s[i - 1] + t) % MOD;
					cout << val << ' ' << cnt[val] << endl;
					auto it = cnt.find(val);
					if (it != cnt.end()) tmp += it -> second;
					t = 2 * t % MOD;
				}
			}
			ans += tmp;
		}
		cout << endl<<endl;
		q[++tail] = make_pair(l, mid);
		q[++tail] = make_pair(mid + 1, r);
	}

	cout << (long long)ans << endl;
	cerr << clock() * 1. / CLOCKS_PER_SEC << endl;
	return 0;
}
