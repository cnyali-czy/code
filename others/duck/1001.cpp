/*
	Problem:	1001.cpp
	Time:		2020-08-11 16:02
	Author:		CraZYali
	E-Mail:		yms-chenziyang@outlook.com 
*/

#define REP(i, s, e) for (register int i(s), end_##i(e); i <= end_##i; i++)
#define DEP(i, s, e) for (register int i(s), end_##i(e); i >= end_##i; i--)
#define DEBUG fprintf(stderr, "Passing [%s] in Line %d\n", __FUNCTION__, __LINE__)

#define chkmax(a, b) (a < (b) ? a = (b) : a)
#define chkmin(a, b) (a > (b) ? a = (b) : a)

#include <algorithm>
#include <vector>
#include <iostream>
#include <cstdio>

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

const int w = 8, B = (1 << w) - 1;

const int maxn = 100000000;
int cnt[B + 1];
unsigned *pool, *str[B + 1];

void sort(unsigned *a, int n)
{
	pool = new unsigned[n];
	/*
	int times = 32 / w;
	REP(j, 0, times - 1)
	{
		REP(i, 0, n - 1) cnt[(a[i] >> (j * w)) & B]++;
		str[0] = pool;
		REP(i, 1, B) str[i] = str[i - 1] + cnt[i - 1], cnt[i - 1] = 0;
		REP(i, 0, n - 1) *(str[(a[i] >> (j * w)) & B]++) = a[i];
		std :: swap(a, pool);
	}
	*/
	int w = 0;
	{
		REP(i, 0, n - 1) cnt[a[i] & B]++;
		str[0] = pool;
		REP(i, 1, B) str[i] = str[i - 1] + cnt[i - 1], cnt[i - 1] = 0;
		REP(i, 0, n - 1) *(str[a[i] & B]++) = a[i];
		std :: swap(a, pool);
	}
	w += ::w;
	{
		REP(i, 0, n - 1) cnt[a[i] >> w & B]++;
		str[0] = pool;
		REP(i, 1, B) str[i] = str[i - 1] + cnt[i - 1], cnt[i - 1] = 0;
		REP(i, 0, n - 1) *(str[a[i] >> w & B]++) = a[i];
		std :: swap(a, pool);
	}
	w += ::w;
	{
		REP(i, 0, n - 1) cnt[a[i] >> w & B]++;
		str[0] = pool;
		REP(i, 1, B) str[i] = str[i - 1] + cnt[i - 1], cnt[i - 1] = 0;
		REP(i, 0, n - 1) *(str[a[i] >> w & B]++) = a[i];
		std :: swap(a, pool);
	}
	w += ::w;
	{
		REP(i, 0, n - 1) cnt[a[i] >> w & B]++;
		str[0] = pool;
		REP(i, 1, B) str[i] = str[i - 1] + cnt[i - 1], cnt[i - 1] = 0;
		REP(i, 0, n - 1) *(str[a[i] >> w & B]++) = a[i];
		a = pool;
	}
}

#ifdef CraZYali
unsigned a[maxn];
int main()
{
	file("1001");
	int n = read<int>();
	REP(i, 0, n - 1) scanf("%u", a + i);
	sort(a, n);
	REP(i, 0, n - 1) printf("%u%c", a[i], i == end_i ? '\n' : ' ');
	return 0;
}
#endif
