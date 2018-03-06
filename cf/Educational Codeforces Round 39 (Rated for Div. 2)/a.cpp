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
const int maxn = 105;

template <typename T> T read()
{
	T ans(0), p(1);
	char c = getchar();
	while (!isdigit(c)) {
		if (c == '-') p = -1;
		c = getchar();
	}
	while (isdigit(c)) {
		ans = ans * 10 + c - 48;
		c = getchar();
	}
	return ans * p;
}
int m, n, k;
int a[maxn];
bool haA, haB;

int main()
{
#ifdef CraZYali
	freopen("a.in", "r", stdin);
	freopen("a.out", "w", stdout);
#endif
	n = read<int>();
	REP(i, 1, n)
	{
		a[i] = read<int>();
		if (a[i] > 0) haA = 1;
		if (a[i] < 0) haB = 1;
	}
	sort(a + 1, a + 1 + n);

	register int ans = 0;
	REP(i, 1, n) ans += abs(a[i]);
	cout << ans;
	return 0;
}
