/*
	Problem:	B.cpp
	Time:		2020-06-15 10:17
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
#include <cstring>

using namespace std;
const int maxn = 50 + 5, maxS = 100000 + 10;
#define ui64 unsigned long long
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

int n, q, Len, len[maxn];
char S[maxS], tmp[maxS];string s[maxn];
const ui64 base = 1e9 + 7;
ui64 H[maxS], h[maxn], bin[maxS];
ui64 query(int l, int r) {return H[r] - H[l - 1] * bin[r - l + 1];}
int lst;
int main()
{
#ifdef CraZYali
	file("B");
#endif
	n = read<int>();q = read<int>();
	REP(i, 1, n)
	{
		cin >> s[i];
		len[i] = s[i].size();
		REP(j, 0, s[i].size() - 1) h[i] = h[i] * base + s[i][j];
	}
	scanf("%s", S + 1);
	Len = strlen(S + 1);
	bin[0] = 1;
	REP(i, 1, Len)
	{
		H[i] = H[i - 1] * base + S[i];
		bin[i] = bin[i - 1] * base;
	}
	lst = Len;
	while (q--)
	{
		int opt = read<int>(), l = read<int>(), r = read<int>();
		if (opt == 1)
		{
			scanf("%s", tmp);
			int qaq = strlen(tmp);
			REP(i, l, r) S[i] = tmp[(i - l) % qaq];
			chkmin(lst, l - 1);
//			REP(i, l, Len) H[i] = H[i - 1] * base + S[i];
//			puts(S+1);
		}
		else
		{
			REP(i, lst + 1, r) H[i] = H[i - 1] * base + S[i];
			chkmax(lst, r);
			int ans = 0;
			REP(i, 1, n)
				REP(j, l, r - len[i] + 1) if (query(j, j + len[i] - 1) == h[i]) ans++;
			printf("%d\n", ans);
		}
	}
	return 0;
}
