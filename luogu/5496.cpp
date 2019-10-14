#define  REP(i, s, e) for (register int i(s), end_##i(e); i <= end_##i; i++)
#define DREP(i, s, e) for (register int i(s), end_##i(e); i >= end_##i; i--)
#define DEBUG fprintf(stderr, "Passing [%s] in Line %d\n", __FUNCTION__, __LINE__)

#define chkmax(a, b) a = max(a, b)
#define chkmin(a, b) a = min(a, b)

#include <iostream>
#include <cstdio>
#include <cstring>

using namespace std;
const int maxn = 5e5 + 10, maxN = maxn << 1;

int ch[maxN][26], fail[maxN], len[maxN], num[maxN], cur;

int n, length, last, s[maxn]; 
char str[maxn]; 

inline void init()
{
	fail[0] = 1;
	len[fail[0] = 1] = -1;
	cur = 1;
}

inline int get_fail(int x)
{
	while (s[n - len[x] - 1] ^ s[n]) x = fail[x];
	return x; 
}
inline void extend()
{
	register int p = get_fail(last); 
	if (!ch[p][s[n]])
	{
		++cur;
		len[cur] = len[p] + 2;
		register int tmp = get_fail(fail[p]);
		fail[cur] = ch[tmp][s[n]];
		num[cur] = num[fail[cur]] + 1;
		ch[p][s[n]] = cur;
	}
	last = ch[p][s[n]];
}

#define file(a) freopen(a".in", "r", stdin), freopen(a".out", "w", stdout)

int main()
{
#ifdef CraZYali
	file("5496");
#endif
	init();
	scanf("%s", str + 1);
	length = strlen(str + 1);
	register int k(0);
	s[0] = 26; 
	for (n = 1; n <= length; n++)
	{
		str[n] = (str[n] - 97 + k) % 26 + 97; 
		s[n] = str[n] - 'a'; 
		extend(); 
		printf("%d ", num[last]);
		k = num[last];
	}
	return 0; 
}
