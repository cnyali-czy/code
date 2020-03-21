/*
	Problem:	D.cpp
	Time:		2020-03-19 22:59
	Author:		CraZYali
	E-Mail:		yms-chenziyang@outlook.com 
*/

#define REP(i, s, e) for (register int i(s), end_##i(e); i <= end_##i; i++)
#define DEP(i, s, e) for (register int i(s), end_##i(e); i >= end_##i; i--)
#define DEBUG fprintf(stderr, "Passing [%s] in Line %d\n", __FUNCTION__, __LINE__)

#define chkmax(a, b) (a < (b) ? a = (b) : a)
#define chkmin(a, b) (a > (b) ? a = (b) : a)

#include <cassert>
#include <cstring>
#include <iostream>
#include <cstdio>

using namespace std;
const int maxn = 1000000 + 10 << 1;

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

int n, d[maxn];
char s[maxn], t[maxn];
inline int Min(int x, int y) {return x < y ? x : y;}

void manacher(char t[], int n)
{
	if (n <= 0) return;
	s[1] = '#';
	REP(i, 1, n) s[i * 2] = t[i], s[i * 2 + 1] = '#';
	n = n * 2 + 1;
	for (int i = 1, l = 1, r = 0; i <= n; i++)
	{
		int &k = d[i];
		k = (l > r ? 1 : min(r - i, d[l + r - i]));
		while (1 <= i - k && i + k <= n && s[i - k] == s[i + k]) k++;
		k--;
		if (i + k > r)
		{
			l = i - k;
			r = i + k;
		}
	}
	int ans = -1, p = 0;
	REP(i, 1, n) if (d[i] > ans && (i - d[i] <= 1 || i + d[i] >= n)) ans = d[i], p = i;
	REP(j, p - ans, p + ans) if (1 <= j && j <= n && s[j] != '#') putchar(s[j]);
}

int main()
{
#ifdef CraZYali
	file("D");
#endif
	register int T = read<int>();
	while (T--)
	{
		scanf("%s", t + 1);
		int n = strlen(t + 1);
		int l = 1, r = n, ccc = 0;
		while (l < r && t[l] == t[r])
		{
			ccc++;
			l++;r--;
		}
		REP(i, 1, ccc) putchar(t[i]);
		manacher(t + ccc, n - ccc - ccc);
		REP(i, n - ccc + 1, n) putchar(t[i]);
		puts("");
	}
	return 0;
}
