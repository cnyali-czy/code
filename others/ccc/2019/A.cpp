#define REP(i, s, e) for (register int i(s), end_##i(e); i <= end_##i; i++)
#define DEP(i, s, e) for (register int i(s), end_##i(e); i >= end_##i; i--)

#include <iostream>
#include <cstdio>

using namespace std;

int a[2][2];

int main()
{
	freopen("A.in", "r", stdin);
	freopen("A.out", "w", stdout);
	a[0][0] = 1;a[0][1] = 2;
	a[1][0] = 3;a[1][1] = 4;
	while (1)
	{
		char c;
		if ((c = getchar()) == EOF) break;
		if (c == 'H') swap(a[0], a[1]);
		else if (c == 'V') swap(a[0][0], a[0][1]), swap(a[1][0], a[1][1]);
		else break;
	}
	printf("%d %d\n%d %d\n", a[0][0], a[0][1], a[1][0], a[1][1]);
	return 0;
}
