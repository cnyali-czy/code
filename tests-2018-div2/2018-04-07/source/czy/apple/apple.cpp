#define REP(i, s, e) for(register int i = s; i <= e ; i++)
#define DEBUG fprintf(stderr, "Passing [%s] in Line %d\n", __FUNCTION__, __LINE__)

#include <bits/stdc++.h>

using namespace std;

int T, n;
bool can[1000];

int main()
{
	freopen("apple.in", "r", stdin);
	freopen("apple.out", "w", stdout);
	cin >> T;
	/*
	int x = 420 / 35, y = 420 / 20, z = 420 / 15;
	REP(i, 0, x)
		REP(j, 0, y)
			REP(k, 0, z)
			{
				int temp = i * 35 + j * 20 + k * 15;
				if (temp <= 420) can[temp] = 1 ;
			}
	while (T --> 0)
	{
		scanf("%d", &n);
		if (n < 15)	printf("-1\n");
		else
		{
			int ans = 1e9;
			n %= 420;
			REP(i, 0, n)
				if (can[i]) ans = min(ans, n - i);
			printf("%d\n", ans);
		}
	}*/
	while (T --> 0)
	{
		scanf("%d", &n);
		if (n < 15) printf("-1\n");
		else if (20 <= n && n <= 30) printf("%d\n", n % 10);
		else printf("%d\n", n % 5);
	}
	return 0;
}
