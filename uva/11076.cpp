#define DREP(i, s, e) for(register int i = s; i >= e ;i--)
#define  REP(i, s, e) for(register int i = s; i <= e ;i++)

#define DEBUG fprintf(stderr, "Passing [%s] in Line %d\n", __FUNCTION__, __LINE__)
#define chkmax(a, b) a = max(a, b)
#define chkmin(a, b) a = min(a, b)

#include <algorithm>
#include <iostream>
#include <cstdlib>
#include <cstring>
#include <cstdio>
#include <bitset>
#include <vector>
#include <cmath>
#include <queue>
#include <map>
#include <set>

using namespace std;
const int maxn = 20;

unsigned long long n, k;

unsigned long long one[maxn];
inline void init_one()
{
	REP(i, 1, 12)
		REP(j, 1, i)
			one[i] += pow(10, j - 1);
}

unsigned long long fac[maxn];
inline void init_fac()
{
	fac[0] = 1;
	REP(i, 1, 12)
		fac[i] = fac[i - 1] * i;
}

unsigned long long cnt[maxn];
unsigned long long sum, ans;

int main()
{
#ifdef CraZYali
	freopen("11076.in", "r", stdin);
	freopen("11076.out", "w", stdout);
#endif
//	while (scanf("%d", &n) != EOF && n) work();
	init_one();
	init_fac();
	while (scanf("%llu", &n) != EOF && n)
	{
		memset(cnt, 0, sizeof(cnt));
		sum = 0;
		REP(i, 1, n)
		{
			scanf("%llu", &k);
			cnt[k]++;
			sum += k;
		}
		ans = fac[n];
		REP(i, 0, 9) ans /= fac[cnt[i]];
		printf("%llu\n", ans * sum / n * one[n]);
	}
	return 0;
}
