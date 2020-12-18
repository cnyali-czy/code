/*
	Problem:	7115.cpp
	Time:		2020-12-18 08:37
	Author:		CraZYali
	E-Mail:		yms-chenziyang@outlook.com 
*/

#define REP(i, s, e) for (register int i(s), end_##i(e); i <= end_##i; i++)
#define DEP(i, s, e) for (register int i(s), end_##i(e); i >= end_##i; i--)
#define DEBUG fprintf(stderr, "Passing [%s] in Line %d\n", __FUNCTION__, __LINE__)

#define chkmax(a, b) (a < (b) ? a = (b) : a)
#define chkmin(a, b) (a > (b) ? a = (b) : a)

#include <algorithm>
#include <cassert>
#include <vector>
#include <iostream>
#include <cstdio>

using namespace std;
const int maxn = 50 + 5, maxm = 400 + 5;

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
		ans = ans * 10 + (c - 48);
		c = getchar();
	}
	return ans * flag;
}

#define file(FILE_NAME) freopen(FILE_NAME".in", "r", stdin), freopen(FILE_NAME".out", "w", stdout)

int n, m;
vector <int> a[maxn];
bool del[maxn];

const int maxN = 1e7;
int u[maxN], v[maxN], N;
void move(int x, int y)
{
	assert(1 <= x && x <= n + 1);
	assert(1 <= y && y <= n + 1);
	assert(x != y);
	assert(a[x].size());
	assert(a[y].size() < m);
	++N;
	u[N] = x;v[N] = y;
	a[y].emplace_back(a[x].back());
	a[x].pop_back();
}

void goup(int x, int y)
{
	int c = 0, sa = a[x].size();
	if (!sa) return;
	assert(sa == m);
	for (auto i : a[x]) if (i == y) c++;
	if (!c) return;
	int null = 0, full = 0;
	REP(i, 1, n + 1) if (i != x && !del[i])
		if (!a[i].size()) null = i;
		else if (a[i].size() == m) full = i;
	REP(i, 1, c) move(full, null);
	int ard = 0, inf = 0, inn = 0;
	while (a[x].size())
	{
		int t = a[x].back();
		if (t == y)
		{
			inf++;
			move(x, full);
			ard++;
			if (ard == c) break;
		}
		else
		{
			inn++;
			move(x, null);
		}
	}
	REP(i, 1, inn) move(null, x);
	REP(i, 1, inf) move(full, x);
	REP(i, 1, c) move(null, full);
}

int main()
{
#ifdef CraZYali
	file("7115");
#endif
	n = read<int>();m = read<int>();
	REP(i, 1, n) REP(j, 1, m) a[i].emplace_back(read<int>());
	static int id[maxn];
	REP(i, 1, n) id[i] = i;
	random_shuffle(id + 1, id + 1 + n);
	REP(I, 1, n - 1)
	{
		int i = id[I];
		REP(j, 1, n + 1) if (!del[j])
			goup(j, i);
		int null = 1;
		REP(j, 1, n + 1) if (!a[j].size()) {null = j;break;}
		REP(j, 1, n + 1) if (j ^ null)
			while (a[j].size() && a[j].back() == i) move(j, null);
		REP(j, 1, n + 1) if (!del[j] && j ^ null)
		{
			REP(k, 1, n + 1) if (!del[k] && j != k)
				while (a[j].size() && a[k].size() < m) move(j, k);
			break;
		}
		del[null] = 1;
	}
	printf("%d\n", N);
	REP(i, 1, N) printf("%d %d\n", u[i], v[i]);
	return 0;
}
