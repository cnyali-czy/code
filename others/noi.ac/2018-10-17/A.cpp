#define DREP(i, s, e) for(register int i = s; i >= e ;i--)
#define  REP(i, s, e) for(register int i = s; i <= e ;i++)

#define DEBUG fprintf(stderr, "Passing [%s] in Line %d\n", __FUNCTION__, __LINE__)
#define chkmax(a, b) a = max(a, b)
#define chkmin(a, b) a = min(a, b)

#include <bits/stdc++.h>

#define int long long
using namespace std;
const int MOD = 1e9 + 7;

int gcd(int a, int b) {return !b ? a : gcd(b, a % b);}

int A, B, C, D, ans;

int top(int x, int y) {return x / y + (x % y == 0 ? 0 : 1);}

signed main()
{
#ifdef CraZYali
	freopen("A.in", "r", stdin);
	freopen("A.out", "w", stdout);
#endif
	cin >> A >> B >> C >> D;
	REP(i, 1, 999)
		REP(j, 1, 999)
			if (gcd(i, j) == 1 && i + j <= 999)
			{
				register int l = max(top(A, i), top(C, j));
				register int r = min(B / i, D / j);
				if (l > r) continue;
				ans = (ans + r - l + 1) % MOD;
			}
	cout << (ans + MOD) % MOD;
	return 0;
}
