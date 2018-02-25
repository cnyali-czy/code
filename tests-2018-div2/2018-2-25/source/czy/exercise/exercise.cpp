#define  REP(i, s, e) for(register int i = s; i <= e ;i++)
#define DREP(i, s, e) for(register int i = s; i >= e ;i--)

#define DEBUG fprintf(stderr, "Passing [%s] in LINE %d\n", __FUNCTION__, __LINE__)
#define chkmin(a, b) a = min(a, b)
#define chkmax(a, b) a = max(a, b)

#include <bits/stdc++.h>

using namespace std;
const int maxn = 2000;

long long k, need[maxn];
int n;

int main()
{
	freopen("exercise.in", "r", stdin);
	freopen("exercise.out", "w", stdout);
	cin >> k >> n;
	REP(i, 1, n)
	{
		long long x, y, z;
		scanf("%*s %lld %lld %lld", &x, &y, &z);
		REP(j, x, y) need[j] += z;
	}
	REP(i, 1, 1440)
	{
		k = k + 1 - need[i];
		if (k <= 0)
		{
			printf("Runtime Error\n%d", i);
			return 0;
		}
	}
	printf("Accepted\n%lld", k);
	return 0;
}
