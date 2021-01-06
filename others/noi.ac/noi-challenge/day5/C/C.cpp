#define REP(i, s, e) for (register int i(s), end_##i(e); i <= end_##i; i++)
#define DEP(i, s, e) for (register int i(s), end_##i(e); i >= end_##i; i--)

#include <cassert>
#include <algorithm>
#include <iostream>
#include <cstdio>
#define i64 long long
#define u64 unsigned long long

using namespace std;
const int maxn = 1e7 + 10;

int prime[maxn], phi[maxn], p_cnt;
bool notp[maxn];
u64 sphi[maxn];

void init(int n)
{
	phi[1] = sphi[1] = 1;
	REP(i, 2, n)
	{
		if (!notp[i])
		{
			prime[++p_cnt] = i;
			phi[i] = i - 1;
		}
		REP(j, 1, p_cnt)
		{
			int t = i * prime[j];
			if (t > n) break;
			notp[t] = 1;
			if (i % prime[j] == 0)
			{
				phi[t] = phi[i] * prime[j];
				break;
			}
			else
				phi[t] = phi[i] * (prime[j] - 1);
		}
		sphi[i] = sphi[i - 1] + phi[i];
	}
}

inline u64 s1(u64 l, u64 r) {return (l + r) * (r - l + 1) / 2;}
u64 s2(u64 n)
{
	u64 x = n, y = n + 1, z = n + n + 1;
	if (x % 3 == 0) x /= 3;
	else if (y % 3 == 0) y /= 3;
	else z /= 3;
	if (x % 2 == 0) x /= 2;
	else if (y % 2 == 0) y /= 2;
	else z /= 2;
	return x * y * z;
}
u64 s2(u64 l, u64 r) {return s2(r) - s2(l - 1);}

u64 calc(int L, int R, int n, int j)
{
	if (L > R) return 0;
	return s1(L, R) * (n + 1) - s2(L, R) * j;
}

u64 f(const int n, const int m)
{
	u64 res = 0;
	const int N = n + 1;
	for (int i = 1, j; i <= m; i = j + 1)
	{
		j = min(min(n / (n / i), N / (N / i)), m);
		const int I = i;
		u64 LIM = (n + 1) / I - 1;
		res += LIM * (LIM + 1) / 2 * s1(i, j);
		res += s1(LIM + 1, n / I) * (n + 1) * (j - i + 1);
		res -= s2(LIM + 1, n / I) * s1(i, j);
	}
	/*
	REP(j, 1, m)
	{
		const int J = j;
		u64 LIM = (n + 1) / J - 1;
		res += LIM * (LIM + 1) / 2 * j;
		res += s1(LIM + 1, n / J) * (n + 1);
		res -= s2(LIM + 1, n / J) * j;
		//res += calc(LIM + 1, n / J, n, j);
	}
	*/
	return res;
}
int n, m;

int main()
{
#ifdef CraZYali
	freopen("C.in", "r", stdin);
	freopen("C.out", "w", stdout);
#endif
	cin >> n >> m;
	init(m);
	u64 ans = 0;
	for (int Ti = 1, Tj; Ti <= m; Ti = Tj + 1)
	{
		Tj = min(n / (n / Ti), m / (m / Ti));
		ans += f(n / Ti, m / Ti) * (sphi[Tj] - sphi[Ti - 1]);
	}
	cout << ans % (1ll << 60) << endl;
	return 0;
}
