/*
	Problem:	C.cpp
	Time:		2021-01-25 14:38
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
#define i64 long long

using namespace std;
const int maxn = 6e5 + 10, MOD = 998244353;

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

int n, m, a[maxn], pre[maxn], nxt[maxn], mem[maxn];
int bin[maxn], sum[maxn], c[maxn], num[maxn];

bool gg(int l, int r)
{
	return (nxt[l] > r || a[l + r - nxt[l]] == a[r]) && (pre[r] < l || a[l + r - pre[r]] == a[l]);
}

int main()
{
#ifdef CraZYali
	file("C");
#endif
	n = read<int>();m = read<int>();
	bin[0] = 1;REP(i, 1, m + 5) bin[i] = 1ll * m * bin[i - 1] % MOD;
	for (int i = 1; i <= n; i += 2, n++) a[i] = read<int>();
	REP(i, 1, n) pre[i] = mem[a[i]], mem[a[i]] = i;
	REP(i, 0, m) mem[i] = n + 1;
	DEP(i, n, 1) nxt[i] = mem[a[i]], mem[a[i]] = i;

	i64 mid = 0, r = 0, res = 0, len = 0, tot = 0, ans = 0;
	REP(i, 1, n)
	{
		if (i <= r)
		{
			int _ = mid * 2 - i;
			res = sum[_];
			len = c[_];
			tot = num[_];
			while (len > r - i + 1)
			{
				if (a[_ - len + 1])
				{
					(res -= bin[m - tot]) %= MOD;
					if (nxt[_ - len + 1] >  _ + len - 1) tot--;
					if (pre[_ + len - 1] <= _ - len + 1) tot--;
				}
				len--;
			}
		}
		else
		{
			len = 1;
			res = (tot = (i & 1)) ? bin[m - 1] : 0;
		}
		while (len < min(i, n - i + 1) && gg(i - len, i + len))
		{
			len++;
			if (a[i - len + 1])
			{
				if (pre[i + len - 1] <  i - len + 1) tot++;
				if (nxt[i - len + 1] >= i + len - 1) tot++;
				(res += bin[m - tot]) %= MOD;
			}
		}
		sum[i] = res;
		num[i] = tot;
		c[i] = len;
		if (i + len - 1 >= r) mid = i, r = i + len - 1;
		(ans += res) %= MOD;
	}
	cout << (ans % MOD + MOD) % MOD << endl;
	return 0;
}
