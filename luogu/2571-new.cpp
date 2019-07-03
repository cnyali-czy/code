#define  REP(i, s, e) for (int i = s; i <= e; i++)
#define DREP(i, s, e) for (int i = s; i >= e; i--)
#define DEBUG fprintf(stderr, "Passing [%s] in Line %d\n", __FUNCTION__, __LINE__)

#define chkmax(a, b) a = max(a, (b))
#define chkmin(a, b) a = min(a, (b))
#define dis(x1, y1, x2, y2) sqrt((x1 - x2) * (x1 - x2) + (y1 - y2) * (y1 - y2))

#include <algorithm>
#include <iostream>
#include <cstring>
#include <cstdlib>
#include <cstdio>
#include <cmath>
#include <queue>

using namespace std;
const int n = 50000;
const double Vmin = 5, Vmax = 500, Pmin = 0, Pmax = 1000, c1 = 15, c2 = 20, inf = 1e20, eps = 1e-8;

void file(string s)
{
	freopen((s + ".in").c_str(), "r", stdin);
	freopen((s + ".out").c_str(), "w", stdout);
}

pair <double, double> getpos(double x1, double y1, double x2, double y2, double len)
{
	double Len = dis(x1, y1, x2, y2);
	if (abs(Len) < eps) return make_pair(x1, y1);
	double l1 = len / Len * (x2 - x1);
	double l2 = len / Len * (y2 - y1);
	return make_pair(x1 + l1, y1 + l2);
}
double dist(pair <double, double> A, pair <double, double> B) {return dis(A.first, A.second, B.first, B.second);}

double Ax, Ay, Bx, By, Cx, Cy, Dx, Dy, P, Q, R;
double f(double AP, double QD)
{
	pair <double, double> _P = getpos(Ax, Ay, Bx, By, AP);
	pair <double, double> _Q = getpos(Dx, Dy, Cx, Cy, QD);
	return AP / P + dist(_P, _Q) / R + QD / Q;
}

double gbest_result = inf;
pair <double, double> gbest;

double Rnd() {return rand() * 1.0 / RAND_MAX;}
double AB, CD;

struct particle
{
	pair <double, double> pbest, cur, v;
	double w, pbest_result;
	void init()
	{
		pbest_result = inf;
		w = 10 * Rnd();
		v = make_pair(20 * Rnd(), 20 * Rnd());
		cur = make_pair(AB * (rand() % 10) / 10, CD * (rand() % 10) / 10);
	}
	void update()
	{
		double temp = f(cur.first, cur.second);
		//cout << cur.first << ' ' << cur.second << ' ' << temp << endl;
		if (temp < gbest_result)
		{
			pbest_result = gbest_result = temp;
			pbest = gbest = cur;
		}
		else if (temp < pbest_result)
		{
			pbest_result = temp;
			pbest = cur;
		}
		v.first = w * v.first + c1 * Rnd() * (pbest.first - cur.first) + c2 * Rnd() * (gbest.first - cur.first);
		v.second = w * v.second + c1 * Rnd() * (pbest.second - cur.second) + c2 * Rnd() * (gbest.second - cur.second);
		if (v.first < Vmin || v.first > Vmax) v.first *= -1;
		if (v.second < Vmin || v.second > Vmax) v.second *= -1;
		cur.first += v.first;
		cur.second += v.second;
		if (cur.first < 0 || cur.first > AB || cur.second < 0 || cur.second > CD) cur = make_pair((pbest.first + gbest.first) / 2, (pbest.second + gbest.second) / 2);
	}
}p[n + 5];

int main()
{
	srand((unsigned long long)new char);
#ifdef CraZYali
	file("2571");
#endif
	cin >> Ax >> Ay >> Bx >> By >> Cx >> Cy >> Dx >> Dy >> P >> Q >> R;
	AB = dis(Ax, Ay, Bx, By);
	CD = dis(Cx, Cy, Dx, Dy);
	REP(i, 1, n) p[i].init();
	int times = 100;
	while (times--)
		REP(i, 1, n) p[i].update();
	printf("%.2lf\n", gbest_result);
	return 0;
}
