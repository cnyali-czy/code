#include <cstdio>
#include <cstring>
#include <iostream>
#include <cstdlib>
#include <algorithm>

using std::cin;
using std::sort;

const int MAXN = 100010;
const int INF = 0x3f3f3f3f;

int g[MAXN];

struct gp {
	int value, num;
	gp()
	{
		value = -INF;
		num = 0;
	}
}a[MAXN];

inline bool cmp(gp a, gp b);

int main()
{
	freopen("invest.in", "r", stdin);
	freopen("invest.out", "w", stdout);
	
	int N;
	scanf("%d", &N);
	
	for (register int i = 1; i <= N; i++) {
		scanf("%d", &g[i]);
		a[i].num = i;
	}
	
	char s[101];
	while (cin.getline(s, 100)) {
		if (s[0] == 'E')
			exit(0);
		if (s[0] == 'R')
			printf("%d %d\n", a[1].num, a[2].num);
		if (isdigit(s[0])) {
			int slen = strlen(s) - 1, x = 0, num = 0;
			bool pd = true;
			for (register int i = 0; i <= slen; i++) {
				if (s[i] == ' ') {
					pd = false;
					continue ;
				}
				if (pd)
					x = x * 10 + s[i] - 48;
				else
					num = num * 10 + s[i] - 48;
			}
			for (register int i = 1; i <= N; i++)
				if (a[i].num == x)
					a[i].value = num - g[a[i].num];
			sort(a + 1, a + N + 1, cmp);
		}
	}
	
	return 0;
}

inline bool cmp(gp a, gp b)
{
	return a.value > b.value;	
}
