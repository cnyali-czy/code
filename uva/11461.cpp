#define  REP(i, s, e) for(register int i = s; i <= e ;i++)
#define DREP(i, s, e) for(register int i = s; i >= e ;i--)

#define DEBUG fprintf(stderr, "Passing [%s] in LINE %d\n", __FUNCTION__, __LINE__)
#define chkmin(a, b) a = min(a, b)
#define chkmax(a, b) a = max(a, b)

#include <bits/stdc++.h>

using namespace std;
const int Max = 100000;

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

int cnt[Max + 10];

int main()
{
#ifdef CraZYali
	freopen("11461.in", "r", stdin);
	freopen("11461.out", "w", stdout);
#endif
	REP(i, 1, i)
		if (i * i > Max) break;
		else cnt[i * i] = 1;
	REP(i, 1, Max) cnt[i] += cnt[i - 1];
	while (1)
	{
		int a, b;
		a = read<int>(); b = read<int>();
		if (!(a * b)) return 0;
		printf("%d\n", cnt[b] - cnt[a - 1]);
	}


	return 0;
}
