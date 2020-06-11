/*
	Problem:	C.cpp
	Time:		2020-06-11 23:26
	Author:		CraZYali
	E-Mail:		yms-chenziyang@outlook.com 
*/

#define REP(i, s, e) for (register int i(s), end_##i(e); i <= end_##i; i++)
#define DEP(i, s, e) for (register int i(s), end_##i(e); i >= end_##i; i--)
#define DEBUG fprintf(stderr, "Passing [%s] in Line %d\n", __FUNCTION__, __LINE__)

#define chkmax(a, b) (a < (b) ? a = (b) : a)
#define chkmin(a, b) (a > (b) ? a = (b) : a)

#include <set>
#include <vector>
#include <iostream>
#include <cstdio>

using namespace std;
const int maxn = 17, N = 2e5 + 5;

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

int n, k, bit[N], match[N];
vector <int> a[20];
vector <vector <int> > ans;

void print(int x)
{
	REP(i, 0, n - 1) if (x >> i & 1) putchar('a' + i);
}

int main()
{
#ifdef CraZYali
	file("C");
#endif
	n = read<int>();k = read<int>();
	REP(i, 1, (1 << n) - 1)
	{
		bit[i] = bit[i >> 1] + (i & 1);
		a[bit[i]].emplace_back(i);
	}
	for (int i = 0; i <= k - i; i++)
	{
		set <int> S;
		for (auto j : a[i]) S.emplace(j);
		int j = 0;
		while (!S.empty())
		{
			if (i == k - i && S.size() == 1) break;
			int u = *S.rbegin();
			do
			{
				if (j == a[k - i].size()) j = 0;
				int v = a[k - i][j];
				if (!(u & v))
				{
					if (match[v])
					{
						match[match[v]] = 0;
						S.emplace(match[v]);
					}
					else S.erase(v);
					match[v] = u;
					match[u] = v;
					S.erase(u);
					j++;
					break;
				}
				j++;
			}while (1);
		}
	}
	REP(i, 1, (1 << n) - 1) if (bit[i] <= k)
		if (match[i])
		{
			if (i < match[i])
			{
				vector <int> tmp(1, match[i]);
				tmp.emplace_back(i);
				ans.emplace_back(tmp);
			}
		}
		else ans.emplace_back(vector <int> (1, i));
	cout << ans.size() << endl;
	for (auto i : ans)
	{
		printf("%d", i.size());
		for (auto j : i) putchar(' '), print(j);
		puts("");
	}
	return 0;
}
