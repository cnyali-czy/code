/*
	Problem:	A.cpp
	Time:		2021-06-27 08:24
	Author:		CraZYali
	E-Mail:		yms-chenziyang@outlook.com 
*/

#define REP(i, s, e) for (register int i(s), end_##i(e); i <= end_##i; i++)
#define DEP(i, s, e) for (register int i(s), end_##i(e); i >= end_##i; i--)
#define DEBUG fprintf(sDerr, "Passing [%s] in Line %d\n", __FUNCTION__, __LINE__)

#define chkmax(a, b) (a < (b) ? a = (b) : a)
#define chkmin(a, b) (a > (b) ? a = (b) : a)

#include <vector>
#include <algorithm>
#include <unordered_map>
#include <iostream>
#include <cstdio>
#include <ctime>
#include <bits/extc++.h>
#define i64 long long
#define fi first
#define se second

using namespace std;
const int maxn = 1e6 + 10, maxm = 1e6 + 10, K = 1e6;

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

int n, m, q;
vector <pair <int, int> > ed;
#define TB __gnu_pbds :: gp_hash_table <int, int>
//unordered_map <int, int> 
TB c[maxn], D;
int d[maxn];
i64 s[maxn];

int main()
{
#ifdef CraZYali
	file("A");
#endif
	n = read<int>();m = read<int>();
	while (m--)
	{
		int x = read<int>(), y = read<int>();
		if (x > y) swap(x, y);
		c[x][y]++;//c[y][x]++;
		d[x]++;if (x != y) {d[y]++;ed.emplace_back(x, y);}
	}
	sort(ed.begin(), ed.end());ed.resize(unique(ed.begin(), ed.end()) - ed.begin());
	REP(i, 1, n) D[d[i]]++;
	for (auto i : D) for (auto j : D) if (i.fi + j.fi <= K) s[i.fi + j.fi] += 1ll * i.se * j.se;
	cerr << clock() * 1. / CLOCKS_PER_SEC << endl;
	REP(i, 1, n) if (d[i] + d[i] <= K) s[d[i] + d[i]]--;
	for (auto E : ed)
	{
		int x = E.fi, y = E.se, t;
		if ((t = d[x] + d[y]) <= K) s[t] -= 2;
		if ((t = d[x] + d[y] - c[x][y]) <= K) s[t] += 2;
	}
	REP(i, 0, K) s[i] /= 2;
	REP(i, 1, K) s[i] += s[i - 1];

	q = read<int>();
	while (q--)
	{
		int k = read<int>();
		i64 ans = n * (n - 1ll) / 2 - s[k];
		printf("%lld\n", ans);		
	}
	
	cerr << clock() * 1. / CLOCKS_PER_SEC << endl;
	return 0;
}
