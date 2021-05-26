#include <bits/stdc++.h>

using namespace std;

int n, m, k, Min = (((1 << 30) - 1) << 1) + 1;

int main()
{
#ifdef CraZYali
	freopen("b.in", "r", stdin);
	freopen("b.out", "w", stdout);
#endif
	cin >> n >> m;
	for (register int i = 1; i <= n ; i ++)
	{
		scanf("%d", &k);
		m -= k;
		Min = min(Min, k);
	}
	printf("%d\n", n + m / Min);
	return 0;
}
