#define DREP(i, s, e) for(int i = s; i >= e ;i--)
#define  REP(i, s, e) for(int i = s; i <= e ;i++)

#define DEBUG fprintf(stderr, "Passing [%s] in Line %d\n", __FUNCTION__, __LINE__)
#define chkmax(a, b) a = max(a, b)
#define chkmin(a, b) a = min(a, b)

#include <bits/stdc++.h>

using namespace std;
const int maxn = 2e5 + 10, maxm = 2e5 + 10, inf = 1e9;

template <typename T> inline T read()
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

int n, m, a[maxn];

struct Question
{
	int type, pos, x, y, k;
	Question() {}
	Question(int _pos, int _x) : pos(_pos), x(_x), type(1) {}
	Question(int _pos, int _x, int _y, int _k) : pos(_pos), x(_x), y(_y), k(_k), type(2){}
}q[maxm + maxn], q1[maxn + maxn], q2[maxn + maxm];
int ans[maxm];

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

void solve(int l, int r, int L, int R)
{
	if (l > r) return;
	if (L == R)
	{
		REP(i, l, r) if (q[i].type == 2) ans[q[i].pos] = L;
		return;
	}
	int cur1(0), cur2(0);
	int mid = L + R >> 1;
	REP(i, l, r)
		if (q[i].type == 1)
			if (q[i].x <= mid)
			{
				add(q[i].pos);
				q1[++cur1] = q[i];
			}
			else q2[++cur2] = q[i];
		else
		{
			int temp = sum(q[i].y) - sum(q[i].x - 1);
			if (temp >= q[i].k) q1[++cur1] = q[i];
			else
			{
				q[i].k -= temp;
				q2[++cur2] = q[i];
			}
		}
	REP(i, 1, cur1) if (q1[i].type == 1) add(q1[i].pos, -1);
	REP(i, 1, cur1) q[l + i - 1] = q1[i];
	REP(i, 1, cur2) q[l + cur1 + i - 1] = q2[i];
	solve(l, l + cur1 - 1, L, mid);
	solve(l + cur1, r, mid + 1, R);
}

int main()
{
#ifdef CraZYali
	freopen("3834-new.in", "r", stdin);
	freopen("3834-new.out", "w", stdout);
#endif
	cin >> n >> m;
	REP(i, 1, n) q[i] = Question(i, read<int>());
	REP(i, n + 1, n + m)
	{
		int l(read<int>()), r(read<int>()), k(read<int>());
		q[i] = Question(i - n, l, r, k);
	}
	solve(1, n + m, -inf, inf);
	REP(i, 1, m) printf("%d\n", ans[i]);
	return 0;
}
