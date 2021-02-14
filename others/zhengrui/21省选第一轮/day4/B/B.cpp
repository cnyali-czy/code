#define REP(i, s, e) for (register int i(s), end_##i(e); i <= end_##i; i++)
#define DEP(i, s, e) for (register int i(s), end_##i(e); i >= end_##i; i--)

#include <iostream>
#include <cstdio>

using namespace std;
const int maxn = 3e5 + 10, D = 1e5;

struct
{
	int ls, rs, v, s, order;
}t[maxn];
#define v(x) t[x].v
#define s(x) t[x].s
#define ls(x) t[x].ls
#define rs(x) t[x].rs
#define order(x) t[x].order

int n, cur, rt;
inline int newnode(int val)
{
	++cur;
	ls(cur) = rs(cur) = 0;
	v(cur) = val;
	s(cur) = 1;
	order(cur) = rand();
	return cur;
}
void pushup(int x) {s(x) = s(ls(x)) + s(rs(x)) + 1;}
void merge(int &x, int a, int b)
{
	if (!a || !b) x = a | b;
	else
	{
		if (order(a) > order(b)) merge(ls(x = b), a, ls(b));
		else merge(rs(x = a), rs(a), b);
		pushup(x);
	}
}
void split(int x, int &a, int &b, int siz)
{
	if (!x) a = b = 0;
	else
	{
		if (s(ls(x)) >= siz) split(ls(b = x), a, ls(x), siz);
		else split(rs(a = x), rs(x), b, siz - s(ls(x)) - 1);
		pushup(x);
	}
}
void dfs(int x)
{
	if (ls(x)) dfs(ls(x));
	printf("%d ", v(x));
	if (rs(x)) dfs(rs(x));
}
int read() {int x;scanf("%d", &x);return x;}
int Q, k[maxn];
namespace bf_shit
{
	int T[1000005];
	bool i2[maxn];
	void work()
	{
		const int dd = 2e5 + 10;
		REP(i, -1e5, 1e5) merge(rt, rt, newnode(i << 1));
		int p = 0, q = 0;
		REP(i, 1, Q)
		{
			int opt = read();
			if (opt == 1)
			{
				int k = read() + p + q, id = (i << 1 | 1);

				int x = 0, y = 0, z = 0;
				split(rt, x, y, k - (-D));
				merge(x, x, newnode(id));
				merge(rt, x, y);

				/*
				split(rt, x, y, k - (-D) + 1);
				split(x, x, z, s(x) - 1);
				cerr << k << ' ' << v(z) << ' ' << id << endl;
				merge(x, x, z);
				merge(rt, x, y);
				*/
			}
			else if (opt == 2)
			{
				i2[i] = 1;
				k[i] = read() + p + q;
			}
			else
			{
				int qx = read() + p + q, qy = read() + p - q;
				int x = 0, y = 0, z = 0;
				split(rt, x, y, qy - (-D) + 1);
				split(x, x, z, s(x) - 1);
				q = v(z) >> 1;
//				cerr << "!" << ' ' << qy << ' ' << "q = " << ' ' << q << endl;
				merge(x, x, z);merge(rt, x, y);
				printf("%d %d\n", p = qx, q);
			}
		}
	}
}
namespace bf
{
	pair <int, int> a[205][205], b[205][205];
	void work()
	{
		REP(i, -100, 100) REP(j, -100, 100) a[i + 100][j + 100] = make_pair(i, j);
		int p = 0, q = 0;
		REP(Case, 1, Q)
		{
			int opt = read();
			if (opt == 1)
			{
				int k = read() + p + q;
				REP(i, -100, 100) REP(j, -100, 100)
				{
					if (j < k) b[i + 100][j + 100] = a[i + 100][j + 100];
					else if (j == k) b[i + 100][j + 100] = make_pair(i, Case);
					else b[i + 100][j + 100] = a[i + 100][j - 1 + 100];
				}
				swap(a, b);
			}
			else if (opt == 2)
			{
				int k = read() + p + q;
				REP(i, -100, 100) REP(j, -100, 100)
				{
					if (i < k) b[i + 100][j + 100] = a[i + 100][j + 100];
					else if (i == k) b[i + 100][j + 100] = make_pair(Case, j);
					else b[i + 100][j + 100] = a[i + 100 - 1][j + 100];
				}
				swap(a, b);
			}
			else
			{
				int qx = read() + p + q + 100, qy = read() + p - q + 100;
				cerr << qx - 100 << ' ' << qy - 100 << endl;
				printf("%d %d\n", p = a[qx][qy].first, q = a[qx][qy].second);
#ifdef CraZYali
				fflush(stdout);
#endif
			}
		}
	}
}

int main()
{
#ifdef CraZYali
	freopen("B.in", "r", stdin);
	freopen("B.out", "w", stdout);
#endif
	cin >> Q;
	if (Q <= 100) bf :: work();
	else bf_shit :: work();
	return 0;
}
