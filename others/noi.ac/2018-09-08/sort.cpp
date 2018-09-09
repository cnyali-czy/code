#define DREP(i, s, e) for(register int i = s; i >= e ;i--)
#define  REP(i, s, e) for(register int i = s; i <= e ;i++)

#define DEBUG fprintf(stderr, "Passing [%s] in Line %d\n", __FUNCTION__, __LINE__)
#define chkmax(a, b) a = max(a, b)
#define chkmin(a, b) a = min(a, b)

#include <bits/stdc++.h>

using namespace std;
const int maxn = 50000 + 10;

int n, m, k;
int a[maxn];

namespace cheat
{
	void work()
	{
		REP(i, 1, n)
			REP(j, 1, n - i)
				if (a[j] > a[j + 1])
				{
					swap(a[j], a[j + 1]);
					printf("%d %d\n", j, j + 1);
				}
		printf("-1 -1");
	}
};

int main()
{
#ifdef CraZYali
	freopen("sort.in", "r", stdin);
	freopen("sort.out", "w", stdout);
#endif
	cin >> n;
	REP(i, 1, n) scanf("%d", a + i);
	
	cheat::work();


	return 0;
}
