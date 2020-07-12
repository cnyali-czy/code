/*
	Problem:	A.cpp
	Time:		2020-07-11 19:12
	Author:		CraZYali
	E-Mail:		yms-chenziyang@outlook.com 
*/

#define REP(i, s, e) for (register int i(s), end_##i(e); i <= end_##i; i++)
#define DEP(i, s, e) for (register int i(s), end_##i(e); i >= end_##i; i--)
#define DEBUG fprintf(stderr, "Passing [%s] in Line %d\n", __FUNCTION__, __LINE__)

#define chkmax(a, b) (a < (b) ? a = (b) : a)
#define chkmin(a, b) (a > (b) ? a = (b) : a)

#include <cassert>
#include <algorithm>
#include <vector>
#include <cmath>
#include <iostream>
#include <cstdio>

using namespace std;
const int maxn = 1e5 + 10;

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

int n, m, q, ans;
int a[maxn], show[maxn], cnt[maxn];

vector <int> pos[maxn], big;
vector <pair <int, int> > G[maxn];
bool opt[maxn], isbig[maxn];
int tot[maxn];

void bf(int x, int delta)
{
	int me = 0;
	for (auto i : pos[x])
	{
		if (a[i - 1] ^ x)
		{
			cnt[a[i - 1]] += delta;
			if (opt[a[i - 1]]) me++;
		}
		if (a[i + 1] ^ x)
		{
			cnt[a[i + 1]] += delta;
			if (opt[a[i + 1]]) me++;
		}
	}
//	printf("bf %d %d %d\n", x, delta, me);
	ans += (tot[x] - me) * delta;
}
void miao(int x, int delta)
{
	if (delta == -1)
		ans -= tot[x] - cnt[x];
	for (auto i : G[x])
	{
		int y = i.first, z = i.second;
		if (opt[y])
		{
			cnt[x] += z * delta;
			cnt[y] += z * delta;
		}
	}
	if (delta == 1)
		ans += tot[x] - cnt[x];
}

int main()
{
#ifdef CraZYali
	file("A");
#endif
	n = read<int>();m = read<int>();q = read<int>();
	REP(i, 1, n)
	{
		show[a[i] = read<int>()]++;
		pos[a[i]].emplace_back(i);
	}
	REP(i, 1, m)
		for (auto j : pos[i]) if (a[j] ^ a[j - 1]) tot[i]++;
	const int block = sqrt(n);
	REP(i, 1, m) if (show[i] > block) big.emplace_back(i);
	for (auto i : big)
	{
		for (auto j : pos[i])
		{
			cnt[a[j - 1]]++;
			cnt[a[j + 1]]++;
		}
		for (auto j : big) if (j ^ i)
			G[i].emplace_back(j, cnt[j]);
		for (auto j : pos[i]) cnt[a[j - 1]] = cnt[a[j + 1]] = 0;
	}
	for (auto i : big)
	{
		sort(G[i].begin(), G[i].end());
		G[i].resize(unique(G[i].begin(), G[i].end()) - G[i].begin());
	}
	while (q--)
	{
		int x = read<int>();
		opt[x] ^= 1;
		int delta = opt[x] ? 1 : -1;
		if (show[x] <= block) bf(x, delta);
		else miao(x, delta);
//		REP(i, 1, m) printf("%d%c", cnt[i], i == end_i ? '\n' : ' ');
		printf("%d\n", ans);
	}
	return 0;
}
