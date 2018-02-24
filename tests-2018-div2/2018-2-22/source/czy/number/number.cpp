#define  REP(i, s, e) for(register int i = s; i <= e ;i++)
#define DREP(i, s, e) for(register int i = s; i >= e ;i--)

#define DEBUG fprintf(stderr, "Passing [%s] in LINE %d\n", __FUNCTION__, __LINE__)
#define chkmin(a, b) a = min(a, b)
#define chkmax(a, b) a = max(a, b)

#include <bits/stdc++.h>

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
int a[maxn];

int main()
{
	freopen("number.in", "r", stdin);
	freopen("number.out", "w", stdout);
	n = read<int>();
	REP(i, 1, n) a[i] = read<int>();
	sort(a + 1, a + 1 + n);
	int Max = -1;
	REP(i, 1, n / 2)
		chkmax(Max, a[i] + a[n - i + 1]);
	cout << Max;
	
	return 0;
}
