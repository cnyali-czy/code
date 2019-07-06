#define  REP(i, s, e) for (int i = s; i <= e; i++)
#define DREP(i, s, e) for (int i = s; i >= e; i--)
#define DEBUG fprintf(stderr, "Passing [%s] in Line %d\n", __FUNCTION__, __LINE__)

#define chkmax(a, b) a = max(a, b)
#define chkmin(a, b) a = min(a, b)

#include <cstdio>
#include <iostream>

using namespace std;
const int maxn = 50000 + 10, maxm = 10000 + 10, inf = 1e9;

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

int n, m, tot, qcnt;

struct Operate
{
	int type, x, y, pos, k, cur;
	Operate() : cur(0){}
	Operate(int _pos, int _x, int _type = 1) : pos(_pos), x(_x), type(_type), cur(0){}
	Operate(int _pos, int _x, int _y, int _k) : pos(_pos), x(_x), y(_y), k(_k), type(2), cur(0) {}
}q[maxn + maxm << 1], tempq[maxn + maxm << 1];
int ans[maxn];

int c[maxn];
void add(int x, int y = 1)
{
	while (x <= n)
	{
		c[x] += y;
		x += x & -x;
	}
}
int sum(int x)
{
	int y = 0;
	while (x > 0)
	{
		y += c[x];
		x -= x & -x;
	}
	return y;
}
int temp[maxn + maxm << 1];
bool mark[maxn + maxm << 1];

void solve(int l, int r, int L, int R)
{
	if (l > r) return;
	if (L == R)
	{
		REP(i, l, r)
			if (q[i].type == 2) ans[q[i].pos] = L;
		return;
	}
	int mid(L + R >> 1);
	REP(i, l, r)
		if (q[i].type == 1 && q[i].x <= mid) add(q[i].pos);
		else if (q[i].type == 3 && q[i].x <= mid) add(q[i].pos, -1);
		else if (q[i].type == 2) temp[i] = sum(q[i].y) - sum(q[i].x-1);
	REP(i, l, r)
		if (q[i].type == 1 && q[i].x <= mid) add(q[i].pos, -1);
		else if (q[i].type == 3 && q[i].x <= mid) add(q[i].pos);
	int tot(0);
	REP(i, l, r)
		if (q[i].type == 2)
			if (q[i].cur + temp[i] >= q[i].k) mark[i] = 1, ++tot;
			else mark[i] = 0, q[i].cur += temp[i];
		else
			if (q[i].x <= mid) mark[i] = 1, ++tot;
			else mark[i] = 0;
	int cur1(l), cur2(l + tot);
	REP(i, l, r)
		if (mark[i]) tempq[cur1++] = q[i];
		else tempq[cur2++] = q[i];
	REP(i, l, r) q[i] = tempq[i];
	solve(l, cur1 - 1, L, mid);
	solve(cur1, cur2 - 1, mid + 1, R);
}
int a[maxn];

int main()
{
#ifdef CraZYali
	freopen("A.in", "r", stdin);
	freopen("A.out", "w", stdout);
#endif
	int Case = read<int>();
	while (Case--)
	{
		tot = 0;
		REP(i, 1, qcnt) ans[i] = 0;
		qcnt = 0;
		n = read<int>();m = read<int>();
		REP(i, 1, n) q[++tot] = Operate(i, a[i] = read<int>());
		REP(i, n + 1, n + m)
		{
			char c = getchar();
			while (c != 'Q' && c != 'C') c = getchar();
			if (c == 'Q')
			{
				int l(read<int>()), r(read<int>()), k(read<int>());
				q[++tot] = Operate(++qcnt, l, r, k);
			}
			else
			{
				int pos(read<int>()), x(read<int>());
				q[++tot] = Operate(pos, a[pos], 3);
				q[++tot] = Operate(pos, x);
				a[pos] = x;
			}
		}
		solve(1, tot, -inf, inf);
		REP(i, 1, qcnt) printf("%d\n", ans[i]);
	}
	return 0;
}
