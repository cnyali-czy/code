/*
	Problem:	52.cpp
	Time:		2020-03-27 23:24
	Author:		CraZYali
	E-Mail:		yms-chenziyang@outlook.com 
*/

#define REP(i, s, e) for (register int i(s), end_##i(e); i <= end_##i; i++)
#define DEP(i, s, e) for (register int i(s), end_##i(e); i >= end_##i; i--)
#define DEBUG fprintf(stderr, "Passing [%s] in Line %d\n", __FUNCTION__, __LINE__)

#define chkmax(a, b) (a < (b) ? a = (b) : a)
#define chkmin(a, b) (a > (b) ? a = (b) : a)

#include <algorithm>
#include "kth.h"
#include <iostream>
#include <cstdio>

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
int num[300005], N, a, b, c;
int query_kth(int n_a, int n_b, int n_c, int k)
{
	N = a = b = c = 0;
	while (k >= 3)
	{
		int delta = k / 3;
		int A(get_a(a + delta - 1)), B(get_b(b + delta - 1)), C(get_c(c + delta - 1));
		if (A < B)
			if (A < C)	a += delta;
			else		c += delta;
		else
			if (B < C)	b += delta;
			else		c += delta;
		k -= delta;
    }
	REP(i, 1, k)
	{
		if (a < n_a) num[++N] = get_a(a++);
		if (b < n_b) num[++N] = get_b(b++);
		if (c < n_c) num[++N] = get_c(c++);
	}
	sort(num + 1, num + N + 1);
	return num[k];
	nth_element(num + 1, num + k, num + N + 1);
	return num[k];
}
