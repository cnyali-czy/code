#define DREP(i, s, e) for(register int i = s; i >= e ;i--)
#define  REP(i, s, e) for(register int i = s; i <= e ;i++)

#define DEBUG fprintf(stderr, "Passing [%s] in Line %d\n", __FUNCTION__, __LINE__)
#define chkmax(a, b) a = max(a, b)
#define chkmin(a, b) a = min(a, b)

#include <algorithm>
#include <iostream>
#include <cstdlib>
#include <cstring>
#include <cstdio>
#include <bitset>
#include <vector>
#include <cmath>
#include <queue>
#include <map>
#include <set>

using namespace std;
const int maxn = 5000 + 10;

int m, n, c;
bool av[20];

struct node
{
	int s[500 + 5], len;
};

inline void print(node x)
{
	REP(i, 0, x.len - 1)
	{
		if (x.s[i] <= 9) printf("%d", x.s[i]);
		else printf("%c", x.s[i] + 'A' - 10);
	}
	putchar(10);
}

inline int mod(node x)
{
	int res(0);
	REP(i, 0, x.len - 1)
		res = (res * c + x.s[i]) % n;
	return res;
}

queue <node> q;
bool vis[maxn];

inline bool BFS()
{
	memset(vis, 0, sizeof(vis));
	while (!q.empty()) q.pop();
	node x;
	x.len = 0;
	int r;
	REP(i, 1, 15)
		if (av[i])
		{
			x.s[0] = i;
			x.len = 1;
			r = mod(x);
			if (!r) {print(x);return 1;}
			else if (!vis[r])
			{
				vis[r] = 1;
				q.push(x);
			}
		}
	while (!q.empty())
	{
		x = q.front();
		q.pop();
		REP(i, 0, 15)
			if (av[i])
			{
				x.s[x.len++] = i;
				r = mod(x);
				if (!r) {print(x);return 1;}
				else if (!vis[r] && x.len < 499)
				{
					vis[r] = 1;
					q.push(x);
				}
				x.len--;
			}
	}
	return 0;
}

int main()
{
#ifdef CraZYali
	freopen("超级密码.in", "r", stdin);
	freopen("超级密码.out", "w", stdout);
#endif
	int T;
	cin >> T;
	while (T--)
	{
		memset(av, 0, sizeof(av));
		scanf("%d%d%d", &n, &c, &m);
		REP(i, 1, m)
		{
			register char c;
			do
			scanf("%c", &c);
			while (!isdigit(c) && !('A' <= c && c <= 'Z'));
			if (isdigit(c)) av[c - '0'] = 1;
			else av[c - 'A' + 10] = 1;
		}
		if (n) {if(!BFS()) printf("give me the bomb please\n");}
		else 
		{
			if (av[0]) printf("0\n");
			else printf("give me the bomb please\n");

		}
	}

	return 0;
}
