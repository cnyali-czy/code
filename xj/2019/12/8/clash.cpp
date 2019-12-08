#define  REP(i, s, e) for (register int i(s), end_##i(e); i <= end_##i; i++)
#define DREP(i, s, e) for (register int i(s), end_##i(e); i >= end_##i; i--)
#define DEBUG fprintf(stderr, "Passing [%s] in Line %d\n", __FUNCTION__, __LINE__)

#include <algorithm>
#include <iostream>
#include <cstdio>
#include <set>

using namespace std;
const int maxn = 1e5 + 10, maxm = maxn, maxk = 50 + 5;

struct Vector
{
	int x, y;
	inline Vector(int x, int y) : x(x), y(y) {}
	inline Vector(int x1, int y1, int x2, int y2) : x(x2 - x1), y(y2 - y1) {}
	inline long long operator * (Vector B) {return x * B.y - B.x * y;}
};

int n, k, m, op;
int x[maxn], y[maxn], a[maxk], b[maxk], c[maxk];

bool Protected(int X, int Y, int a, int b, int c, int x, int y)
{
	if (y < c) return 0;
	long long tmp1(Vector(X, Y, a, c) * Vector(X, Y, x, y));
	long long tmp2(Vector(X, Y, b, c) * Vector(X, Y, x, y));
	return tmp1 <= 0 && tmp2 >= 0;
}

namespace bf
{
	void work()
	{
		while (m--)
		{
			int X, Y, res(0);
			scanf("%d%d", &X, &Y);
			REP(i, 1, n)
			{
				bool flag = 1;
				REP(j, 1, k) 
					if (Protected(X, Y, a[j], b[j], c[j], x[i], y[i]))
					{
						flag = 0;
						break;
					}
//				if (flag) printf("(%d, %d) can shoot (%d, %d)\n", X, Y, x[i], y[i]);
				res += flag;
			}
			printf("%d\n", res);
		}
	}
}
namespace cheat
{
	int sum[maxn];
	inline void add(int x, int val = 1)
	{
		while (x <= m)
		{
			sum[x] += val;
			x += x & -x;
		}
	}
	inline void update(int l, int r)
	{
		add(l);
		add(r + 1, -1);
	}
	inline int query(int x)
	{
		int res(0);
		while (x > 0)
		{
			res += sum[x];
			x -= x & -x;
		}
		return res;
	}
	int askx[maxm], asky[maxm], id[maxm];
	struct node
	{
		int l, r, v;
		node(int l = 0, int r = 0, int v = 0) : l(l), r(r), v(v) {}
		inline bool operator < (const node &B) const {return l < B.l;}
	};
	set <node> s;
	using IT = set <node> :: iterator;
	IT split(int pos)
	{
		auto it = s.lower_bound(node(pos));
		if (it != s.end() && it -> l == pos) return it;
		--it;
		int L(it -> l), R(it -> r), v(it -> v);
		s.erase(it);
		if (L < pos) s.emplace(L, pos - 1, v);
		return pos <= R ? s.emplace(pos, R, v).first : s.end();
	}
	inline void assign(int l, int r)
	{
		auto itr = split(r+1), itl = split(l);
		s.erase(itl, itr);
		s.emplace(l, r, 0);
	}
	pair <double, double> calc(int x1, int y1, int x2, int y2)
	{
		double k = (y1 - y2) * 1. / (x1 - x2);
		double b = y1 - x1 * k;
		return make_pair(k, b);
	}
	double getx(double k, double b, double y)
	{
		return (y - b) / k;
	}
	int back[maxm];
	inline void work()
	{
		REP(i, 1, m)
		{
			id[i] = i;
			scanf("%d%d", askx + i, asky + i);
		}
		sort(id + 1, id + 1 + m, [&](int A, int B) {return askx[A] < askx[B];});
		REP(i, 1, n) back[id[i]] = i;
		REP(i, 1, n)
		{
			s.clear();
			s.emplace(1, m, 1);
			REP(j, 1, k) if (y[i] > c[j])
			{
				double l, r;
				if (x[i] == a[j]) l = x[i];
				else
				{
					pair <double, double> qaq = calc(x[i], y[i], a[j], c[j]);
					l = getx(qaq.first, qaq.second, asky[1]);
				}
				if (x[i] == b[j]) r = x[i];
				else
				{
					pair <double, double> qaq = calc(x[i], y[i], b[j], c[j]);
					r = getx(qaq.first, qaq.second, asky[1]);
				}
				if (l > r) swap(l, r);
				int qaq1(0), qaq2(m+1);
				int L(1), R(m);
				while (L <= R)
				{
					int mid = L + R >> 1;
					if (askx[id[mid]] < l)
					{
						qaq1 = mid;
						L = mid + 1;
					}
					else R = mid - 1;
				}
				L = 1;R = m;
				while (L <= R)
				{
					int mid = L + R >> 1;
					if (askx[id[mid]] > r)
					{
						qaq2 = mid;
						R = mid - 1;
					}
					else L = mid + 1;
				}
#ifdef DDEBUG
				printf("i = %d j = %d\n(l, r) = (%.2lf, %.2lf)\n [1, %d] and [%d, %d] is good\n", i, j, l,r,qaq1, qaq2, m);
#endif
				if (qaq1 + 1 <= qaq2 - 1)
				{
					assign(qaq1 + 1, qaq2 - 1);
#ifdef DDEBUG
					printf("clear : %d %d\n", qaq1 + 1, qaq2 - 1);
#endif
				}
			}
			for (auto it : s)
				if (it.v && it.l <= it.r)
				{
#ifdef DDEBUG
					cout << "i = " << i << " and good : " << it.l << ' ' << it.r << endl;
#endif
					//	REP(i, it.l, it.r) ans[i]++;
					update(it.l, it.r);
				}
		}
		REP(i, 1, m) printf("%d\n", query(back[i]));
	}
}
int main()
{
#ifdef CraZYali
	freopen("clash.in", "r", stdin);
	freopen("clash.out", "w", stdout);
#endif
	cin >> n >> k >> m >> op;
	REP(i, 1, n) scanf("%d%d", x + i, y + i);
	REP(i, 1, k) scanf("%d%d%d", a + i, b + i, c + i);
	if (n <= 2000 && m <= 2000) bf::work();
	else cheat::work();
	return 0;
}
