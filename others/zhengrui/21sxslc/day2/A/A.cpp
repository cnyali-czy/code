/*
	Problem:	A.cpp
	Time:		2021-01-10 08:22
	Author:		CraZYali
	E-Mail:		yms-chenziyang@outlook.com 
*/

#define REP(i, s, e) for (register int i(s), end_##i(e); i <= end_##i; i++)
#define DEP(i, s, e) for (register int i(s), end_##i(e); i >= end_##i; i--)
#define DEBUG fprintf(stderr, "Passing [%s] in Line %d\n", __FUNCTION__, __LINE__)

#define chkmax(a, b) (a < (b) ? a = (b) : a)
#define chkmin(a, b) (a > (b) ? a = (b) : a)

#include <ctime>
#include <unordered_map>
#include <algorithm>
#include <vector>
#include <iostream>
#include <cstdio>

using namespace std;
const int maxn = 5e5 + 10;

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

int n, a[maxn], ls[maxn], rs[maxn], L[maxn], R[maxn], rt;
vector <int> P[maxn], N[maxn];

void dfs0(int x)
{
	L[x] = R[x] = x;
	if (ls[x]) dfs0(ls[x]), L[x] = L[ls[x]];
	if (rs[x]) dfs0(rs[x]), R[x] = R[rs[x]];
}

void build()
{
	static int stk[maxn], ntop, top;
	REP(i, 1, n)
	{
		int ntop = top;
		while (ntop && a[stk[ntop]] < a[i]) ntop--;
		if (ntop) rs[stk[ntop]] = i;
		if (ntop < top) ls[i] = stk[ntop + 1];
		stk[top = (++ntop)] = i;
	}
	static bool notroot[maxn];
	REP(i, 1, n) notroot[ls[i]] = notroot[rs[i]] = 1;
	REP(i, 1, n) if (!notroot[i]) {rt = i;break;}
	dfs0(rt);
}

void cdq(int x)
{
	if (ls[x]) cdq(ls[x]);
	if (rs[x]) cdq(rs[x]);
	int l = L[x], r = R[x];
	if (l == x || r == x) return;
	if (x - l < r - x)
		REP(i, l, x - 1)
		{
			int need = a[x] - a[i];
			N[x].emplace_back(need);
			P[r].emplace_back(need);
		}
	else
		REP(i, x + 1, r)
		{
			int need = a[x] - a[i];
			N[l - 1].emplace_back(need);
			P[x - 1].emplace_back(need);
		}
}

unordered_map <int, int> cnt;
int main()
{
#ifdef CraZYali
	file("A");
#endif
	n = read<int>();
	REP(i, 1, n) a[i] = read<int>();
	build();
	cdq(rt);
	long long ans = 0;
	REP(i, 1, n)
	{
		cnt[a[i]]++;
		for (auto j : N[i]) if (cnt.find(j) != cnt.end()) ans -= cnt[j];
		for (auto j : P[i]) if (cnt.find(j) != cnt.end()) ans += cnt[j];
	}
	cout << ans << endl;
	return 0;
}
