/*
 * File Name:	3725.cpp
 * Author	:	CraZYali
 * Time		:	2020.01.27 14:33
 * Email	:	yms-chenziyang@outlook.com
 */

#define DEP(i, s, e) for (register int i(s), end_##i(e); i >= end_##i; i--)
#define REP(i, s, e) for (register int i(s), end_##i(e); i <= end_##i; i++)
#define DEBUG fprintf(stderr, "Passing [%s] in Line %d\n", __FUNCTION__, __LINE__)

#define chkmax(a, b) (a < (b) ? a = (b) : a) 
#define chkmin(a, b) (a > (b) ? a = (b) : a) 

#include <cstring>
#include <cmath>
#include <algorithm>
#include <iostream>
#include <cstdio>

using namespace std;
const int maxn = 1e6 + 10;

template <typename T> inline T read()
{
	T ans(0), flag(1);
	char c(getchar());
	while (!isdigit(c))
	{
		if (c == '-') flag = -1;
		c = getchar();
	}
	while (isdigit(c))
	{
		ans = ans * 10 + c - 48;
		c = getchar();
	}
	return ans * flag;
}

#define file(FILE_NAME) freopen(FILE_NAME".in", "r", stdin), freopen(FILE_NAME".out", "w", stdout);

int n, m, id[maxn];
typedef long long ll;
struct Vector
{
	ll x, y, id;
	inline Vector(ll x = 0, ll y = 0, ll id = 0) : x(x), y(y), id(id) {}
	inline Vector operator - (Vector B) {return Vector(x - B.x, y - B.y);}
	inline ll operator * (Vector B) {return x * B.y - y * B.x;}
	inline bool operator < (const Vector &B) const {return x < B.x;}
	inline double dis(Vector B) {return sqrt((x - B.x) * (x - B.x) + (y - B.y) * (y - B.y));}
}a[maxn], S, T;
int q[2][maxn], head[2], tail[2];
int dir[maxn], nd[maxn], pre[maxn];


int main()
{
#ifdef CraZYali
	file("3725");
#endif
	cin >> n >> T.x >> T.y;
	REP(i, 1, n)
	{
		ll x(read<ll>()), y(read<ll>());
		a[i] = Vector(x, y, i);
		double theta;scanf("%lf", &theta);
		double tol = atan2(-a[i].y, -a[i].x);
		double tor = atan2(T.y - a[i].y, T.x - a[i].x);
		if (tol < tor) dir[i] = (tol < theta && theta < tor);
		else dir[i] = !(tor < theta && theta < tol);
	}
	sort(a + 1, a + 1 + n);
	a[0] = S;
	REP(i, 1, n)
		if (a[i].x < T.x)
		{
			if (a[i].x > 0)
			{
				++m;
				a[m] = a[i];
				nd[m] = dir[a[i].id];
			}
		}
		else break;
	a[++m] = T;
	q[0][0] = q[1][0] = 1;
	DEP(i, m + 1, 1)
	{
		a[i] = a[i-1];
		nd[i] = nd[i-1];
	}
	m++;
	REP(i, 1, m)
	{
		int x = nd[i], &l0 = head[x], &r0 = tail[x], &l1 = head[!x], &r1 = tail[!x], *q0 = q[x], *q1 = q[!x], tg = (x ? -1 : 1);
		if (l1 < r1 && (a[i] - a[q1[l1]]) * (a[q1[l1+1]] - a[q1[l1]]) * tg >= 0)
		{
			while (l1 < r1 && (a[i] - a[q1[l1]]) * (a[q1[l1+1]] - a[q1[l1]]) * tg >= 0) l1++;
			pre[i] = q1[l1];
			q0[l0 = r0 = r0 + 1] = q1[l1];
		}
		else
		{
			while (l0 < r0 && (a[i] - a[q0[r0-1]]) * (a[q0[r0]] - a[q0[r0-1]]) * tg >= 0) r0--;
			pre[i] = q0[r0];
		}
		q0[++r0] = i;
	}
    double ans = 0;
    for (register int i = m; i ^ 1 ; i = pre[i]) ans += a[i].dis(a[pre[i]]);
	printf("%.9lf\n", ans);
	return 0;
}
