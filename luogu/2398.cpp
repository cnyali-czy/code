#define  REP(i, s, e) for (int i = s; i <= e; i++)
#define DREP(i, s, e) for (int i = s; i >= e; i--)
#define DEBUG fprintf(stderr, "Passing [%s] in Line %d\n", __FUNCTION__, __LINE__)

#define chkmax(a, b) a = max(a, b)
#define chkmin(a, b) a = min(a, b)

#include <iostream>
#include <cstdio>
using namespace std;
const int maxn = 1e6 + 10;
long long n, ans, f[maxn];

int main()
{
#ifdef CraZYali
	freopen("2398.in", "r", stdin);
	freopen("2398.out", "w", stdout);
#endif
	cin >> n;
	DREP(i, n, 1)
	{
        f[i] = n / i * (n / i);
		REP(j, 2, 2333333)
			if (i * j > n) break;
			else f[i] -= f[i * j];
		ans += f[i] * i;
	}
	cout << ans << endl;
	return 0;
}
