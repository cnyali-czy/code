#define  REP(i, s, e) for (int i(s), end_##i(e); i <= end_##i; i++)
#define DREP(i, s, e) for (int i(s), end_##i(e); i >= end_##i; i--)
#define DEBUG fprintf(stderr, "Passing [%s] in Line %d\n", __FUNCTION__, __LINE__)

#include <algorithm>
#include <iostream>
#include <cstring>
#include <cstdio>
#include <map>

using namespace std;
const int maxn = 8000 + 10;

int n, m, h[maxn], ans[maxn][maxn], vec[maxn][maxn], sta[maxn << 2];
map <int, int> id;
struct node
{
	int x, id;
	bool operator < (node B) const {return x < B.x;}
}a[maxn];

int main()
{
#ifdef CraZYali
	freopen("sequence.in", "r", stdin);
	freopen("sequence.out", "w", stdout);
#endif
	scanf("%d%d", &n, &m);
	REP(i, 1, n)
	{
		int x;
		scanf("%d", &x);
		a[i] = (node){x, i};
	}
	sort(a + 1, a + 1 + n);
	int cur(0);
	REP(i, 1, n)
	{
		if (a[i].x ^ a[i-1].x) cur++;
		id[a[i].x] = h[a[i].id] = cur;
	}
	REP(i, 1, n) vec[h[i]][++vec[h[i]][0]] = i;
	REP(i, 1, cur) vec[i][vec[i][0] + 1] = n + 1;
	ans[0][0] = n * (n + 1) / 2;
	REP(i, 1, cur)
	{
		int top(0);
		REP(j, 1, n) if (h[j] == i) sta[++top] = j;
		sta[top+1] = n + 1;
		REP(j, 0, top)
		{
			int x = sta[j + 1] - sta[j] - 1;
			ans[i][0] += x * (x + 1) / 2;
		}
		ans[0][i] = ans[i][0];
	}
	memset(sta, 0, sizeof sta);
	REP(i, 1, cur)
	{
		ans[i][i] = n * (n + 1) / 2;
		REP(j, i + 1, cur)
		{
			int sum(0), x(0), y(0), Max;
			if (vec[i][x + 1] > vec[j][y + 1])
			{
				Max = vec[j][++y];
				--sum;
			}
			else
			{
				Max = vec[i][++x];
				++sum;
			}
			sta[n] = Max;
			ans[i][j] = Max * (Max - 1) / 2;
			while (x < vec[i][0] || y < vec[j][0])
			{
				if (vec[i][x + 1] > vec[j][y + 1])
				{
					int tmp = vec[j][++y] - Max;
					ans[i][j] +=
						(tmp - 1) * tmp / 2 +
						tmp * sta[n + sum];
					sta[n + sum] +=	tmp;
					sum--;
					Max = vec[j][y];
					continue; 
				}
				++x;
				int tmp = vec[i][x] - Max;
				ans[i][j] +=
					(tmp - 1) * tmp / 2 +
					tmp * sta[n + sum];
				sta[n + sum] += tmp;
				sum++;
				Max = vec[i][x];
			}
			int tmp = n - Max + 1;
			ans[i][j] +=
				(tmp - 1) * tmp / 2 + 
				tmp * sta[sum + n];
			ans[j][i] = ans[i][j];
			REP(k, -vec[j][0], vec[i][0]) sta[k + n] = 0;
		}
	}
	while (m--)
	{
		int x, y;
		scanf("%d%d", &x, &y);
		printf("%d\n", ans[id[x]][id[y]]);
	}
	return 0;
}
