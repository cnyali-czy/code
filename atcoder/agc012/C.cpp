/*
	Problem:	C.cpp
	Time:		2021-05-31 20:55
	Author:		CraZYali
	E-Mail:		yms-chenziyang@outlook.com 
*/

#define REP(i, s, e) for (register int i(s), end_##i(e); i <= end_##i; i++)
#define DEP(i, s, e) for (register int i(s), end_##i(e); i >= end_##i; i--)
#define DEBUG fprintf(stderr, "Passing [%s] in Line %d\n", __FUNCTION__, __LINE__)

#define chkmax(a, b) (a < (b) ? a = (b) : a)
#define chkmin(a, b) (a > (b) ? a = (b) : a)

#include <vector>
#include <algorithm>
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

long long n;
int m;
#define vec vector <int> 
vec operator + (vec A, vec B) {A.insert(A.end(), B.begin(), B.end());return A;}

vec build(long long n)
{
	if (n == 1) return vec(0);
	auto res = build(n >> 1);
	res = res + vec{++m};
	if (n & 1) res = vec{++m} + res;
	//cerr << n << ": ";for (auto i : res) cerr << i << ' ' ;cerr << endl;
	return res;
}

int main()
{
#ifdef CraZYali
	file("C");
#endif
	cin >> n;n++;
	vec ans = build(n);
	printf("%d\n", 100 + ans.size());
	REP(i, 1, 100) printf("%d ", i);
	for (auto i : ans) cout << i << ' ' ;
	for (auto i : ans) cerr << i << ' ' ;
	
	return 0;
}
