/*
	Problem:	A.cpp
	Time:		2021-06-20 08:24
	Author:		CraZYali
	E-Mail:		yms-chenziyang@outlook.com 
*/

#define REP(i, s, e) for (register int i(s), end_##i(e); i <= end_##i; i++)
#define DEP(i, s, e) for (register int i(s), end_##i(e); i >= end_##i; i--)
#define DEBUG fprintf(stderr, "Passing [%s] in Line %d\n", __FUNCTION__, __LINE__)

#define chkmax(a, b) (a < (b) ? a = (b) : a)
#define chkmin(a, b) (a > (b) ? a = (b) : a)

#include <cstring>
#include <algorithm>
#include <bitset>
#include <iostream>
#include <cstdio>
#include <vector>
#define i64 long long
using namespace std;
const int maxn = 3000 + 10, maxk = 10000 + 10;

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
string s[maxn];

const i64 base = 1e9 + 9, MOD = 2000000011;
vector <i64> h[maxn];
i64 bin[maxk];
inline bool cmp(int x, int y)
{
	return s[x] < s[y];
	int l = 0, r = min(s[x].size(), s[y].size()) - 1, res = -1;
	while (l <= r)
	{
		int mid = l + r >> 1;
		if (h[x][mid] == h[y][mid])
		{
			res = mid;
			l = mid + 1;
		}
		else r = mid - 1;
	}
	if (res == min(s[x].size(), s[y].size()) - 1) return s[x].size() < s[y].size();
	return s[x][res + 1] < s[y][res + 1];
}

bitset <maxk> f[maxn], all;
int main()
{
#ifdef CraZYali
	file("A");
#endif
	n = read<int>();k = read<int>();
	bin[0] = 1;REP(i, 1, k) bin[i] = bin[i - 1] * base % MOD;
	REP(i, 1, n)
	{
		scanf("%s", str);
		s[i] = str;
		unsigned i64 H = 0;
		REP(i, 0, strlen(str) - 1)
			h[i].emplace_back(H = (H * base + str[i]) % MOD);
	}
	static int id[maxn], rk[maxn];
	REP(i, 1, n) id[i] = i;
	sort(id + 1, id + 1 + n, cmp);
	REP(i, 1, n) rk[id[i]] = i;

	REP(i, 0, k) all[i] = 1;
	f[n + 1][0] = 1;
	DEP(i, n, 1) f[i] = ((f[i + 1] << s[i].size()) | f[i + 1]) & all;

	int lst = 0, len = 0;
	while (len < k)
	{
		string res = "";int pick = 0;
		REP(i, lst + 1, n) if (f[i + 1][k - len - s[i].size()])
			if (!pick || rk[i] < rk[pick]) pick = i;
		lst = pick;
		res = s[pick];
		len += res.size();
		printf("%s", res.c_str());
	}
	return 0;
}
