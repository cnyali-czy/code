/*
	Problem:	A.cpp
	Time:		2020-02-24 00:06
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
#define int long long
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
inline int Abs(int x) {return x < 0 ? -x : x;}

int area(int x1, int y1, int x2, int y2)
{
	return Abs(x1 - x2 + 1) * Abs(y1 - y2 + 1);
}
int ans;
int a, b, x, y;
void Chk(int x1, int y1, int x2, int y2)
{
	if (x1 < 0 || x1 >= a || x2 < 0 || x2 >= a) return;
	if (y1 < 0 || y1 >= b || y2 < 0 || y2 >= b) return;
	chkmax(ans, area(x1, y1, x2, y2));
}
int d[][2] = {{1, 0}, {-1, 0}, {0, 1}, {0, -1}};
signed main()
{
#ifdef CraZYali
	file("A");
#endif
	register int T = read<int>();
	while(T--)
	{
		cin >> a >> b >> x >> y;
		x++;y++;
		ans = 0;
		chkmax(ans, (x - 1) * b);//cerr<<ans<<' ';
		chkmax(ans, (a - x) * b);//cerr<<ans<<' ';
		chkmax(ans, (y - 1) * a);//cerr<<ans<<' ';
		chkmax(ans, (b - y) * a);//cerr<<ans<<' ';
		//cerr<<endl;
		cout << ans << '\n';
	}
	return 0;
}
