/*
 * File Name:	1439.cpp
 * Author	:	CraZYali
 * Year		:	2019.10.30 23:19
 * Email	:	yms-chenziyang@outlook.com
 */

#define DREP(i, s, e) for (register int i(s), end_##i(e); i >= end_##i; i--)
#define  REP(i, s, e) for (register int i(s), end_##i(e); i <= end_##i; i++)
#define DEBUG fprintf(stderr, "Passing [%s] in Line %d\n", __FUNCTION__, __LINE__)

#define chkmax(a, b) (a < (b) ? a = (b) : a) 
#define chkmin(a, b) (a > (b) ? a = (b) : a) 

#include <iostream>
#include <cstdio>

using namespace std;
const int maxn = 1e5 + 10;

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

int n, top;
int a[maxn], p[maxn], stack[maxn];

int find(int x)
{
	int l(1), r(top);
	while (l <= r)
	{
		int mid = l + r >> 1;
		if (p[stack[mid]] > p[x]) r = mid - 1;
		else l = mid + 1;
	}
	return r + 1;
}

int main()
{
#ifdef CraZYali
	file("1439");
#endif
	cin >> n;
	REP(i, 1, n) a[i] = read<int>();
	REP(i, 1, n) p[read<int>()] = i;
	REP(i, 1, n)
		if (p[a[i]] > p[stack[top]]) stack[++top] = a[i];
		else stack[find(a[i])] = a[i];
	cout << top << endl;
    return 0;
}
