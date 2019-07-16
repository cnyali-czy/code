#define REP(i, s, e) for (int i = s; i <= e ;i++)

#define chkmin(a, b) a = min(a, b)
#define chkmax(a, b) a = max(a, b)

#include <bits/stdc++.h>
#define double long double

using namespace std;
const int maxn = 3e5 + 10;
const double eps = 1e-4, pi = acos(-1), theta = pi / 3, S = sin(theta), C = cos(theta), inf = 1e10;

int n;
struct circle
{
	double x, y, r;
	int id;
	circle(){}
	circle(double _x, double _y, double _r, int _id) : x(_x), y(_y), r(_r), id(_id){}
	void update()
	{
		double xx(x), yy(y);
		x = xx * C - yy * S;
		y = xx * S + yy * C;
	}
}c[maxn], bg[maxn];
bool del[maxn];
struct square
{
	double x1, y1, x2, y2;//x1 <= x2, y1 <= y2
	int id;
	void init(circle c)
	{
		x1 = c.x - c.r;x2 = c.x + c.r;
		y1 = c.y - c.r;y2 = c.y + c.r;
		id = c.id;
	}
	void clear()
	{
		x1 = inf;x2 = -inf;
		y1 = inf;y2 = -inf;
		del[id] = 1;
	}
}t[maxn];
bool cmp1(circle A, circle B) {return A.x < B.x;}
bool cmp2(circle A, circle B) {return A.y < B.y;}
bool cmp3(circle A, circle B) {return abs(A.r - B.r) < eps ? A.id < B.id : A.r < B.r;}

int cur;
int root, ls[maxn], rs[maxn];
#define mid (l + r >> 1)
#define lson ls[p], l, mid
#define rson rs[p], mid + 1, r
void pushup(int p)
{
	if (!del[t[p].id]) t[p].init(bg[p]);
	else
	{
		t[p].x1 = inf;t[p].y1 = inf;
		t[p].x2 = -inf;t[p].y2 = -inf;
	}	
	int l = ls[p], r = rs[p];
	chkmin(t[p].x1, min(t[l].x1, t[r].x1));
	chkmin(t[p].y1, min(t[l].y1, t[r].y1));
	chkmax(t[p].x2, max(t[l].x2, t[r].x2));
	chkmax(t[p].y2, max(t[l].y2, t[r].y2));
}
void build(int &p, int l, int r, bool flag)
{
	if (flag)	nth_element(c + l, c + mid, c + r + 1, cmp1);
	else		nth_element(c + l, c + mid, c + r + 1, cmp2);
	t[p = ++cur].init(c[mid]);
	bg[p] = c[mid];
	if (l == r) return;
	build(lson, flag ^ 1);
	build(rson, flag ^ 1);
	pushup(p);
}

int main()
{
#ifndef ONLINE_JUDGE
	freopen("2586.in", "r", stdin);
	freopen("2586.out", "w", stdout);
#endif
	cin >> n;
	REP(i, 1, n)
	{
		double x, y, r;
		scanf("%LF%LF%LF", &x, &y, &r);
		c[i] = circle(x, y, r, i);
		c[i].update();
	}
	build(root, 1, n, 0);
	sort(c + 1, c + 1 + n, cmp3);
	return 0;
}
