//modify to learn

#define REP(i, s, e) for (int i = s; i <= e; i++)

#include <algorithm>
#include <iostream>
#include <cstring>
#include <cstdio>
#include <cmath>
using namespace std;
const int maxn = 3000 + 10;
const double pi = acos(-1), inf = 1e20;

int n;long long ans;
int cnt[2][3];
//cnt[0/1][x] 分割线左右的cnt
bool app[maxn];
//被搞过去几次

struct point
{
	int x, y, c, id;
	double k;

	bool operator < (point B) const {return k < B.k;}//极角排序
}P[maxn], p[maxn], O;

int main()
{
#ifndef ONLINE_JUDGE
	freopen("B.in", "r", stdin);
	freopen("B.out", "w", stdout);
#endif
	cin >> n;
	REP(i, 1, n) scanf("%d%d%d", &P[i].x, &P[i].y, &P[i].c), P[i].id = i;

	long long tmp;
	REP(i, 1, n)
	{
		O = P[i];
		int k = O.c;
		copy(P + 1, P + 1 + n, p + 1);
		int cur(0);
		REP(j, 1, n)
			if (i ^ p[j].id)
			{
				p[++cur]=p[j];
				p[cur].k = atan2(p[cur].y - O.y, p[cur].x - O.x);
				if (p[cur].k <= 0) p[cur].k += pi;
			}
		sort(p + 1, p + n);
		memset(cnt, 0, sizeof(cnt));
		memset(app, 0, sizeof(app));
		REP(j, 1, cur)
			if (p[j].y < O.y || p[j].y == O.y && p[j].x > O.x) ++cnt[0][p[j].c];//一开始下面
			else ++cnt[1][p[j].c], app[j] = 1;
		REP(j, 1, cur)
		{
			--cnt[app[j]][p[j].c];
			tmp = 1ll * (k ? cnt[0][0] : 1) * (p[j].c ? cnt[1][0] : 1) * ((k ^ 1) ? cnt[0][1] : 1) * ((p[j].c ^ 1) ? cnt[1][1] : 1) * ((k ^ 2) ? cnt[0][2] : 1) * ((p[j].c ^ 2) ? cnt[1][2] : 1);//大力统计颜色
			ans += tmp;
			tmp = 1ll * (k ? cnt[1][0] : 1) * (p[j].c ? cnt[0][0] : 1) * ((k ^ 1) ? cnt[1][1] : 1) * ((p[j].c ^ 1) ? cnt[0][1] : 1) * ((k ^ 2) ? cnt[1][2] : 1) * ((p[j].c ^ 2) ? cnt[0][2] : 1);
			ans += tmp;
			++cnt[app[j] ^= 1][p[j].c];
		}
	}
	cout << ans / 4 << endl;
	return 0;
}
