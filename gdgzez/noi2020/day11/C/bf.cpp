/*
	Problem:	C.cpp
	Time:		2020-06-11 10:43
	Author:		CraZYali
	E-Mail:		yms-chenziyang@outlook.com 
*/

#define REP(i, s, e) for (register int i(s), end_##i(e); i <= end_##i; i++)
#define DEP(i, s, e) for (register int i(s), end_##i(e); i >= end_##i; i--)
#define DEBUG fprintf(stderr, "Passing [%s] in Line %d\n", __FUNCTION__, __LINE__)

#define chkmax(a, b) (a < (b) ? a = (b) : a)
#define chkmin(a, b) (a > (b) ? a = (b) : a)

#include <unordered_set>
#include <algorithm>
#include <iostream>
#include <cstring>
#include <cstdio>

using namespace std;
const int maxn = 1000 + 10;

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

int n;
char s[maxn];
#define ui64 unsigned long long
const ui64 base = 1e9 + 7;
ui64 bin[maxn];
struct __init__
{
	__init__(const int N = maxn - 10)
	{
		bin[0] = 1;
		REP(i, 1, N) bin[i] = bin[i - 1] * base;
	}
}__INIT__;
struct Table
{
	ui64 H[maxn];
	void init(char src[])
	{
		H[0] = 0;
		REP(i, 1, n) H[i] = H[i - 1] * base + src[i];
	}
	ui64 query(int l, int r)
	{
		return H[r] - H[l - 1] * bin[r - l + 1];
	}
}h, hr;
unordered_set <ui64> S[maxn];

int good[maxn][maxn];

int main()
{
#ifdef CraZYali
	file("C");
#endif
	n = read<int>();
	scanf("%s", s + 1);
	h.init(s);
	reverse(s + 1, s + 1 + n);
	hr.init(s);
	reverse(s + 1, s + 1 + n);
	REP(i, 1, n) REP(j, i, n)
		if (h.query(i, j) == hr.query(n - j + 1, n - i + 1)) good[i][j] = 1;
	REP(i, 1, n) DEP(j, n, 1) good[i][j] += good[i][j + 1];
	long long ans = 0;
	REP(i, 1, n)
	{
	}
//			REP(k, i, j) S[j].emplace(h.query(i, k));
	REP(i, 1, n)
	{
		if (S[i].size() < S[i - 1].size()) S[i].swap(S[i - 1]);
		for (auto j : S[i - 1]) S[i].emplace(j);
		printf("%d\n", S[i].size());
	}
	return 0;
}
