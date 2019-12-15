/*
 * File Name:	B.cpp
 * Author	:	CraZYali
 * Time		:	2019.12.15 10:26
 * Email	:	yms-chenziyang@outlook.com
 */

#define DEP(i, s, e) for (register int i(s), end_##i(e); i >= end_##i; i--)
#define REP(i, s, e) for (register int i(s), end_##i(e); i <= end_##i; i++)
#define DEBUG fprintf(stderr, "Passing [%s] in Line %d\n", __FUNCTION__, __LINE__)

#define chkmax(a, b) (a < (b) ? a = (b) : a) 
#define chkmin(a, b) (a > (b) ? a = (b) : a) 

#include <set>
#include <iostream>
#include <cstdio>
#include <cmath>

using namespace std;
const int maxn = 1e5 + 10;
const double sqrt3(sqrt(3)), pi(acos(-1)), COS(cos(pi/3)),SIN(sin(pi/3));
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

#define file(FILE_NAME) freopen(FILE_NAME".err", "w", stderr), freopen(FILE_NAME".in", "r", stdin), freopen(FILE_NAME".out", "w", stdout);

int n, q;

pair <double, double> rotate(double x, double y, double _x, double _y)
{
	return make_pair((x + _x - sqrt3 * (y - _y)) / 2, (y + _y + sqrt3 * (x - _x)) / 2);
	x -= _x;
	y -= _y;
	return make_pair(x * COS - y * SIN + _x, x * SIN + y * COS + _y);
}
pair <double, double> P[maxn];

struct node
{
	int l, r;
	double _x, _y;
	bool need;
	node(int l = 0, int r = 0, double _x = 0, double _y = 0, bool need = 1) : l(l), r(r), _x(_x), _y(_y), need(need) {}
	inline bool operator < (const node &B) const {return l < B.l;}
};
set <node> S;
using IT = set <node> :: iterator;
IT split(int pos)
{
	if (S.empty()) return S.end();
	auto it = S.lower_bound(node(pos));
	if (it != S.end() && it -> l == pos) return it;
	--it;
	int L(it -> l), R(it -> r);
	double _x(it -> _x), _y(it -> _y);
	bool need(it -> need);
	S.erase(it);
	if (L < pos) S.emplace(L, pos - 1, _x, _y, need);
	return pos <= R ? S.emplace(pos, R, _x, _y, need).first : S.end();
}
double c[2][maxn];
void add(double c[], int x, double val)
{
	while (x <= n)
	{
		c[x] += val;
		x += x & -x;
	}
}
double sum(double c[], int x)
{
	double res(0);
	while (x > 0)
	{
		res += c[x];
		x -= x & -x;
	}
	return res;
}
double sum(double c[], int l, int r) {return sum(c, r) - sum(c, l - 1);}
int main()
{
#ifdef CraZYali
	file("B");
#endif
	cin >> n >> q;
	S.emplace(1, n, 233, 666, 0);
	REP(i, 1, n)
	{
		double x, y;
		scanf("%lf%lf", &x, &y);
		P[i] = make_pair(x, y);
		add(c[0], i, x);
		add(c[1], i, y);
	}
	while (q--)
	{
		int l(read<int>()), r(read<int>());
		auto itr = split(r + 1), itl = split(l);
#ifdef NEEDDEBUG
		fprintf(stderr, "%d %d\n", l, r);
#endif
		auto itt = itl;
		while (itl != itr)
		{
			if (!itl -> need)
			{
				itl++;
				continue;
			}
#ifdef NEEDDEBUG
			fprintf(stderr, "need work %d %d\n", itl -> l, itl -> r);
#endif
			REP(i, itl -> l, itl -> r)
			{
				add(c[0], i, -P[i].first);
				add(c[1], i, -P[i].second);
				P[i] = rotate(P[i].first, P[i].second, itl -> _x, itl -> _y);
				add(c[0], i, P[i].first);
				add(c[1], i, P[i].second);
			}
			itl++;
		}
		S.erase(split(l), itr);
		double _x = sum(c[0], l, r) / (r - l + 1);
		double _y = sum(c[1], l, r) / (r - l + 1);
		printf("%.12lf %.12lf\n", _x, _y);
		S.emplace(node(l, r, _x, _y));
#ifdef NEEDDEBUG
		cerr << "emplace! " << ' ' << l << ' ' << r << endl;
		cerr <<"START!\n";
		for (auto i : S)
			fprintf(stderr, "%d %d %.2lf %.2lf %d\n", i.l, i.r, i._x, i._y, i.need);
		cerr << "END!\n";
		fputs("========\n", stderr);
#endif
	}
	for (auto it : S) if (it.need)
		REP(i, it.l, it.r)
		{
			add(c[0], i, -P[i].first);
			add(c[1], i, -P[i].second);
			P[i] = rotate(P[i].first, P[i].second, it._x, it._y);
			add(c[0], i, P[i].first);
			add(c[1], i, P[i].second);
		}
	REP(i, 1, n) printf("%.12lf %.12lf\n", P[i].first, P[i].second);
	return 0;
}
