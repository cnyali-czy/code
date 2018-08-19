#define  REP(i, s, e) for(register long long i = s; i <= e ;i++)
#define DREP(i, s, e) for(register long long i = s; i >= e ;i--)

#define DEBUG fprlong longf(stderr, "Passing [%s] in LINE %d\n", __FUNCTION__, __LINE__)
#define chkmin(a, b) a = min(a, b)
#define chkmax(a, b) a = max(a, b)

#include <bits/stdc++.h>

using namespace std;
const long long maxn = 50000 + 10;

long long ans, now, k, n;

bool flag;
long long Max = -1e9;

int main()
{
#ifdef CraZYali
	freopen("最大子段和.in", "r", stdin);
	freopen("最大子段和.out", "w", stdout);
#endif
	flag = 1;
	cin >> n;
	while (n--)
	{
		scanf("%lld", &k);
		now += k;
		chkmax(Max, k);
		if (now > 0) flag = 0;
		if (now < 0) now = 0;
		chkmax(ans, now);
	}
	cout << (flag ? Max : ans);

	return 0;
}
