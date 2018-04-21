#define DREP(i, s, e) for(register int i = s; i >= e ;i--)
#define  REP(i, s, e) for(register int i = s; i <= e ;i++)

#define DEBUG fprintf(stderr, "Passing [%s] in Line %d\n", __FUNCTION__, __LINE__)
#define chkmax(a, b) a = max(a, b)
#define chkmin(a, b) a = min(a, b)

#include <iostream>
#include <cstdio>

using namespace std;
const int maxn = 20000 + 10;

int n, k;

int main()
{
#ifdef CraZYali
	freopen("11892.in", "r", stdin);
	freopen("11892.out", "w", stdout);
#endif
	register int T;
	cin >> T;
	while (T --> 0)
	{
		scanf("%d", &n);
		bool win = 0;
		REP(i, 1, n)
		{
			scanf("%d", &k);
			if (k ^ 1) win = 1;
		}
		if (win) printf("poopi\n");
		else if (n % 2 == 0) printf("piloop\n");
		else printf("poopi\n");
	}
	return 0;
}
