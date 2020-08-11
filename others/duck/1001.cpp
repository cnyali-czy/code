/*
	Problem:	1001.cpp
	Time:		2020-08-11 16:02
	Author:		CraZYali
	E-Mail:		yms-chenziyang@outlook.com 
*/

#define file(FILE_NAME) freopen(FILE_NAME".in", "r", stdin), freopen(FILE_NAME".out", "w", stdout)

#include <iostream>
#include <cstdio>

const int w = 8, B = (1 << w) - 1;

const int maxn = 100000000;
int cnt[B + 1];
unsigned *pool, *str[B + 1];

#define work()\
{\
	for (int i = 0; i < n; i++) cnt[a[i] >> w & B]++;\
	str[0] = pool;\
	for (int i = 0; i < B; i++) str[i + 1] = str[i] + cnt[i], cnt[i] = 0;\
	for (int i = 0; i < n; i++) *(str[a[i] >> w & B]++) = a[i];\
}

void sort(unsigned *a, int n)
{
	pool = new unsigned[n];
	int w = 0;
	{
		for (int i = 0; i < n; i++) cnt[a[i] & B]++;
		str[0] = pool;
		for (int i = 0; i < B; i++) str[i + 1] = str[i] + cnt[i], cnt[i] = 0;
		for (int i = 0; i < n; i++) *(str[a[i] & B]++) = a[i];
		std :: swap(a, pool);
	}
	w += ::w;
	work();
	std :: swap(a, pool);

	w += ::w;
	work();
	std :: swap(a, pool);

	w += ::w;
	work();
	a = pool;
}

#ifdef CraZYali
unsigned a[maxn];
int main()
{
	file("1001");
	int n;scanf("%d", &n);
	for (int i = 0; i < n; i++) scanf("%u", a + i);
	sort(a, n);
	for (int i = 0; i < n; i++) printf("%u%c", a[i], i == n - 1 ? '\n' : ' ');
	return 0;
}
#endif
