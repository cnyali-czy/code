/*
	Problem:	C.cpp
	Time:		2020-12-21 23:11
	Author:		CraZYali
	E-Mail:		yms-chenziyang@outlook.com 
*/

#define REP(i, s, e) for (register int i(s), end_##i(e); i <= end_##i; i++)
#define DEP(i, s, e) for (register int i(s), end_##i(e); i >= end_##i; i--)
#define DEBUG fprintf(stderr, "Passing [%s] in Line %d\n", __FUNCTION__, __LINE__)

#define chkmax(a, b) (a < (b) ? a = (b) : a)
#define chkmin(a, b) (a > (b) ? a = (b) : a)

#include <set>
#include <cstring>
#include <iostream>
#include <cstdio>
#define u64 unsigned long long
using namespace std;
const int maxn = 2e5 + 10;

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

int n, m;
char s[maxn], t[maxn];

const u64 base = 131, MOD = 998244353;
u64 bin[maxn], H[maxn];
u64 get(int l, int r) {return H[r] - H[l - 1] * bin[r - l + 1];}
int main()
{
#ifdef CraZYali
	file("C");
#endif
	scanf("%s\n%s", s + 1, t + 1);
	n = strlen(s + 1);m = strlen(t + 1);
	REP(i, 1, n) s[i] -= 'a' - 1;
	REP(i, 1, m) t[i] -= 'a' - 1;
	bin[0] = 1;
	REP(i, 1, m) bin[i] = bin[i - 1] * base;
	REP(i, 1, m) H[i] = H[i - 1] * base + t[i];
	set <u64> ssr;
	static int cnt[27], tnc[27];
	REP(i, 1, n) cnt[s[i]]++;
	REP(i, 1, n - 1) tnc[t[i]]++;
	REP(i, n, m)
	{
		tnc[t[i - n]]--;tnc[t[i]]++;
		bool flg = 1;
		REP(j, 1, 26) if (cnt[j] ^ tnc[j]) {flg = 0;break;}
		if (flg) ssr.emplace(get(i - n + 1, i));
	}
	cout << ssr.size() << endl;
	return 0;
}
