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
const int maxn = 100010;

template <typename T> T read()
{
	T ans(0), p(1);
	char c = getchar();
	while (!isdigit(c)) {
		if (c == '-') p = -1;
		c = getchar();
	}
	while (isdigit(c)) {
		ans = ans * 10 + c - 48;
		c = getchar();
	}
	return ans * p;
}
int m, n, k;

struct Graph
{
	int co[10][10];
}X;

#define node pair<Graph, vector <pair<pair<int, int>, int> > >

inline bool judge(node T)
{
	REP(i, 1, 5)
		REP(j, 1, 7)
			if (T.first.co[i][j]) return 0;
	return 1;
}

inline void out(node T)
{
	int siz = T.second.size() - 1;
	REP(i, 0, siz)
		printf("%d %d %d\n", T.second[i].first.first, T.second[i].first.second, T.second[i].second);
}

queue <pair<Graph, node> > q;

map <node, bool> vis;

inline void fall(node &T)
{
	REP(i, 1, 5)
		REP(j, 1, 7)
		{
			int cnt = 0;
			if (T.first.co[i][j]) T.first.co[i][++cnt] = T.first.co[i][j];
			while (cnt < 7)
			{
				cnt++;
				T.first.co[i][cnt] = 0;
			}
		}
}

bool mark[10][10];
inline int del(node &T)
{
	bool flag = 0;
	memset(mark, 0, sizeof(mark));
	REP(i, 1, 5)
		REP(j, 1, 5)
			if (T.first.co[i][j] == T.first.co[i][j + 1] && T.first.co[i][j + 1] == T.first.co[i][j + 2])
			{
				flag = 1;
				mark[i][j] = mark[i][j+1] = mark[i][j+2] = 1;
			}
	REP(i, 1, 3)
		REP(j, 1, 7)
			if (T.first.co[i][j] == T.first.co[i + 1][j] && T.first.co[i + 1][j] == T.first.co[i + 2][j])
			{
				flag = 1;
				mark[i][j] = mark[i+1][j] = mark[i+2][j] = 1;
			}
	if (!flag) return -1;
	else
	{
		fall(T);
		return 1;
	}
}

int main()
{
#ifdef CraZYali
	freopen("1312.in", "r", stdin);
	freopen("1312.out", "w", stdout);
#endif
	n = read<int>();
	REP(i, 1, 5)
	{
		int cnt = 0;
		while (1)
		{
			k = read<int>();
			if (!k) break;
			X.co[i][++cnt] = k;
		}
	}
	vector <pair<pair<int, int>, int> > emptyV;
	q.push(make_pair(X, emptyV));


	while (!q.empty())
	{
		node T = q.front();
		q.pop();
		if (vis[T] && T != make_pair(X, emptyV)) continue;
		else if (T.second.size() > n)
		{
			cout << -1;
			return 0;
		}
		vis[T] = 1;
		if (judge(T))
		{
			out(T);
			return 0;
		}
		REP(i, 1, 5)
			REP(j, 1, 7)
				if (!T.first.co[i][j]) break;
				else
				{
					if (i < 5 && T.first.co[i][j] ^ T.first.co[i+1][j])
					{
						node temp = T;
						swap(temp.first.co[i][j], temp.first.co[i+1][j]);
						fall(temp);
						while (1)
						{
							int re = del(T);
							if (re == -1) break;
						}
						temp.second.push_back(make_pair(make_pair(i, j), 1));
					}
					if (i > 1 && T.first.co[i][j] ^ T.first.co[i-1][j])
					{
						node temp = T;
						swap(temp.first.co[i][j], temp.first.co[i-1][j]);
						fall(temp);
						while (1)
						{
							register int re = del(T);
							if (re == -1) break;
						}
						temp.second.push_back(make_pair(make_pair(i, j), -1));
						q.push(temp);
					}
				}
	}
	cout << -1;
	return 0;
}
