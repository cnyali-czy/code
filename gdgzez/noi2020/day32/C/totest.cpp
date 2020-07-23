/*
	Problem:	C.cpp
	Time:		2020-07-23 08:49
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
#define int long long
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

int n, k, s[maxn], Min[maxn], Max[maxn];

bool judge()
{
	if (n == 1 && k == 1) return 1;
	if (s[n] > s[1]) return 0;
	int l, r;l = r = k;
	while (1)
	{
		bool flag = 0;
		int x, bst;

		x = bst = l;
		while (1 < x && s[x - 1] >= s[r])
		{
			x--;
			if (s[x] >= s[bst]) {bst = x, flag = 1;break;}
		}
		l = bst;

		x = bst = r;
		while (x < n && s[x + 1] <= s[l])
		{
			x++;
			if (s[x] <= s[bst]) {bst = x, flag = 1;break;}
		}
		r = bst;
		if (!flag) break;
	}
	if (l == 1 & r == n) return 1;
	if (l == 1 && s[l] < s[r + 1]) return 0;
	if (r == n && s[l - 1] < s[r]) return 0;
	
	int L = l, R = r;
	l = 1, r = n;
	while (1)
	{
		int sl = l, sr = r;
		int x, bst;

		x = bst = l;
		while (x < L && s[x + 1] >= s[r])
		{
			x++;
			if (s[x] >= s[l]) {bst = x;break;}
		}
		l = bst;

		x = bst = r;
		while (R < x && s[l] >= s[x - 1])
		{
			x--;
			if (s[x] <= s[r]) {bst = x;break;}
		}
		r = bst;

		if (l == sl && r == sr) break;
	}
	return l == L && R == r;
}

signed main()
{
#ifdef CraZYali
	freopen("C.in", "r", stdin);
	freopen("totest.out", "w", stdout);
#endif
	register int T = read<int>();
	while (T--)
	{
		n = read<int>();k = read<int>();
		REP(i, 1, n) s[i] = s[i - 1] + read<int>();
		Min[1] = s[1];REP(i, 2, n) Min[i] = min(Min[i - 1], s[i]);
		Max[n] = s[n];DEP(i, n - 1, 1) Max[i] = max(Max[i + 1], s[i]);
		puts(judge() ? "Yes" : "No");
	}
	return 0;
}
