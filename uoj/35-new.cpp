#define REP(i, s, e) for (register int i(s), end_##i(e); i <= end_##i; i++)
#define DEP(i, s, e) for (register int i(s), end_##i(e); i >= end_##i; i--)

#include <vector>
#include <iostream>
#include <cstdio>
#include <cstring>

using namespace std;
const int maxn = 1e5 + 10;

inline int trans(char c)
{
	return c - 'a';
}

namespace SAM
{
	const int maxn = ::maxn << 1, sig = 26;
	int ch[maxn][sig], len[maxn], fail[maxn], id[maxn], cur = 1, lst = 1;
	inline void extend(int c, int _id)
	{
		int u = ++cur, v = lst;
		len[u] = len[v] + 1;
		id[u] = _id << 1 | 1;
		for (; v && !ch[v][c]; v = fail[v]) ch[v][c] = u;
		if (!v) fail[u] = 1;
		else if (len[ch[v][c]] == len[v] + 1) fail[u] = ch[v][c];
		else
		{
			int Old = ch[v][c], New = ++cur;
			len[New] = len[v] + 1;
			copy(ch[Old], ch[Old] + sig, ch[New]);
			fail[New] = fail[Old];
			fail[u] = fail[Old] = New;
			id[New] = _id << 1;
			for (; v && ch[v][c] == Old; v = fail[v]) ch[v][c] = New;
		}
		lst = u;
	}
	void clear()
	{
		REP(i, 1, cur)
		{
			REP(j, 0, sig - 1) ch[i][j] = 0;
			len[i] = fail[i] = id[i] = 0;
		}
		cur = lst = 1;
	}
	int bg[maxn], ne[maxn], to[maxn], e;
	inline void add(int x, int y)
	{
		e++;
		to[e] = y;
		ne[e] = bg[x];
		bg[x] = e;
	}
	int res[maxn], dfs_clock;
	void dfs(int x)
	{
		if (id[x] & 1) res[++dfs_clock] = id[x] >> 1;
		for (int i = bg[x]; i; i = ne[i]) dfs(to[i]);
	}
	vector <int> stk[sig];
	vector <int> getsa(char s[])
	{
		clear();
		int n = strlen(s + 1);
		vector <int> ans(n + 1, 0);
		DEP(i, n, 1) extend(trans(s[i]), i);
		REP(i, 1, cur) bg[i] = 0;e = 0;
		REP(i, 0, sig - 1) stk[i].clear();
		REP(i, 2, cur)
		{
			int c = trans(s[len[fail[i]] + (id[i] >> 1)]);
			stk[c].emplace_back(i);
		}
		DEP(i, sig - 1, 0) for (int x : stk[i]) add(fail[x], x);
		dfs_clock = 0;
		dfs(1);
		REP(i, 1, n) ans[i] = res[i];
		return ans;
	}
};

vector <int> getheight(char s[], vector <int> SA) // height[i] = LCP(SA[i], SA[i + 1]), h[i] = height[rk[i]], h[i] >= h[i - 1] - 1
{
	int n = strlen(s + 1), res = 0;
	static int rk[maxn];
	REP(i, 1, n) rk[SA[i]] = i;
	vector <int> height(n + 1, 0);
	REP(i, 1, n)
	{
		res = max(res - 1, 0);
		while (max(SA[rk[i]], SA[rk[i] + 1]) + res <= n && s[SA[rk[i]] + res] == s[SA[rk[i] + 1] + res]) res++;
		height[rk[i]] = res;
	}
	return height;
}

int main()
{
#ifdef CraZYali
	freopen("35-new.in", "r", stdin);
	freopen("35-new.out", "w", stdout);
#endif
	static char s[maxn];
	scanf("%s", s + 1);
	auto SA = SAM :: getsa(s), h = getheight(s, SA);
	int n = strlen(s + 1);
	REP(i, 1, n) printf("%d%c", SA[i], i == end_i ? '\n' : ' ');
	REP(i, 1, n - 1) printf("%d%c", h[i], i == end_i ? '\n' : ' ');
	return 0;
}
