#define REP(i, s, e) for (register int i = (s), end_##i = (e); i <= end_##i; i++)
#define DEP(i, s, e) for (register int i = (s), end_##i = (e); i >= end_##i; i--)
#define DEBUG fprintf(stderr, "Passing [%s] in Line %d\n", __FUNCTION__, __LINE__)

#define chkmax(a, b) (a < (b) ? a = (b) : a)
#define chkmin(a, b) (a > (b) ? a = (b) : a)

#include <algorithm>
#include <iostream>
#include <cassert>
#include <cstring>
#include <cstdlib>
#include <cstdio>
#include <ctime>
#include <vector>
#include <cmath>

using namespace std;
#define int long long
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

int m, n, k;
long long Rand() {return 1ll * rand() * rand();}
vector <pair <int, int> > v;
signed main()
{
	freopen("A.in", "w", stdout);
	srand(time(0));
	n = 10000;
	const long long N = 1e18, qq = 1e8;
	cout << n << endl;
	while (n--)
	{
		long long l = Rand() % N + 1, r = Rand() % N  + 1;
		if (l > r) swap(l, r);
		printf("%lld %lld\n", l, r);
	}
	return 0;
}
