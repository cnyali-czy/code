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

int n, m, a[maxn], ans;

#include <tr1/unordered_set>
tr1::unordered_set <int> G[maxn];

int deg[maxn];
inline void add(int x, int y)
{
	deg[x]++;deg[y]++;
	G[x].insert(y);
	G[y].insert(x);
}
inline bool cmp(int A, int B) {return deg[A] > deg[B];}
int id[maxn], times[maxn];

//vector <pair <int, int> > qaq[maxn];

int main()
{
#ifdef CraZYali
	file("C");
#endif
	cin >> n >> m;
	REP(i, 1, n) a[i] = read<int>();
	while (m--) add(read<int>(), read<int>());
	REP(i, 1, n) id[i] = i;
	sort(id + 1, id + 1 + n, cmp);
	const int inv2 = (MOD + 1) / 2;
	REP(I, 1, n)
	{
		int u = id[I];
		for (auto v : G[u])
		{
			(times[v] += 1ll * (deg[u] - 1) * (deg[u] - 2) % MOD * inv2 % MOD) %= MOD;
			cerr << v << ' ' << (-1 + deg[u]) * (deg[u] - 2) / 2<< endl;
	//		G[v].erase(u);
	//		deg[v]--;
		}
	}
//	REP(i, 1, n)
//		for (auto j : qaq[i]) (ans += 1ll * j.second * (j.second - 1) % MOD * a[i] % MOD) %= MOD, cout << i << ' ' << j.first << ' '<< j.second << endl;
	REP(i, 1, n)
		(ans += 1ll * a[i] * times[i] % MOD) %= MOD;
	cout << (MOD + ans) % MOD << endl;
	return 0;
}
