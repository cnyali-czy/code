#define  REP(i, s, e) for (int i = s; i <= e; i++)
#define DREP(i, s, e) for (int i = s; i >= e; i--)
#define DEBUG fprintf(stderr, "Passing [%s] in Line %d\n", __FUNCTION__, __LINE__)

#define chkmax(a, b) a = max(a, b)
#define chkmin(a, b) a = min(a, b)

#include <iostream>
#include <cstdio>
#include <queue>

using namespace std;
const int maxt = 1000 + 10, maxn = 1e6 + 10;

template <typename T> T read()
{
	T ans = 0, p = 1;
	char c = getchar();
	while (!isdigit(c))
	{
		if (c == '-') p = -1;
		c = getchar();
	}
	while (isdigit(c))
	{
		ans = ans * 10 + c - 48;
		c = getchar();
	}
	return ans * p;
}

int Case, t;
bool f[maxt];
int belong[maxn];

char s[10];

int main()
{
#ifdef CraZYali
	freopen("C.in", "r", stdin);
	freopen("C.out", "w", stdout);
#endif
	while (scanf("%d", &t) * t)
	{
		queue <int> q[maxt], team;
		printf("Scenario #%d\n", ++Case);
		REP(i, 1, t)
		{
			f[i] = 0;
			int n = read<int>();
			while (n --> 0) belong[read<int>()] = i;
		}
		while (scanf("%s", s + 1) != EOF && s[1] != 'S')
		{
			if (s[1] == 'E')
			{
				int x = read<int>();
				if (!f[belong[x]]) 
				{
					team.push(belong[x]);
					f[belong[x]] = 1;
				}
				q[belong[x]].push(x);
			}
			else
			{
				int frt = team.front();
				printf("%d\n", q[frt].front());
				q[frt].pop();
				if (q[frt].empty())
				{
					f[frt] = 0;
					team.pop();
				}
			}
		}
		putchar(10);
	}
	return 0;
}
