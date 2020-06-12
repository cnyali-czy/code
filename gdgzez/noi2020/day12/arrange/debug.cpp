/*
	Problem:	arrange.cpp
	Time:		2020-06-12 08:43
	Author:		CraZYali
	E-Mail:		yms-chenziyang@outlook.com 
*/

#define REP(i, s, e) for (register int i(s), end_##i(e); i <= end_##i; i++)
#define DEP(i, s, e) for (register int i(s), end_##i(e); i >= end_##i; i--)
#define DEBUG fprintf(stderr, "Passing [%s] in Line %d\n", __FUNCTION__, __LINE__)

#define chkmax(a, b) (a < (b) ? a = (b) : a)
#define chkmin(a, b) (a > (b) ? a = (b) : a)

#include <cassert>
#include <set>
#include <iostream>
#include <cstdio>
#ifdef CraZYali
#include <ctime>
#endif

using namespace std;
const int maxn = 2e5 + 10;

int bg[maxn], ne[maxn << 1], to[maxn << 1], e;
inline void add(int x, int y)
{
	e++;
	to[e] = y;
	ne[e] = bg[x];
	bg[x] = e;
}

template <typename T>
inline T read()
{
	T ans = 0, flag = 1;
	char c = getchar();
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

#define file(FILE_NAME) freopen(FILE_NAME".in", "r", stdin), freopen(FILE_NAME".out", "w", stdout)

int n, k, a[maxn];

int M, siz[maxn], cnt[maxn];
multiset <int> s[maxn];
void dfs0(int x, int fa = 0)
{
	s[x].clear();
	cnt[x] = 1;
	siz[x] = 1;
	int Max = 0;
	for (int i = bg[x]; i; i = ne[i]) if (to[i] ^ fa)
	{
		dfs0(to[i], x);
		siz[x] += siz[to[i]];
		if (cnt[to[i]] == siz[to[i]]) cnt[x] += cnt[to[i]];
		else
		{
			chkmax(Max, cnt[to[i]]);
			s[x].emplace(cnt[to[i]]);
		}
	}
	cnt[x] += Max;
	cnt[x] *= (a[x] >= M);
}
bool flag;

int tmp[1005][1005];

void dfs(int x, int fa = 0)
{
	printf("M = %d x = %d\n", M, x);
	REP(i, 1, n) printf("%d%c", cnt[i], i == end_i ? '\n' : ' ');
	REP(i, 1, n) printf("%d%c", tmp[x][i], i == end_i ? '\n' : ' ');
	REP(i, 1, n)
	{
		printf("%d: ", i);
		for (auto j : s[i]) cout << j << ' ' ;cout << endl;
	}
	cout<<endl;
	REP(i, 1, n) assert(cnt[i] == tmp[x][i]);
	if (flag) return;
	if (cnt[x] >= k) {flag = 1;return;}
	for (int i = bg[x]; i; i = ne[i]) if (to[i] ^ fa)
	{
		int y = to[i];
		int cx = cnt[x], cy = cnt[y];
		if (a[x] >= M)
		{
			if (cnt[y] == siz[y]) cnt[x] -= cnt[y];
			else
			{
				cnt[x] -= *s[x].rbegin();
				s[x].erase(s[x].find(cnt[y]));
				if (s[x].size()) cnt[x] += *s[x].rbegin();
			}
		}
		if (a[y] >= M)
		{
			if (cnt[x] == n - siz[y]) cnt[y] += cnt[x];
			else
			{
				if (s[y].size()) cnt[y] -= *s[y].rbegin();
				s[y].emplace(cnt[x]);
				cnt[y] += *s[y].rbegin();
			}
		}
		dfs(y, x);if (flag) return;
		if (a[y] >= M)
		{
			if (cnt[x] == n - siz[y]) cnt[y] -= cnt[x];
			else
			{
				cnt[y] -= *s[y].rbegin();
				s[y].erase(s[y].find(cnt[x]));
				if (s[y].size()) cnt[y] += *s[y].rbegin();
			}
		}
		if (a[x] >= M)
		{
			if (cnt[y] == siz[y]) cnt[x] += cnt[y];
			else
			{
				if (s[x].size()) cnt[x] -= *s[x].rbegin();
				s[x].emplace(cnt[y]);
				cnt[x] += *s[x].rbegin();
			}
		}
		assert(cx == cnt[x]);
		assert(cy == cnt[y]);
	}
}

bool judge(int mid)
{
	M = mid;
	DEP(i, n, 1)
	{
		dfs0(i);
		copy(cnt, cnt + n + 1, tmp[i]);
	}
	dfs0(1);
	flag = 0;
	dfs(1);
	return flag;
}

int main()
{
#ifdef CraZYali
	file("arrange");
#endif
	n = read<int>();k = read<int>();
	REP(i, 1, n) a[i] = read<int>();
	REP(i, 2, n)
	{
		int x(read<int>()), y(read<int>());
		add(x, y);add(y, x);
	}
	int l = 1, r = 0, good = 1;
	REP(i, 1, n) chkmax(r, a[i]);
	while (l <= r)
	{
		int mid = l + r >> 1;
		if (judge(mid)) {good = mid;l = mid + 1;}
		else r = mid - 1;
	}
	cout << good << endl;
#ifdef CraZYali
	cerr << clock() * 1. / CLOCKS_PER_SEC << endl;
#endif
	return 0;
}
