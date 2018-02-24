#define  REP(i, s, e) for(register int i = s; i <= e ;i++)
#define DREP(i, s, e) for(register int i = s; i >= e ;i--)

#define DEBUG fprintf(stderr, "Passing [%s] in LINE %d\n", __FUNCTION__, __LINE__)
#define chkmin(a, b) a = min(a, b)
#define chkmax(a, b) a = max(a, b)

#include <bits/stdc++.h>

using namespace std;
const int maxn = 25;

template <typename T> T read()
{
	T ans(0), p(1);
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

int m, n, k;
int a[maxn][maxn];

#define node pair<int, int>
#define now first
#define step second

bool vis[2 << 21];

int main()
{
	freopen("tv.in", "r", stdin);
	freopen("tv.out", "w", stdout);
	n = read<int>();
	REP(i, 1, n) k |= ((read<int>()) << i);
	REP(i, 1, n)
	{
		a[i][0] = read<int>();
		REP(j, 1, a[i][0])
			a[i][j] = read<int>();
	}
	queue <node> q;
	q.push(make_pair(k, 0));
	while (!q.empty())
	{
		register node x = q.front();
		q.pop();
		if (x.now == (1 << 3))
		{
			cout << x.step;
			return 0;
		}
		REP(i, 1, n)
			if (!(x.now & (1 << i)))
			{
				register node temp;
				temp.step = x.step + 1;
				temp.now = x.now;
				temp.now |= (1 << i);
				REP(j, 1, a[i][0])
					if (temp.now & (1 << a[i][j]))
						temp.now ^= (1 << a[i][j]);
				if (vis[temp.now]) continue;
				else
				{
					vis[temp.now] = 1;
					q.push(temp);
				}
			}
	}

	return 0;
}
