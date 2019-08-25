#define  REP(i, s, e) for (int i = s; i <= e; i++)
#define DREP(i, s, e) for (int i = s; i >= e; i--)
#define DEBUG fprintf(stderr, "Passing [%s] in Line %d\n", __FUNCTION__, __LINE__)

#define chkmax(a, b) a = max(a, b)
#define chkmin(a, b) a = min(a, b)

#include <iostream>
#include <cstdio>
#include <cmath>
#include <tr1/unordered_map>
#define int long long

using namespace std;

int p, a, b, x1, t;

int exgcd(int a, int b, int &x, int &y)
{
	if (!b)
	{
		x = 1;
		y = 0;
		return a;
	}
	int res = exgcd(b, a % b, y, x);
	y -= a / b * x;
	return res;
}

inline int power_pow(int base, int b, int MOD)
{
	base %= MOD;
	int ans(1);
	while (b)
	{
		if (b & 1) ans = ans * base % MOD;
		base = base * base % MOD;
		b >>= 1;
	}
	return (ans + MOD) % MOD;
}
tr1::unordered_map <int, int> mp;
inline int bsgs(int A, int B, int C)
{
	A %= C;
	if(!A) return B ? -1 : 1;
	int m=sqrt(C) + 1, t = 1, I = 1, Im = power_pow(A, C-1-m, C);
	mp.clear();mp[1]=m+1;
	REP(i, 1, m - 1)
	{
		t = t * A % C;
		if (!mp[t]) mp[t]=i;
	}
	REP(k, 0, m - 1)
	{
		int i = mp[B * I % C];
		if (i)
		{
			if (i == m + 1) i = 0;
			return k * m + i;
		}
		I = I * Im % C;
	}
	return -1;
}
inline int cal1()
{
	int C = (t - x1 + p) % p, x, y;
	int t = exgcd(b, p, x, y);
	if (C % t) return -1;
	x = x * (C /= t) %p;
	if (x < 0) x += p;
	return x+1;
}
inline int cal2()
{
	int c = power_pow(a - 1, p - 2, p), A = (x1 + b * c) % p, C = (t + b * c) % p, x, y;
	int t = exgcd(A, p, x, y);
	if (C % t) return -1;
	C /= t;
	if (x < p) x = x % p + p;
	t = bsgs(a, x * C % p, p);
	return t == -1 ? -1 : t + 1;
}
signed main()
{
#ifdef CraZYali
	freopen("3122.in", "r", stdin);
	freopen("3122.out", "w", stdout);
#endif
	int Case;cin >> Case;
	while (Case--)
	{
		scanf("%lld%lld%lld%lld%lld", &p, &a, &b, &x1, &t);
		printf("%lld\n", x1 == t ? 1 : a == 0 ? b == t ? 2 : -1 : a == 1 ? cal1() : cal2());
	}
	return 0;
}
