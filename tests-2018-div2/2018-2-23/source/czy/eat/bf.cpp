#define  REP(i, s, e) for(register int i = s; i <= e ;i++)
#define DREP(i, s, e) for(register int i = s; i >= e ;i--)

#define DEBUG fprintf(stderr, "Passing [%s] in LINE %d\n", __FUNCTION__, __LINE__)
#define chkmin(a, b) a = min(a, b)
#define chkmax(a, b) a = max(a, b)

#include <bits/stdc++.h>

using namespace std;

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
const int maxn = 1010;
int a[maxn], b[maxn];

int main()
{
	freopen("eat.in", "r", stdin);
	freopen("bf.out", "w", stdout);
	n = read<int>();
	m = read<int>();
	REP(i, 1, n)
		a[i] = read<int>();
	REP(i, 1, n)
		b[i] = read<int>();
	int ans = 0;
	REP(i, 1, n)
		REP(j, 1, n)
			ans += a[i] > b[j];
	cout << ans;

	return 0;
}

