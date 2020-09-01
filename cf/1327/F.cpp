/*
	Problem:	F.cpp
	Time:		2020-09-01 20:51
	Author:		CraZYali
	E-Mail:		yms-chenziyang@outlook.com 
*/

#define REP(i, s, e) for (register int i(s), end_##i(e); i <= end_##i; i++)
#define DEP(i, s, e) for (register int i(s), end_##i(e); i >= end_##i; i--)
#define DEBUG fprintf(stderr, "Passing [%s] in Line %d\n", __FUNCTION__, __LINE__)

inline void chkmax(int &x, int y) {if (x < y) x = y;}
inline void chkmin(int &x, int y) {if (x > y) x = y;}

#include <iostream>
#include <cstdio>
#define i64 long long

using namespace std;
const int maxn = 5e5 + 10, maxm = 5e5 + 10, MOD = 998244353;

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

int n, k, m;
int l[maxm], r[maxm], x[maxm];

int f[maxn], pos[maxn], s[maxn];

int main()
{
#ifdef CraZYali
	file("F");
#endif
	n = read<int>();
	k = read<int>();
	m = read<int>();
	REP(i, 1, m) l[i] = read<int>(), r[i] = read<int>(), x[i] = read<int>();
	int ans = 1;
	for (int c = 0; c < k; c++)
	{
		REP(i, 1, n + 1) s[i] = pos[i] = 0;
		REP(i, 1, m)
			if (x[i] >> c & 1)
			{
				s[l[i]]++;
				s[r[i] + 1]--;
			}
			else chkmax(pos[r[i] + 1], l[i]);
		REP(i, 1, n + 1)
		{
			s[i] += s[i - 1];
			chkmax(pos[i], pos[i - 1]);
		}
		f[0] = 1;
		int sum = 1, lst = 0;
		REP(i, 1, n + 1)
		{
			while (lst < pos[i]) (sum -= f[lst++]) %= MOD;
			if (s[i]) f[i] = 0;
			else
			{
				f[i] = sum;
				(sum <<= 1) %= MOD;
			}
		}
		ans = 1ll * ans * f[n + 1] % MOD;
	}
	cout << (ans + MOD) % MOD << endl;
	return 0;
}
