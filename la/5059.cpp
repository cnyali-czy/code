#define DREP(i, s, e) for(register long long i = s; i >= e ;i--)
#define  REP(i, s, e) for(register long long i = s; i <= e ;i++)

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
const long long maxn = 100 + 5;

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
long long n;

long long SG(long long x) {return x % 2 ? SG(x >> 1) : x >> 1;}

int main()
{
#ifdef CraZYali
	freopen("5059.in", "r", stdin);
	freopen("5059.out", "w", stdout);
#endif
	register long long T = read<long long>();
	while (T --> 0)
	{
		n = read<long long>();
		long long k = 0;
		while (n--) k ^= SG(read<long long>());
		if (k) printf("YES\n");
		else printf("NO\n");
	}
/*
	REP(i, 2, 60)
	{
		memset(vis, 0, sizeof(vis));
		REP(j, 1, i)
			if (j * 2 > i) break;
			else vis[SG[i - j]] = 1;
		register long long pos = 0;
		while (1)
			if (!vis[pos])
			{
				SG[i] = pos;
				break;
			}
			else pos++;
		printf("%d ", SG[i]);
	}
*/
	return 0;
}
