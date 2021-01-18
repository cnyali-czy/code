/*
	Problem:	C.cpp
	Time:		2021-01-17 09:56
	Author:		CraZYali
	E-Mail:		yms-chenziyang@outlook.com 
*/

#define REP(i, s, e) for (register int i(s), end_##i(e); i <= end_##i; i++)
#define DEP(i, s, e) for (register int i(s), end_##i(e); i >= end_##i; i--)
#define DEBUG fprintf(stderr, "Passing [%s] in Line %d\n", __FUNCTION__, __LINE__)

#define chkmax(a, b) (a < (b) ? a = (b) : a)
#define chkmin(a, b) (a > (b) ? a = (b) : a)

#include <ctime>
#include <vector>
#include <cstring>
#include <set>
#include <algorithm>
#include <iostream>
#include <cstdio>

using namespace std;
const int maxn = 55;

vector <int> G[maxn];
void add(int x, int y)
{
	G[x].emplace_back(y);
	G[y].emplace_back(x);
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

int n, A[maxn << 1], u[maxn], v[maxn], ans;
int fa[maxn];
int find(int x) {return fa[x] == x ? fa[x] : fa[x] = find(fa[x]);}
void uni(int x, int y) {fa[find(x)] = find(y);}

int rt, allnode, siz[maxn], Max[maxn];
void findrt(int x, int fa = 0)
{
	siz[x] = 1;Max[x] = 0;
	for (int y : G[x]) if (y ^ fa)
	{
		findrt(y, x);
		siz[x] += siz[y];
		Max[x] = max(Max[x], siz[y]);
	}
	Max[x] = max(Max[x], allnode - siz[x]);
	if (Max[x] < Max[rt] || !rt) rt = x;
}
string dfs(int x, int fa = 0)
{
	string res = "(";
	vector <string> v;
	for (int y : G[x]) if (y ^ fa) v.emplace_back(dfs(y, x));
	sort(v.begin(), v.end());
	for (auto i : v) res += i;
	return res + ")";
}
pair <string, string> res[1 << 20];
int cnt[1 << 20];
bool ok[1 << 20];

int main()
{
#ifdef CraZYali
	file("C");
#endif
	while (scanf("%d", A + 1 + n) != EOF) n++;
	n = n / 2 + 1;
	REP(i, 1, n - 1) u[i] = A[i] + 1;
	REP(i, n, n * 2 - 2) v[i - n + 1] = A[i] + 1;

	int ans = 0;
	REP(S, 1, (1 << n) - 1)
	{
		cnt[S] = cnt[S >> 1] + (S & 1);
		if (cnt[S] > n / 2) continue;
		static int stk[maxn];int top = 0;
		int rt1 = rt, rt2 = rt;
		REP(i, 1, n) fa[i] = i, G[i].clear();
		REP(i, 1, n - 1)
			if ((S >> (u[i] - 1) & 1) && (S >> (v[i] - 1) & 1)) add(u[i], v[i]), uni(u[i], v[i]);
		REP(i, 1, n) if (S >> (i - 1) & 1) stk[++top] = i;
		REP(i, 2, top) if (find(stk[1]) != find(stk[i])) goto gg;
		ok[S] = 1;
		rt = 0;allnode = cnt[S];
		findrt(stk[1]);
		REP(i, 1, top) if (Max[stk[i]] == Max[rt] && stk[i] != rt) rt2 = stk[i];
		res[S] = make_pair(dfs(rt1), dfs(rt2));
		if (res[S].first > res[S].second) swap(res[S].first, res[S].second);
gg:;
	}
	const int ALL = (1 << n) - 1;
	REP(x, 1, ALL) if (cnt[x] <= n / 2 && cnt[x] > ans && ok[x])
	{
		for (int tS = ALL ^ x, y = tS; y; y = (y - 1) & tS)
			if (cnt[x] == cnt[y] && ok[y] && res[x] == res[y])
			{
				ans = max(ans, cnt[x]);
				if (ans == n / 2) break;
				goto gg2;
			}
gg2:;
	}
	cout << ans << endl;
	return 0;
}
