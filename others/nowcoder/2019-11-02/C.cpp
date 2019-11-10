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

<<<<<<< HEAD
int n, m, a[maxn], ans;

#include <tr1/unordered_set>
tr1::unordered_set <int> G[maxn];

=======
int n, m, a[maxn];
vector <int> G[maxn];
>>>>>>> e902dac5501555f8dfead2ead9a2ab10b0801d44
int deg[maxn];
inline void add(int x, int y)
{
	deg[x]++;deg[y]++;
<<<<<<< HEAD
	G[x].insert(y);
	G[y].insert(x);
=======
	G[x].emplace_back(y);
	G[y].emplace_back(x);
>>>>>>> e902dac5501555f8dfead2ead9a2ab10b0801d44
}
inline bool cmp(int A, int B) {return deg[A] > deg[B];}
int id[maxn], times[maxn];

<<<<<<< HEAD
//vector <pair <int, int> > qaq[maxn];
=======
int ans;
int cnt[maxn], cir[maxn], id[maxn], rk[maxn];
>>>>>>> e902dac5501555f8dfead2ead9a2ab10b0801d44

int main()
{
#ifdef CraZYali
	file("C");
#endif
	cin >> n >> m;
	REP(i, 1, n) a[i] = read<int>();
	while (m--) add(read<int>(), read<int>());
	REP(i, 1, n) id[i] = i;
<<<<<<< HEAD
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
=======
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
>>>>>>> e902dac5501555f8dfead2ead9a2ab10b0801d44
	return 0;
}
