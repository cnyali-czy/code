#define   REP(i, s, e) for(register long long i = s; i <= e ;i++)
#define  DREP(i, s, e) for(register long long i = s; i >= e ;i--)

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
const long long MOD = 100000007;

int main()
{
#ifdef CraZYali
	freopen("11490.in", "r", stdin);
	freopen("11490.out", "w", stdout);
#endif
	long long S;
	while (scanf("%lld", &S) != EOF && S)
	{
		bool flag = 0;
		for (register long long i = 1; i * i * 6 < S; i++)
		{
			long long temp = S - i * i * 6;
			if (temp % (7 * i) == 0)
			{
				long long ans = temp / (7 * i) % MOD;
				printf("Possible Missing Soldiers = %lld\n", (2ll * ans * ans )% MOD);
				flag = 1;
			}
		}
		if (!flag) printf("No Solution Possible\n");
		putchar(10);
	}

	return 0;
}
