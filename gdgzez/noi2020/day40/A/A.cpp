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
	const int maxN = 2e7 + 10;
	int cnt[maxN];
	void sort(int a[])
	{
		int Max = 0, Min = 2e7;
		REP(i, 1, n)
		{
			cnt[a[i]]++;
			if (Max < a[i]) Max = a[i];
			if (Min > a[i]) Min = a[i];
		}
		int N = 0;
		DEP(i, Max, Min)
			while (cnt[i])
			{
				cnt[i]--;
				a[++N] = i;
			}
	}
}

int main()
{
#ifdef CraZYali
	file("A");
#endif
	gen :: gen();
	i64 ans = 0, Ans = 0;
	fastsort :: sort(a);
	fastsort :: sort(b);
	int n1 = 0, n2 = 0;
	REP(i, 1, k)
	{
		if (n1 < n)	ans += a[++n1];
		else		ans += b[++n2];
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
