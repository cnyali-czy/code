/*
	Problem:	B.cpp
	Time:		2020-09-06 21:27
	Author:		CraZYali
	E-Mail:		yms-chenziyang@outlook.com 
*/

#define REP(i, s, e) for (register int i(s), end_##i(e); i <= end_##i; i++)
#define DEP(i, s, e) for (register int i(s), end_##i(e); i >= end_##i; i--)
#define DEBUG fprintf(stderr, "Passing [%s] in Line %d\n", __FUNCTION__, __LINE__)

#define chkmax(a, b) (a < (b) ? a = (b) : a)
#define chkmin(a, b) (a > (b) ? a = (b) : a)

#include <bitset>
#include <iostream>
#include <cstdio>
#define int long long
using namespace std;

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

int p, g;

int st[114514], top;
void split(int x)
{
	for (int i = 2; i * i <= x; i++)
		if (x % i == 0)
		{
			st[++top] = i;
			while (x % i == 0) x /= i;
		}
	if (x > 1) st[++top] = x;
}
int power_pow(__int128 base, int b, const int MOD)
{
	__int128 ans = 1;
	while (b)
	{
		if (b & 1) (ans *= base) %= MOD;
		(base *= base) %= MOD;
		b >>= 1;
	}
	return ans;
}
bool judge(int g)
{
	int phi = p - 1;
	REP(i, 1, top)
		if (power_pow(g, phi / st[i], p) == 1) return 0;
	return 1;
}
const int maxb = 1e8;
bitset <maxb> b;

const int w = 4e5;
int p1[w + 5], p2[w + 5];
void init()
{
	p1[0] = 1;
	REP(i, 1, w) p1[i] = __int128(g) * p1[i - 1] % p;
	p2[0] = 1;
	REP(i, 1, w) p2[i] = __int128(p1[w]) * p2[i - 1] % p;
}
int pow(int b) {return __int128(p1[b % w]) * p2[b / w] % p;}
void print(__int128 x)
{
	static int st[100], top;
	top = 0;
	while (x)
	{
		st[++top] = x % 10;
		x /= 10;
	}
	DEP(i, top, 1) putchar(st[i] + '0');
}
signed main()
{
#ifdef CraZYali
	file("B");
#endif
	cin >> p;
	split(p - 1);
	for (g = 2; !judge(g); g++);
	init();
	//	cout << g << endl;
	REP(i, 1, (p - 1) / 2) b[pow(2 * i)] = 1;
	__int128 ans = 0;
	for (auto x = b._Find_first(); x ^ maxb; x = b._Find_next(x)) ans += x;
	print(ans);
	return 0;
}
