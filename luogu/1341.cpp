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
const int maxn = 3000;

int m, n, k;

pair <int, int> a[maxn];

inline int to(char c)
{
	if ('a' <= c && c <= 'z') return c - 'a' + 27;
	else return c - 'A' + 1;
}

inline char backto(int x)
{
	if (1 <= x && x <= 26) return x - 1 + 'A';
	else return x - 27 + 'a';
}

const int maxnode = 100;

int degree[maxnode];
bool G[maxnode][maxnode];

deque <int> ans;

void dfs(int now)
{
	REP(i, 1, 70)
		if (G[i][now])
		{
			G[i][now] = G[now][i] = 0;
			dfs(i);
		}
	ans.push_front(now);
}

int main()
{
#ifdef CraZYali
	freopen("1341.in", "r", stdin);
	freopen("1341.out", "w", stdout);
#endif
	cin >> n;
	REP(i, 1, n)
	{
		char s[5];
		scanf("%s", s + 1);
		a[i].first = to(s[1]);
		a[i].second = to(s[2]);
		G[a[i].first][a[i].second] = 1;
		G[a[i].second][a[i].first] = 1;
		degree[a[i].first]++;
		degree[a[i].second]++;
	}
	int pos = 0, cnt = 0;
	REP(i, 1, 70)
		cnt += degree[i] % 2 == 1;
	if (cnt && cnt ^ 2)
	{
		cout << "No Solution";
		return 0;
	}
	if (cnt)
		REP(i, 1, 70)
			if (degree[i] & 1)
			{
				pos = i;
				break;
			}
	if (!cnt)
		REP(i, 1, 70)
			if (degree[i])
			{
				pos = i;
				break;
			}
	dfs(pos);
	while (!ans.empty())
	{
		putchar(backto(ans.front()));
		ans.pop_front();
	}
	return 0;
}
