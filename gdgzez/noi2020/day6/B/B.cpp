#define REP(i, s, e) for (register int i = (s), end_##i = (e); i <= end_##i; i++)
#define DEP(i, s, e) for (register int i = (s), end_##i = (e); i >= end_##i; i--)
#define DEBUG fprintf(stderr, "Passing [%s] in Line %d\n", __FUNCTION__, __LINE__)

#define chkmax(a, b) (a < (b) ? a = (b) : a)
#define chkmin(a, b) (a > (b) ? a = (b) : a)

#include <algorithm>
#include <iostream>
#include <cassert>
#include <cstring>
#include <cstdlib>
#include <cstdio>
#include <vector>
#include <cmath>

using namespace std;
const int MOD = 1e9 + 7, maxn = 4050;
#define i64 long long

template <typename T> T read()
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

void file(string s)
{
	freopen((s + ".in").c_str(), "r", stdin);
	freopen((s + ".out").c_str(), "w", stdout);
}

int m, n, k;
char s[maxn];

long long ans[maxn], tot[maxn];
int fail[maxn], dep[maxn];

int main()
{
#ifdef CraZYali
	file("B");
#endif
	n = read<int>();
	scanf("%s", s + 1);
	REP(i, 1, n)
	{
		char *s = ::s + i - 1;
		dep[0] = -1;
		int k = 0;
		long long tot = 0;
		REP(j, 2, n - i + 1)
		{
			while (k && s[j] != s[k + 1]) k = fail[k];
			fail[j] = (k += (s[j] == s[k + 1]));
			dep[j] = dep[k] + 1;
			tot += dep[j];
			ans[i + j - 1] += tot;
		}
		/*
		REP(j, 1, i - 1) putchar(' ');puts(s + 1);
		REP(j, 1, n - i + 1) printf("%d%c", fail[j], j == end_j ? '\n' : ' ');
		REP(j, 1, n - i + 1) printf("%d%c", dep[j], j == end_j ? '\n' : ' ');
		puts("");
		*/
	}
	REP(i, 1, n)
	{
		(ans[i] += ans[i - 1]) %= MOD;
		cout << ans[i] << '\n';
	}
	return 0;
}
