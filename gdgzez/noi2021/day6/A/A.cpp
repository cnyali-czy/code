/*
	Problem:	A.cpp
	Time:		2021-03-09 10:43
	Author:		CraZYali
	E-Mail:		yms-chenziyang@outlook.com 
*/

#define REP(i, s, e) for (register int i(s), end_##i(e); i <= end_##i; i++)
#define DEP(i, s, e) for (register int i(s), end_##i(e); i >= end_##i; i--)
#define DEBUG fprintf(stderr, "Passing [%s] in Line %d\n", __FUNCTION__, __LINE__)

#define chkmax(a, b) (a < (b) ? a = (b) : a)
#define chkmin(a, b) (a > (b) ? a = (b) : a)

#include <bitset>
#include <cstring>
#include <iostream>
#include <cstdio>

using namespace std;
const int maxn = 1050;

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

int n, a[maxn], b[maxn];
bitset <maxn> A, B;
char str[maxn];

int getstr(int x, int y, bool op)
{
    if (!y)
	{
		REP(i, 0, x - 1) a[i] = op;
		return x;
    }
    int t = x / y;
    int d = getstr(y, x - y * t, !op);
    int cnt = 0;
	REP(i, 0, x - y * (t - 1) - 1)
	{
		if (a[i] ^ op) REP(j, 1, t) b[cnt++] = op;
		b[cnt++] = a[i];
    }
	REP(i, 0, cnt - 1) a[i] = b[i];
    return d;
}
int solve(int d)
{
	bitset <maxn> res0, res1;
	REP(i, 0, n - 1)
		if (!a[i]) res0[i] = 1;
		else res1[i] = 1;
	int ans = 0;
	REP(i, 0, d - 1)
	{
		if ((A & res1).none() && (B & res0).none()) ans++;
		res1 >>= 1;res0 >>= 1;
		if (!a[i]) res0[n - 1] = 1;
		else res1[n - 1] = 1;
    }
    return ans;
}

int main()
{
#ifdef CraZYali
	file("A");
#endif
	scanf("%d\n%s", &n, str);
	REP(i, 0, n - 1)
	{
		A[i] = (str[i] == '0');
		B[i] = (str[i] == '1');
	}
	int ans = 0;
	REP(i, 0, n)
	{
		int d = (i < n - i ? getstr(n - i, i, 1) : getstr(i, n - i, 0));
		ans += solve(n / d);
	}
	cout << ans << endl;
	return 0;
}
