#define  REP(i, s, e) for (int i = s; i <= e; i++)
#define DREP(i, s, e) for (int i = s; i >= e; i--)
#define DEBUG fprintf(stderr, "Passing [%s] in Line %d\n", __FUNCTION__, __LINE__)

#define chkmax(a, b) a = max(a, b)
#define chkmin(a, b) a = min(a, b)

#include<iostream>
#include<cstdio>

using namespace std;


int biao[] = {1,3,5,9,13,17,25,33,41,49,65,81};

int main()
{
#ifdef CraZYali
	freopen("D.out", "w", stdout);
#endif
	REP(i, 0, 11)printf("%d\n", biao[i]);
	return 0;
}

