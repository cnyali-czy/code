#define  REP(i, s, e) for (int i = s; i <= e; i++)
#define DREP(i, s, e) for (int i = s; i >= e; i--)
#define DEBUG fprintf(stderr, "Passing [%s] in Line %lld\n", __FUNCTION__, __LINE__)

#define chkmax(a, b) a = max(a, b)
#define chkmin(a, b) a = min(a, b)

#include <algorithm>
#include <iostream>
#include <cstdio>
#define int long long

using namespace std;
const int maxn = 1000 + 10, maxm = 1000 + 10;

int n, m;
pair <int, int> b[maxm * maxn];
bool cmp(pair <int, int> A, pair <int, int> B) {return A.first < B.first;}

int c[maxm * maxn], t[maxn * maxm], cur;
void add(int x)
{
	while (x <= cur)
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
int calc(int a[], int n)
{
	REP(i, 1, n) b[i] = make_pair(a[i], i);
	sort(b + 1, b + 1 + n, cmp);
	REP(i, 1, n) a[b[i].second] = i;
	int ret = 0;
	REP(i, 1, n)
	{
		add(a[i]);
		ret += 1ll * i - sum(a[i]);
	}
	REP(i, 1, n) c[i] = 0;
	return ret;
}

int a[maxn][maxm], r;

signed main()
{
#ifdef CraZYali
	freopen("D.in", "r", stdin);
	freopen("D.out", "w", stdout);
#endif
	while (scanf("%lld%lld", &n, &m) && (n + m))
	{
		cur = 0;
		REP(i, 1, n)
			REP(j, 1, m)
			{
				scanf("%lld", a[i] + j);
				if (!a[i][j]) r = i;
				else t[++cur] = a[i][j];
			}
		int ret = calc(t, cur);
		if (m & 1) printf("%s\n", (ret & 1) ? "NO" : "YES");
		else printf("%s\n", (ret % 2 == (n - r) % 2) ? "YES" : "NO");
	}
	return 0;
}
