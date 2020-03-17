/*
	Problem:	C.cpp
	Time:		2020-03-12 20:38
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
#include <algorithm>
#define i64 long long
using namespace std;
const int maxn = 5e5 + 10;
const i64 inf = 1e18;
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

namespace run
{
	int n, m, L;
	i64 a[maxn], b[maxn], f[maxn], fg[maxn], s[maxn], g[maxn], ans[maxn], cut[maxn];

	int main()
	{
		n = read<int>();
		REP(i, 1, n) a[i] = read<i64>(); 
		sort(a + 1, a + 1 + n, greater <i64> () );
		int j = 1;
		REP(i, 1, n)
		{
			while (j <= n && a[j] == a[i]) j++;
			a[++m] = a[i++];
			while (i < j) b[++L] = a[i++];
			i--;
		}
		DEP(i, m, 1) fg[i] = __gcd(fg[i + 1], a[i]);
		REP(i, 1, m) s[i] = s[i - 1] + a[i];
		REP(i, 1, L) g[i] = g[i - 1] + b[i];
		int lst = 1;
		REP(i, 1, m) if (fg[i + 1] ^ fg[i + 2] || i == m)
		{
			cut[0] = -inf;
			REP(l, 1, i) cut[l] = max(cut[l - 1], __gcd(a[l], fg[i + 1]) - a[l] - fg[i + 1]);
			REP(l, lst, i) f[l] = fg[i + 1] + s[l] + cut[l];
			int l = lst, r = 0;
			while (l <= i && r <= L)
			{
				chkmax(ans[l + r], f[l] + g[r]);
				if ((l ^ i && (f[l + 1] + g[r] > f[l] + g[r + 1])) || r == L) l++;
				else r++;
			}
			lst = i + 1;
		}
		REP(i, 1, n) cout << chkmax(ans[i], ans[i - 1]) << '\n';
		return 0;
	} 
}
int main()
{
#ifdef CraZYali
	file("C");
#endif
	return run::main();
}
