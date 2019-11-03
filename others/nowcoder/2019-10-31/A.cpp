/*
 * File Name:	A.cpp
 * Author	:	CraZYali
 * Year		:	2019.10.31 18:38
 * Email	:	yms-chenziyang@outlook.com
 */

#define DREP(i, s, e) for (register int i(s), end_##i(e); i >= end_##i; i--)
#define  REP(i, s, e) for (register int i(s), end_##i(e); i <= end_##i; i++)
#define DEBUG fprintf(stderr, "Passing [%s] in Line %d\n", __FUNCTION__, __LINE__)

#define chkmax(a, b) (a < (b) ? a = (b) : a) 
#define chkmin(a, b) (a > (b) ? a = (b) : a) 

#include <iostream>
#include <cstdio>
#include <set>

using namespace std;
const int maxn = 400000 + 10;

template <typename T> inline T read()
{
	T ans(0), flag(1);
	char c(getchar());
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

#define file(FILE_NAME) freopen(FILE_NAME".in", "r", stdin), freopen(FILE_NAME".out", "w", stdout);

int n, m, q, a[maxn];
multiset <int, greater <int> > S;
long long sum;

int main()
{
#ifdef CraZYali
	file("A");
#endif
	cin >> n >> m >> q;
	REP(i, 1, n)
	{
		S.insert(a[i] = read<int>());
		sum += a[i];
	}
	printf("%lld\n", max((long long)*S.begin(), sum / m + (sum % m == 0 ? 0 : 1)));
	while (q--)
	{
		int i(read<int>());
		sum -= a[i];
		S.erase(S.find(a[i]));
		a[i] = read<int>();
		S.insert(a[i]);
		sum += a[i];
		printf("%lld\n", max((long long)*S.begin(), sum / m + (sum % m == 0 ? 0 : 1)));
	}
	return 0;
}
