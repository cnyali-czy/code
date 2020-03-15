/*
	Problem:	C.cpp
	Time:		2020-03-15 17:52
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
const int maxn = 1e6 + 10;

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
struct interval
{
	int n;
	i64 sum;
	interval(int n = 0, i64 sum = 0) : n(n), sum(sum) {}
	inline interval operator +		(interval B) {return interval(n + B.n, sum + B.sum);}
	inline interval operator +=	(interval B) {return *this = *this + B;}
	inline bool operator < (const interval &B) const {return 1. * n / sum < 1. * B.n / B.sum;}
	inline bool operator > (const interval &B) const {return 1. * n / sum > 1. * B.n / B.sum;}
}stack[maxn];
int a[maxn], n, top;

int main()
{
#ifdef CraZYali
	file("C");
#endif
	n = read<int>();
	REP(i, 1, n) a[i] = read<int>();
	stack[top = 1] = interval(1, a[1]);
	REP(i, 2, n)
	{
		stack[++top] = interval(1, a[i]);
		while (top > 1)
			if (stack[top - 1] < stack[top])
			{
				stack[top - 1] += stack[top];
				DEBUG;
				top--;
			}
			else break;
	}
	REP(i, 1, top)
	{
		double res = 1. * stack[i].sum / stack[i].n;
		REP(j, 1, stack[i].n) printf("%.10lf\n", res);
	}
	return 0;
}
