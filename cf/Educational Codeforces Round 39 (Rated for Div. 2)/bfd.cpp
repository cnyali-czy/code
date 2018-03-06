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
const int maxn = 100010;

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

int a[500][500];

inline int calc()
{
	register int ans = 0;
	REP(i, 1, n)
	{
		int s = m + 1, t = -1;
		REP(j, 1, m)
			if (a[i][j]) {chkmin(s, j);chkmax(t, j);}
		ans += t - s + 1;
	}
	return ans;
}

int ans = 1e9;

inline void dfs(int x, int left)
{
	if (x == k || !left)
	{
		chkmin(ans, calc());
		return;	
	}
	x++;
	REP(i, 1, n)
		REP(j, 1, m)
			if (a[i][j])
			{
				a[i][j] = 0;
				dfs(x, left - 1);
				a[i][j] = 1;
			}
}

int main()
{
	freopen("d.in", "r", stdin);
	freopen("bfd.out", "w", stdout);
	n = read<int>();
	m = read<int>();
	k = read<int>();
	int left = 0;
	REP(i, 1, n)
		REP(j, 1, m)
			scanf("%1d", &a[i][j]), left += a[i][j];
	dfs(0, left);
	cout << ans << endl;
	return 0;
}

