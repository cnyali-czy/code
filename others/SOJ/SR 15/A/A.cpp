/*
	Problem:	A.cpp
	Time:		2021-02-18 16:14
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
		ans = ans * 10 + (c - 48);
		c = getchar();
	}
	return ans * flag;
}

#define file(FILE_NAME) freopen(FILE_NAME".in", "r", stdin), freopen(FILE_NAME".out", "w", stdout)

int n, k, l[maxn];

const int LIM = 8;
int a[maxn], fail[maxn], x;

string mem[maxn][1 << LIM];

void calc(int n)
{
	int sta = 0;
	for (int x = fail[n]; x; x = fail[x]) sta |= (1 << x - 1);
	string res = "";
	REP(i, 1, n) res += a[i];
	if (!mem[n][sta].size() || res < mem[n][sta]) mem[n][sta] = res;
}
void dfs(int x = 0, int cur = 'a')
{
	if (x) calc(x);
	if (x >= LIM) return;
	x++;
	REP(i, 'a', min((int)'z', cur + 1))
	{
		a[x] = i;
		if (x > 1)
		{
			int k = fail[x - 1];
			while (k && a[k + 1] != i) k = fail[k];
			if (a[k + 1] == i) k++;
			fail[x] = k;
		}
		dfs(x, max(i, cur));
	}
}

int main()
{
#ifdef CraZYali
	file("A");
#endif
	dfs();
	register int T = read<int>();
	while (T--)
	{
		n = read<int>();k = read<int>();
		static int l[maxn];
		REP(i, 1, k) l[i] = read<int>();
		if (!k)
		{
			REP(i, 1, n - 1) putchar('a');
			puts("b");
			continue;
		}
		if (k == n - 1)
		{
			REP(i, 1, n) putchar('a');
			puts("");
			continue;
		}
		if (n > LIM) {puts("GG");continue;}
		int sta = 0;
		REP(i, 1, k) sta |= (1 << l[i] - 1);
		string res = mem[n][sta];
		if (res.size())
		{
			cout << res << '\n';
			continue;
		}

		int ard = 1e9;
		for (int U = (1 << n - 1) - 1, V = U ^ sta, x = V; ; x = (x - 1) & V)
		{
			if (mem[n][sta | x].size() && ard >= __builtin_popcount(x) && (!res.size() || res > mem[n][sta | x])) res = mem[n][sta | x], ard = __builtin_popcount(x);
			if (!x) break;
		}
		cout << res << '\n';
	}
	return 0;
}
