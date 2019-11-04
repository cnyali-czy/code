/*
 * File Name:	C.cpp
 * Author	:	CraZYali
 * Year		:	2019.11.02 20:23
 * Email	:	yms-chenziyang@outlook.com
 */

#define DREP(i, s, e) for (register int i(s), end_##i(e); i >= end_##i; i--)
#define  REP(i, s, e) for (register int i(s), end_##i(e); i <= end_##i; i++)
#define DEBUG fprintf(stderr, "Passing [%s] in Line %d\n", __FUNCTION__, __LINE__)

#define chkmax(a, b) (a < (b) ? a = (b) : a) 
#define chkmin(a, b) (a > (b) ? a = (b) : a) 

#include <algorithm>
#include <iostream>
#include <cstdio>
#include <vector>

using namespace std;
const int maxn = 1e5 + 10, MOD = 1e9 + 7;

template <typename T> inline T read()
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

#define file(FILE_NAME) freopen(FILE_NAME".in", "r", stdin), freopen(FILE_NAME".out", "w", stdout);

int n, m, a[maxn];
vector <int> G[maxn];
int deg[maxn];
inline void add(int x, int y)
{
	deg[x]++;deg[y]++;
	G[x].emplace_back(y);
	G[y].emplace_back(x);
}

int ans;
int cnt[maxn], cir[maxn], id[maxn], rk[maxn];

int main()
{
#ifdef CraZYali
	file("C");
#endif
	cin >> n >> m;
	REP(i, 1, n) a[i] = read<int>();
	while (m--) add(read<int>(), read<int>());
	REP(i, 1, n) id[i] = i;
	sort(id + 1, id + 1 + n, [&](int x, int y) {return deg[x] > deg[y];});
	REP(i, 1, n) rk[id[i]] = i;
	REP(u, 1, n)
	{
		for (int v : G[u]) if (rk[v] < rk[u])
			for (int w : G[v]) if (rk[w] < rk[u])
			{
				int &tmp = cnt[w];
				cir[u] += tmp;
				cir[v] += tmp;
				cir[w] += tmp;
				tmp++;
			}
		for (int v : G[u]) if (rk[v] < rk[u])
			for (int w : G[v]) if (rk[w] < rk[u])
				cir[v] += --cnt[w];
	}
	REP(i, 1, n) (ans += 1ll * cir[i] * a[i] % MOD) %= MOD;
	cout << (MOD + 1ll * ans % MOD) % MOD << endl;
	return 0;
}
