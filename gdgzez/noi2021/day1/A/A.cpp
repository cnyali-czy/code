/*
	Problem:	A.cpp
	Time:		2021-02-25 16:29
	Author:		CraZYali
	E-Mail:		yms-chenziyang@outlook.com 
*/

#define REP(i, s, e) for (register int i(s), end_##i(e); i <= end_##i; i++)
#define DEP(i, s, e) for (register int i(s), end_##i(e); i >= end_##i; i--)
#define DEBUG fprintf(stderr, "Passing [%s] in Line %d\n", __FUNCTION__, __LINE__)

#define chkmax(a, b) (a < (b) ? a = (b) : a)
#define chkmin(a, b) (a > (b) ? a = (b) : a)

#include <ctime>
#include <vector>
#include <algorithm>
#include <iostream>
#include <cstdio>
#define int long long

using namespace std;
const int maxn = 1e5 + 10;

	template <typename T>
inline T read()
{
	T ans = 0, flag = 1;
	char c = getchar();
	while (!isdigit(c))
	{
		if (c == '-') flag = -1;
		c = getchar();
	}
	while (isdigit(c))
	{
		ans = ans * 10 + (c - 48);
		c = getchar();
	}
	return ans * flag;
}

#define file(FILE_NAME) freopen(FILE_NAME".in", "r", stdin), freopen(FILE_NAME".out", "w", stdout)

#define vec pair <int, int>
#define x first
#define y second
#define y1 aajgljashjljghasdjkg
vec operator + (vec A, vec B) {return vec(A.x + B.x, A.y + B.y);}
vec operator - (vec A, vec B) {return vec(A.x - B.x, A.y - B.y);}

int n, q, x1[maxn], y1[maxn], x2[maxn], y2[maxn];

vec simp(vec v)
{
	int g = __gcd(v.x, v.y);
	v.x /= g;v.y /= g;
	if (v.x < 0) v.x = -v.x, v.y = -v.y;
	return v;
}
vec s[maxn], d[maxn];
const int B = 100, L = 1 - 1e4, R = 1e9 + 1e4, Per = (R - L + 1) / B;
vector <int> V[B * B + 5];

inline int left(int block)
{
	return L + (block - 1) * Per;
}
inline int right(int block)
{
	return left(block) + Per - 1;
}
inline int id(int x, int y)
{
	return (x - 1) * B + y;
}
inline int blg(int x)
{
	return (x - L) / Per + 1;
}
int operator * (vec A, vec B) {return A.x * B.y - A.y * B.x;}
const int inf = 1e18;

signed main()
{
#ifdef CraZYali
	file("A");
#endif
	cin >> n >> q;
	REP(i, 1, n)
	{
		scanf("%lld%lld%lld%lld", x1 + i, y1 + i, x2 + i, y2 + i);
		s[i] = vec(x1[i], y1[i]);
		d[i] = simp(vec(x2[i], y2[i]) - s[i]);
		int sx = s[i].x, dx = d[i].x, sy = s[i].y, dy = d[i].y;
		vector <pair <pair <double, double>, int > > X;
		REP(j, 1, B)
		{
			int lx = left(j), rx = right(j);
			double Lx = -inf, Rx = inf;
			if (dx)
			{
				Lx = 1. * (lx - sx) / dx;
				Rx = 1. * (rx - sx) / dx;
			}
			else if (!(lx <= sx && sx <= rx)) continue;
			X.emplace_back(make_pair(Lx, Rx), j);
		}
		sort(X.begin(), X.end());
		REP(k, 1, B)
		{
			int ly = left(k), ry = right(k);
			double Ly = -inf, Ry = inf;
			if (dy > 0)
			{
				Ly = 1. * (ly - sy) / dy;
				Ry = 1. * (ry - sy) / dy;
			}
			else if (dy < 0)
			{
				Ry = 1. * (ly - sy) / dy;
				Ly = 1. * (ry - sy) / dy;
			}
			else if (!(ly <= sy && sy <= ry)) continue;
			for (register auto j : X)
			{
				double Lx = j.first.first, Rx = j.first.second;
				if (Rx < Ly) continue;
				if (Ry < Lx) break;
				V[id(j.second, k)].emplace_back(i);
			}
		}
		if (i % 2000 == 0) cerr << i << endl;
	}
#ifdef CraZYali
	cerr << clock() * 1. / CLOCKS_PER_SEC << endl;
#endif
	REP(i, 1, q)
	{
		int x = read<int>(), y = read<int>();
		int ans = 0;
		for (register int i : V[id(blg(x), blg(y))])
		{
			vec qaq = vec(x, y) - s[i];
			if (qaq * d[i] == 0) ans++;
		}
		cout << ans << '\n';
	}
#ifdef CraZYali
	cerr << clock() * 1. / CLOCKS_PER_SEC << endl;
#endif
	return 0;
}
