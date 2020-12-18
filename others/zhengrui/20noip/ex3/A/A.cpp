/*
	Problem:	A.cpp
	Time:		2020-12-18 15:56
	Author:		CraZYali
	E-Mail:		yms-chenziyang@outlook.com 
*/

#define REP(i, s, e) for (register int i(s), end_##i(e); i <= end_##i; i++)
#define DEP(i, s, e) for (register int i(s), end_##i(e); i >= end_##i; i--)
#define DEBUG fprintf(stderr, "Passing [%s] in Line %d\n", __FUNCTION__, __LINE__)

#define chkmax(a, b) (a < (b) ? a = (b) : a)
#define chkmin(a, b) (a > (b) ? a = (b) : a)

#include <map>
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
		ans = ans * 10 + (c - 48);
		c = getchar();
	}
	return ans * flag;
}

#define file(FILE_NAME) freopen(FILE_NAME".in", "r", stdin), freopen(FILE_NAME".out", "w", stdout)

int n, k;
char str[maxn];
i64 s[maxn];
map <i64, int> Max, Min;

int main()
{
#ifdef CraZYali
	file("A");
#endif
	n = read<int>();k = read<int>();
	scanf("%s", str + 1);
	REP(i, 1, n)
	{
		s[i] = s[i - 1];
		if (str[i] == '1') s[i] -= k;
		else s[i]++;
	}
	REP(i, 0, n) Max[s[i]] = i;
	DEP(i, n, 0) Min[s[i]] = i;
	int ans = 0;
	REP(i, 1, n) ans = max(ans, Max[s[i]] - Min[s[i]]);
	cout << ans << endl;
	return 0;
}
