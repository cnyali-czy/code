#define DREP(i, s, e) for(int i = s; i >= e ;i--)
#define  REP(i, s, e) for(int i = s; i <= e ;i++)

#define DEBUG fprintf(stderr, "Passing [%s] in Line %d\n", __FUNCTION__, __LINE__)
#define chkmax(a, b) a = max(a, b)
#define chkmin(a, b) a = min(a, b)

#include <iostream>
#include <cstdio>
#define int long long

using namespace std;
const int maxn = 1e5 + 10;

int n, m, ans, cnt[maxn];
//ans = \sum_i \sum_j (i,j) - nm

signed main()
{
#ifdef CraZYali
	freopen("2005.in", "r", stdin);
	freopen("2005.out", "w", stdout);
#endif
	cin >> n >> m;
	ans = -n * m;
	int N(min(n, m));
	DREP(i, N, 1)
	{
		int &c = cnt[i];
		c = (n/i) * (m/i);
		for (int j = i + i; j <= N;j += i) c -= cnt[j];
		ans += i * c * 2;
	}
	cout << ans << endl;	
	return 0;
}
