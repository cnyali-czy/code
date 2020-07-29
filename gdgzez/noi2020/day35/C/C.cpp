/*
	Problem:	B.cpp
	Time:		2020-07-29 09:10
	Author:		CraZYali
	E-Mail:		yms-chenziyang@outlook.com 
*/

#define REP(i, s, e) for (register int i(s), end_##i(e); i <= end_##i; i++)
#define DEP(i, s, e) for (register int i(s), end_##i(e); i >= end_##i; i--)
#define DEBUG fprintf(stderr, "Passing [%s] in Line %d\n", __FUNCTION__, __LINE__)

#define chkmax(a, b) (a < (b) ? a = (b) : a)
#define chkmin(a, b) (a > (b) ? a = (b) : a)

#include <iostream>
#include <cstdio>
#include <vector>

using namespace std;
const int maxn = 2e5 + 10;

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

int n, m, a[maxn];
vector <int> v[maxn];

void merge(int x, int y)
{
	if (v[x].size() < v[y].size()) swap(v[x], v[y]);
	v[x].insert(v[x].end(), v[y].begin(), v[y].end());
	v[y].clear();
}

int st[maxn], top, cnt[maxn], ccnt[maxn];
long long sc[maxn];

int main()
{
#ifdef CraZYali
	file("C");
#endif
	n = read<int>();m = read<int>();
	REP(i, 1, n) a[i] = read<int>();
	REP(i, 1, n) v[i].emplace_back(i);
	while (m--)
	{
		int opt = read<int>();
		if (opt == 1)
		{
			int x = read<int>(), y = read<int>();
			merge(x, y);
		}
		else
		{
			int x = read<int>(), l = read<int>(), r = read<int>(), k = read<int>();
			top = 0;
			for (auto i : v[x]) if (l <= i && i <= r)
			{
				st[++top] = i;
				cnt[a[i]]++;
			}
			REP(i, 1, top) ccnt[cnt[a[st[i]]]]++;
			REP(i, 1, k) sc[i] = sc[i - 1] + ccnt[i];
			long long res = 0;
			REP(i, 1, min(k, top)) if (ccnt[i])
				res += ccnt[i] * sc[k - i];
			printf("%lld\n", res);
			REP(i, 1, top) ccnt[cnt[a[st[i]]]] = 0;
			REP(i, 1, top) cnt[a[st[i]]] = 0;
		}
	}
	return 0;
}
