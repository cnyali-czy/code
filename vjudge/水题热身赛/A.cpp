#define  REP(i, s, e) for(register int i = s; i <= e ;i++)
#define DREP(i, s, e) for(register int i = s; i >= e ;i--)

#define DEBUG fprintf(stderr, "Passing [%s] in LINE %d\n", __FUNCTION__, __LINE__)
#define chkmin(a, b) a = min(a, b)
#define chkmax(a, b) a = max(a, b)

#include <iostream>
#include <cstring>
#include <cstdio>

using namespace std;

int m, n, k;

char s1[1000], s2[1000];

char s[1000][1000];

int top = 1, rtop = 1;

int main()
{
#ifdef CraZYali
	freopen("A.in", "r", stdin);
	freopen("A.out", "w", stdout);
#endif
	ios::sync_with_stdio(false);
	strcpy(s[top = rtop = 1], "http://www.acm.org/");
	while (scanf("%s", s1) != EOF)
		if (s1[0] == 'V')
		{
			scanf("%s", s2);
			strcpy(s[++top], s2), rtop = top;
			puts(s2);
		}
		else if (s1[0] == 'B')
		{
			if (top == 1) puts("Ignored");
			else puts(s[--top]);
		}
		else if (s1[0] == 'F')
		{
			if (top == rtop) puts("Ignored");
			else puts(s[++top]);
		}
		else return 0;
}
