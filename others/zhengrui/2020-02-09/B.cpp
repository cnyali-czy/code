/*
 * File Name:	B.cpp
 * Author	:	CraZYali
 * Time		:	2020.02.09 09:18
 * Email	:	yms-chenziyang@outlook.com
 */

#define DEP(i, s, e) for (register int i(s), end_##i(e); i >= end_##i; i--)
#define REP(i, s, e) for (register int i(s), end_##i(e); i <= end_##i; i++)
#define DEBUG fprintf(stderr, "Passing [%s] in Line %d\n", __FUNCTION__, __LINE__)

#define chkmax(a, b) (a < (b) ? a = (b) : a) 
#define chkmin(a, b) (a > (b) ? a = (b) : a) 

#include <iostream>
#include <cstdio>
#define i64 long long
using namespace std;

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

struct Vector
{
	i64 x, y;
	Vector(i64 x = 0, i64 y = 0) : x(x), y(y) {}
	Vector operator + (Vector B) {return Vector(x + B.x, y + B.y);}
	Vector operator +=(Vector B) {return *this = *this + B;}
	Vector operator - (Vector B) {return Vector(x - B.x, y - B.y);}
	i64 operator * (Vector B) {return x * B.y - y * B.x;}
	Vector operator * (i64 B) {return Vector(B * x, B * y);}
}lake[maxn];

int W, H, n;

int main()
{
#ifdef CraZYali
	file("C");
#endif
	return 0;
}
