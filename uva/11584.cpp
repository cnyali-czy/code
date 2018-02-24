#define DREP(i, s, e) for(register int i = s; i >= e ;i--)
#define  REP(i, s, e) for(register int i = s; i <= e ;i++)

#define DEBUG fprintf(stderr, "Passing [%s] in Line %d\n", __FUNCTION__, __LINE__)
#define chkmax(a, b) a = max(a, b)
#define chkmin(a, b) a = min(a, b)

#include <algorithm>
#include <iostream>
#include <cstdlib>
#include <cstring>
#include <cstdio>
#include <bitset>
#include <vector>
#include <cmath>
#include <queue>
#include <map>
#include <set>

using namespace std;
const int maxn = 1010;

int m, n, k;
char s[maxn];

int dp[maxn];
inline bool OK(int _s, int _t)
{
	while (_s <= _t)
		if (s[_s] ^ s[_t]) return 0;
		else _s++, _t--;
	return 1;
}

int main()
{
#ifdef CraZYali
	freopen("11584.in", "r", stdin);
	freopen("11584.out", "w", stdout);
#endif
	register int T;
	cin >> T;
	while (T--)
	{
		scanf("%s", s + 1);
		n = strlen(s + 1);
		memset(dp, 0, sizeof(dp));
		REP(i, 1, n) dp[i] = i;
		REP(i, 2, n)
			REP(j, 1, i)
				if (OK(j, i)) chkmin(dp[i], dp[j - 1] + 1);
		printf("%d\n", dp[n]);
	}

	return 0;
}
