#define DREP(i, s, e) for(register int i = s; i >= e ;i--)
#define  REP(i, s, e) for(register int i = s; i <= e ;i++)

#define DEBUG fprintf(stderr, "Passing [%s] in Line %d\n", __FUNCTION__, __LINE__)
#define chkmax(a, b) a = max(a, b)
#define chkmin(a, b) a = min(a, b)

#include <bits/stdc++.h>

#define int long long
using namespace std;

int gcd(int a, int b) {return b ? a : gcd(b, a % b);}

int A, B, C, D, ans;

signed main()
{
#ifdef CraZYali
	freopen("A.in", "r", stdin);
	freopen("A.out", "w", stdout);
#endif
	cin >> A >> B >> C >> D;
	
	REP(i, A, B)
		REP(j, C, D)
			if (0 <= (i + j) / gcd(i, j) && (i + j) / gcd(i, j) <= 999) ans++;
	cout << ans;
	

	return 0;
}
