/*
	Problem:	E.cpp
	Time:		2021-05-28 15:32
	Author:		CraZYali
	E-Mail:		yms-chenziyang@outlook.com 
*/

#define REP(i, s, e) for (register int i(s), end_##i(e); i <= end_##i; i++)
#define DEP(i, s, e) for (register int i(s), end_##i(e); i >= end_##i; i--)
#define DEBUG fprintf(stderr, "Passing [%s] in Line %d\n", __FUNCTION__, __LINE__)

#define chkmax(a, b) (a < (b) ? a = (b) : a)
#define chkmin(a, b) (a > (b) ? a = (b) : a)

#include <cstring>
#include <iostream>
#include <cstdio>

using namespace std;
const int maxn = 5e5 + 100;

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

int n, a[maxn], sum;
char s[maxn];

int main()
{
#ifdef CraZYali
	file("E");
#endif
	scanf("%s", s);
	n = strlen(s);
	REP(i, 1, n) a[i] = (s[n - i] - 48) * 9;
	n += 5;
	REP(i, 1, n) 
		if (a[i] > 9)
		{
			a[i + 1] += a[i] / 10;
			a[i] %= 10;
		}
	while (n > 1 && !a[n]) n--;
	REP(i, 1, n) sum += a[i];
	for (int k = 1; ; k++)
	{
		a[1] += 9;
		sum += 9;
		n += 5;
		REP(i, 1, n)
			if (a[i] > 9)
			{
				sum -= 9;
				a[i + 1]++;
				a[i] -= 10;
			}
			else break;
		while (n > 1 && !a[n]) n--;
		if (sum <= 9 * k) {cout << k << endl;return 0;}
	}
	return 0;
}
