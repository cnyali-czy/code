#define  REP(i, s, e) for (register int i = (s), end_##i = (e); i <= end_##i; i++)
#define DREP(i, s, e) for (register int i = (s), end_##i = (e); i >= end_##i; i--)
#define DEBUG fprintf(stderr, "Passing [%s] in Line %d\n", __FUNCTION__, __LINE__)

#define chkmax(a, b) a = max(a, (b))
#define chkmin(a, b) a = min(a, (b))

#include <algorithm>
#include <iostream>
#include <cstring>
#include <cstdlib>
#include <cstdio>
#include <cmath>
#include <queue>

using namespace std;
const int maxn = 200000 + 10;

template <typename T> T read()
{
	T ans(0), flag(1);
	char c(getchar());
	while (!isdigit(c))
	{
		if (c == '-') flag = -1;
		c = getchar();
	}
	while (isdigit(c))
	{
		ans = ans * 10 + c - 48;
		c = getchar();
	}
	return ans * flag;
}

void file(string s)
{
	freopen((s + ".in").c_str(), "r", stdin);
	freopen((s + ".out").c_str(), "w", stdout);
}

int n, m, a[maxn], s[maxn][2];

int main()
{
#ifdef CraZYali
	file("A");
#endif
	cin >> n >> m;
	REP(i, 1, n)
	{
		a[i] = read<int>();
		s[i][0] = s[i-1][0] ^ (i % 2 == 0 ? a[i] : 0); 
		s[i][1] = s[i-1][1] ^ (i % 2 == 1 ? a[i] : 0); 
	}
	while (m--)
	{
		int l(read<int>()), r(read<int>());
		if ((r - l + 1) % 2 == 0) printf("0\n");
		else
		{
			int keng = (l & 1);
			printf("%d\n", s[r][keng] ^ s[l-1][keng]);
		}
	}
	return 0;
}
