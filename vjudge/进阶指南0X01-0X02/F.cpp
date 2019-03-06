#define  REP(i, s, e) for (int i = s; i <= e; i++)
#define DREP(i, s, e) for (int i = s; i >= e; i--)
#define DEBUG fprintf(stderr, "Passing [%s] in Line %d\n", __FUNCTION__, __LINE__)

#define chkmax(a, b) a = max(a, b)
#define chkmin(a, b) a = min(a, b)

#include <iostream>
#include <cstdio>
#include <set>

using namespace std;
const int maxn = 10000 + 10;

template <typename T> T read()
{
	T ans = 0, p = 1;
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

set <pair <int, int> > S;
int d[maxn];

int n, R, H, I;

int main()
{
#ifdef CraZYali
	freopen("F.in", "r", stdin);
	freopen("F.out", "w", stdout);
#endif
	cin >> n >> I >> H >> R;
	while (R --> 0)
	{
		int a(read<int>()), b(read<int>());
		if (a > b) swap(a, b);
		if (S.find(make_pair(a, b)) != S.end()) continue;
		S.insert(make_pair(a, b));
		d[a+1]--;d[b]++;
	}
	REP(i, 1, n) printf("%d\n", (d[i] += d[i-1]) + H);
	return 0;
}
