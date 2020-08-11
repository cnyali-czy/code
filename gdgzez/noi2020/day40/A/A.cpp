/*
	Problem:	A.cpp
	Time:		2020-08-11 11:08
	Author:		CraZYali
	E-Mail:		yms-chenziyang@outlook.com 
*/

#define REP(i, s, e) for (register int i(s), end_##i(e); i <= end_##i; i++)
#define DEP(i, s, e) for (register int i(s), end_##i(e); i >= end_##i; i--)
#define DEBUG fprintf(stderr, "Passing [%s] in Line %d\n", __FUNCTION__, __LINE__)

#define chkmax(a, b) (a < (b) ? a = (b) : a)
#define chkmin(a, b) (a > (b) ? a = (b) : a)

#include <algorithm>
#include <iostream>
#include <cstdio>
#define i64 long long
using namespace std;
const int maxn = 5e6 + 10, maxk = 1.5e7 + 10;

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

int n, k, a[maxn], b[maxn];

namespace gen
{
	const int threshold=10000000;
	unsigned long long k1,k2;
	unsigned long long xorShift128Plus()
	{
		unsigned long long k3=k1,k4=k2;
		k1=k4;
		k3^=k3<<23;
		k2=k3^k4^(k3>>17)^(k4>>26);
		return k2+k4;
	}
	void gen()
	{
		scanf("%d%d%llu%llu",&n,&k,&k1,&k2);
		REP(i, 1, n)
		{
			a[i] = xorShift128Plus() % threshold + 1;
			b[i] = a[i] + xorShift128Plus() % threshold + 1;
		}
	} 
}

namespace fastsort
{
	const int w = 8, B = (1 << w) - 1;

	int cnt[B + 1];
	int *pool, *str[B + 1];

#define work()\
	{\
		for (int i = 0; i < n; i++) cnt[a[i] >> w & B]++;\
		str[0] = pool;\
		for (int i = 0; i < B; i++) str[i + 1] = str[i] + cnt[i], cnt[i] = 0;\
		for (int i = 0; i < n; i++) *(str[a[i] >> w & B]++) = a[i];\
	}

	void sort(int *a, int n)
	{
		pool = new int[n];
		int w = 0;
		{
			for (int i = 0; i < n; i++) cnt[a[i] & B]++;
			str[0] = pool;
			for (int i = 0; i < B; i++) str[i + 1] = str[i] + cnt[i], cnt[i] = 0;
			for (int i = 0; i < n; i++) *(str[a[i] & B]++) = a[i];
			std :: swap(a, pool);
		}
		w += fastsort :: w;
		work();
		std :: swap(a, pool);

		w += fastsort :: w;
		work();
		std :: swap(a, pool);

		w += fastsort :: w;
		work();
		std :: swap(a, pool);
		//a = pool;
	}
}
int main()
{
#ifdef CraZYali
	file("A");
#endif
	gen :: gen();
	i64 ans = 0, Ans = 0;
	fastsort :: sort(a + 1, n);reverse(a + 1, a + 1 + n);
	fastsort :: sort(b + 1, n);reverse(b + 1, b + 1 + n);
	int n1 = 0, n2 = 0;
	REP(i, 1, k)
	{
		ans += a[++n1];
		while (n1 >= 2)
		{
			int delta = b[n2 + 1] - a[n1] - a[n1 - 1];
			if (delta > 0)
			{
				ans += delta;
				n2++;n1 -= 2;
			}
			else break;
		}
		Ans ^= ans;
	}
	cout << Ans << endl;
	return 0;
}
