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
const int maxn = 10000 + 10;

template <typename T> T read()
{
	T ans(0), p(1);
	char c = getchar();
	while (!isdigit(c))
	{
		if (c == '-') p = -1;
		c = getchar();
	}
	while (isdigit(c))
	{
		ans = ans * 10 + c - 48;
		c = getchar();
	}
	return ans * p;
}
int m, n, k;
int a[maxn], b[maxn];

int main()
{
#ifdef CraZYali
	freopen("2327.in", "r", stdin);
	freopen("2327.out", "w", stdout);
#endif
	n = read<int>();
	REP(i, 1, n) a[i] = read<int>();
	int ans = 0;
	bool flag;

	flag = 1;
	b[1] = 1;
	REP(i, 2, n + 1)
	{
		b[i] = a[i - 1] - b[i - 1] - b[i - 2];
		if (b[i] > 1 || b[i] < 0)
		{
			flag = 0;
			break;
		}
	}
	ans += flag && !b[n + 1];
	
	flag = 1;
	b[1] = 0;
	REP(i, 2, n + 1)
	{
		b[i] = a[i - 1] - b[i - 1] - b[i - 2];
		if (b[i] > 1 || b[i] < 0)
		{
			flag = 0;
			break;
		}
	}
	ans += flag && !b[n + 1];

	cout << ans;
	return 0;
}
