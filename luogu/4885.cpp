#define DREP(i, s, e) for(register int i = s; i >= e ;i--)
#define  REP(i, s, e) for(register int i = s; i <= e ;i++)

#define DEBUG fprintf(stderr, "Passing [%s] in Line %d\n", __FUNCTION__, __LINE__)
#define chkmax(a, b) a = max(a, b)
#define chkmin(a, b) a = min(a, b)

#include <bits/stdc++.h>

using namespace std;
const int maxs = 5e5 + 10, maxq = 5e5 + 10;

template <typename T> inline T read()
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

template <typename T> void write(T x)
{
	if (x < 0) putchar('-'), write(-x);
	else if (x / 10) write(x / 10);
	putchar(x % 10 + '0');
}

int m, n, k, s, q;

pair <int, int> S[maxs];

int main()
{
#ifdef CraZYali
	freopen("4885.in", "r", stdin);
	freopen("4885.out", "w", stdout);
#endif
	cin >> n >> m >> s >> q;
	REP(i, 1, s)
	{
		S[i].first = read<int>();
		S[i].second = read<int>();
	}
		
	
	return 0;
}
