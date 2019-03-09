#define  REP(i, s, e) for (int i = s; i <= e; i++)
#define DREP(i, s, e) for (int i = s; i >= e; i--)
#define DEBUG fprintf(stderr, "Passing [%s] in Line %d\n", __FUNCTION__, __LINE__)

#define chkmax(a, b) a = max(a, b)
#define chkmin(a, b) a = min(a, b)

#include <algorithm>
#include <iostream>
#include <cstdio>
#include <cstring>
#include <map>

using namespace std;
const int maxn = 500000 + 10;

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

int n, a[maxn];
pair <int, int> b[maxn];
bool cmp(pair <int, int> A, pair <int, int> B) {return A.first < B.first;}

int c[maxn];
void add(int x)
{
	while (x <= n)
	{
		c[x]++;
		x += x & -x;
	}
}
int sum(int x)
{
	int y = 0;
	while (x > 0)
	{
		y += c[x];
		x -= x & -x;
	}
	return y;
}

int main()
{
#ifdef CraZYali
	freopen("C.in", "r", stdin);
	freopen("C.out", "w", stdout);
#endif
	b[0].first = -2e9;
	while (scanf("%d", &n) != EOF && n)
	{
		REP(i, 0, n + 10) c[i] = 0;
		REP(i, 1, n) b[i] = make_pair(a[i] = read<int>(), i);
		sort(b + 1, b + 1 + n, cmp);
		REP(i, 1, n) a[b[i].second] = (b[i].first == b[i-1].first ? b[i-1].second : i);
		long long ans = 0;
		REP(i, 1, n)
		{
			add(a[i]);
			ans += 1ll * (i - sum(a[i]));
		}
		printf("%lld\n", ans);
	}
	return 0;
}
