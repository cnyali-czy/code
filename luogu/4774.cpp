/*
 * File Name:	4774.cpp
 * Author	:	CraZYali
 * Time		:	2020.02.11 20:51
 * Email	:	yms-chenziyang@outlook.com
 */

#define DEP(i, s, e) for (register int i(s), end_##i(e); i >= end_##i; i--)
#define REP(i, s, e) for (register int i(s), end_##i(e); i <= end_##i; i++)
#define DEBUG fprintf(stderr, "Passing [%s] in Line %d\n", __FUNCTION__, __LINE__)

#define chkmax(a, b) (a < (b) ? a = (b) : a) 
#define chkmin(a, b) (a > (b) ? a = (b) : a) 

#include <cassert>
#include <algorithm>
#include <set>
#include <iostream>
#include <cstdio>
#define i128 long long
#define i128 __int128
using namespace std;
const int maxn = 1e5 + 10;

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

template <typename T>
T exgcd(T a, T b, T &x, T &y)
{
	if (!b)
	{
		x = 1;y = 0;
		return a;
	}
	T res = exgcd(b, a % b, y, x);
	y -= a / b * x;
	return res;
}
i128 inv(i128 a, i128 MOD)
{
	i128 x, y;
	exgcd(a, MOD, x, y);
	return x;
}

multiset <i128> S;
i128 a[maxn], p[maxn], ATK[maxn];
int reward[maxn], n, m;

namespace allone
{
	bool judge() {REP(i, 1, n) if (p[i] ^ 1) return 0;return 1;}
	void work() {i128 ans = 0;REP(i, 1, n) chkmax(ans, (ATK[i] + a[i] - 1) / ATK[i]);cout << (long long)ans << '\n';}
}
void output(i128 x)
{
	if (x / 10) output(x / 10);
	putchar(x % 10 + '0');
}
signed main()
{
#ifdef CraZYali
	file("4774");
#endif
	register int T = read<int>();
	while (T--)	
	{
		n = read<int>(), m = read<int>();
		REP(i, 1, n) a[i] = read<i128>();
		REP(i, 1, n) p[i] = read<i128>();
		REP(i, 1, n) reward[i] = read<int>();
		S.clear();
		while (m--) S.emplace(read<int>());
		REP(i, 1, n)
		{
			auto it = S.upper_bound(a[i]);
			if (it == S.begin()) ATK[i] = *it;
			else ATK[i] = *(--it);
			S.erase(it);S.emplace(reward[i]);
		}
		if (allone::judge()) {allone::work();continue;}
		bool flag = 1;
		int N = 0;
		REP(i, 1, n)
		{
			if (ATK[i] % p[i] == 0) {flag = 0;break;}
			int g = __gcd(ATK[i], p[i]);
			if (a[i] % g) {flag = 0;break;}
			ATK[i] /= g;p[i] /= g;a[i] /= g;
			a[i] *= inv(ATK[i], p[i]);
			a[i] = (a[i] % p[i] + p[i]) % p[i];
			if (a[i])
			{
				++N;
				a[N] = a[i];
				p[N] = p[i];
			}
		}
		if (flag)
		{
			i128 a1 = a[1], p1 = p[1];
//			cout << "func[1]: " << a[1] << ' ' << p[1] << endl;
			REP(i, 2, N)
			{
				i128 a2 = a[i], p2 = p[i], g = __gcd(p1, p2);
				if ((a2 - a1) % g)
				{
					flag = 0;
					puts("-1");
					break;
				}
				i128 kk = (a2 - a1) / g;
				p1 /= g;p2 /= g;
				i128 k1, k2_, k2;
				exgcd(p1, p2, k1, k2_);k2 = -k2_;
				k1 *= kk;k2_ *= kk;k2 *= kk;
				p1 *= g;p2 *= g;
//				printf("func[%d] : %lld %lld\n",i, a[i], p[i]);
//				printf("%lld * %lld - %lld * %lld = %lld\n", (i128)p1, (i128)k1, (i128)p2, (i128)k2, (i128)(a2 - a1));
//				printf("sol: %lld %lld\n", (i128)(a1 + p1 * k1), (i128)(a2 + p2 * k2));
				a1 += p1 * k1;
				p1 *= p2 / g;
				a1 = (a1 % p1 + p1) % p1;
			}
			if (flag)
			{
				output(a1);
				putchar(10);
			}
		}
		else puts("-1");
	}
	return 0;
}
