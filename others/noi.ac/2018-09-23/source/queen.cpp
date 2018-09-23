#define DREP(i, s, e) for(register int i = s; i >= e ;i--)
#define  REP(i, s, e) for(register int i = s; i <= e ;i++)

#define DEBUG fprintf(stderr, "Passing [%s] in Line %d\n", __FUNCTION__, __LINE__)
#define chkmax(a, b) a = max(a, b)
#define chkmin(a, b) a = min(a, b)

#include <bits/stdc++.h>

using namespace std;
const int maxn = 1e5 + 10, maxm = 1e5 + 10;

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

int m, n, k;

pair <int, int> a[maxn];

set <int> line[maxn];//横着
set <int> row[maxn];//竖着

set <int> :: iterator it;

int w[10];

set <int> A[maxn << 1], B[maxn << 1];

int main()
{
#ifdef CraZYali
	freopen("queen.in", "r", stdin);
	freopen("queen.out", "w", stdout);
#endif
	cin >> n >> m;
	REP(i, 1, m) scanf("%d%d", &a[i].first, &a[i].second);
	REP(i, 1, m) line[a[i].first].insert(a[i].second);
	REP(i, 1, m) row[a[i].second].insert(a[i].first);

	REP(i, 1, m) A[a[i].first + a[i].second].insert(a[i].second);
	REP(i, 1, m) B[a[i].first - a[i].second + n].insert(a[i].second);

	REP(i, 1, m)
	{
		register int cnt = 0;
		it = row[a[i].second].lower_bound(a[i].first);
		if (it != row[a[i].second].begin())		++cnt;
		if (it != row[a[i].second].end())
		{
			it++;
			if (it != row[a[i].second].end())	++cnt;
		}
		it = line[a[i].first].lower_bound(a[i].second);
		if (it != line[a[i].first].begin())		++cnt;
		if (it != line[a[i].first].end())
		{
			it++;
			if (it != line[a[i].first].end())	++cnt;
		}
		register int k = a[i].first + a[i].second;
		it = A[k].lower_bound(a[i].second);
		if (it != A[k].begin())					++cnt;
		if (it != A[k].end())
		{
			it++;
			if (it != A[k].end())				++cnt;
		}
		it = B[a[i].first - a[i].second + n].lower_bound(a[i].second);
		if (it != B[a[i].first - a[i].second + n].begin())		++cnt;
		if (it != B[a[i].first - a[i].second + n].end())
		{
			it++;
			if (it != B[a[i].first - a[i].second + n].end())	++cnt;
		}
		w[cnt]++;
	}

	REP(i, 0, 8) printf("%d ", w[i]);

	return 0;
}
