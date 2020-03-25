#define REP(i, s, e) for (register int i = (s), end_##i = (e); i <= end_##i; i++)
#define DEP(i, s, e) for (register int i = (s), end_##i = (e); i >= end_##i; i--)
#define DEBUG fprintf(stderr, "Passing [%s] in Line %d\n", __FUNCTION__, __LINE__)

#define chkmax(a, b) a = max(a, (b))
#define chkmin(a, b) a = min(a, (b))

#include <iostream>
#include <cstring>
#include <cstdio>
#include <bitset>

using namespace std;
const int maxn = 1e6 + 10;

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

int m, n;

void merge(pair <int, int> a[], int n, pair <int, int> b[], int m, pair <int, int> c[])
{
	int N = 0, i = 1, j = 1;
	while (i <= n && j <= m)
		if (a[i] < b[j]) c[++N] = a[i++];
		else c[++N] = b[j++];
	while (i <= n) c[++N] = a[i++];
	while (j <= m) c[++N] = b[j++];
}

pair <int, int> cur[maxn], nxt1[maxn], nxt2[maxn], nxt[maxn];

bool good[maxn];
void solve()
{
	int N(0);
	cur[++N] = make_pair(1, n);
	DEP(i, n - 1, 1)
	{
		int c1(0), c2(0);
		REP(j, 1, N)
		{
			int l, r;
			l = max(1, cur[j].first - i), r = max(0, cur[j].second - i);
			if (l <= r) nxt1[++c1] = make_pair(l, r);
			l = min(n + 1, cur[j].first + i), r = min(n, cur[j].second + i);
			if (l <= r) nxt2[++c2] = make_pair(l, r);
		}
		merge(nxt1, c1, nxt2, c2, nxt);
		int M = 1;
		REP(i, 2, c1 + c2)
			if (nxt[i].first <= nxt[M].second) chkmax(nxt[M].second, nxt[i].second);
			else nxt[++M] = nxt[i];
		nxt[0] = make_pair(0, 0);
		nxt[M + 1] = make_pair(n + 1, n + 1);
		N = 0;
		REP(j, 1, M + 1)
		{
			if (nxt[j].first == nxt[j-1].second + 1) continue;
			cur[++N] = make_pair(nxt[j-1].second + 1, nxt[j].first - 1);
		}
	}
	REP(i, 1, N) REP(j, cur[i].first, cur[i].second) good[j] = 1;
}

int main()
{
#ifdef CraZYali
	file("C");
	freopen("C.err", "w", stderr);
#endif
	cin >> n >> m;
	solve();
	REP(i, 1, m) printf("%d", !good[read<int>()]);
	return 0;
}
