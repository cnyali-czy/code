/*
 * File Name:	530.cpp
 * Author	:	CraZYali
 * Time		:	2020.02.11 17:28
 * Email	:	yms-chenziyang@outlook.com
 */

#define DEP(i, s, e) for (register int i(s), end_##i(e); i >= end_##i; i--)
#define REP(i, s, e) for (register int i(s), end_##i(e); i <= end_##i; i++)
#define DEBUG fprintf(stderr, "Passing [%s] in Line %d\n", __FUNCTION__, __LINE__)

#define chkmax(a, b) (a < (b) ? a = (b) : a) 
#define chkmin(a, b) (a > (b) ? a = (b) : a) 

#include <algorithm>
#include <iostream>
#include <cstdio>
#define i64 long long
using namespace std;
const int maxm = 100 + 5;

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

int prime[maxm], p_cnt;
bool can_append(int x)
{
	REP(i, 1, p_cnt) if (x % prime[i] == 0) return 0;
	return 1;
}
int m;
pair <int, i64> a[maxm];

int main()
{
#ifdef CraZYali
	file("530");
#endif
	prime[++p_cnt] = 2;
	for (int i = 3; p_cnt <= 100; i += 2) if (can_append(i)) {prime[++p_cnt] = i;if (p_cnt >= 100) break;}
	register int T = read<int>();
	while (T--)
	{
		m = read<int>();
		REP(i, 1, m) a[i] = make_pair(i, read<i64>());
		random_shuffle(a + 1, a + 1 + m);
		i64 ans = 1;
		REP(i, 1, m)
		{
			i64 l = ans, r = 1e18;
			while (l ^ r)
			{
				i64 mid = l + r >> 1, n = mid;
				i64 res = 0;
				while (n)
				{
					n /= prime[a[i].first];
					res += n;
					if (res >= a[i].second) break;
				}
				if (res >= a[i].second) r = mid;
				else l = mid + 1;
			}
			ans = r;
		}
		printf("%lld\n", ans);
	}
	return 0;
}
