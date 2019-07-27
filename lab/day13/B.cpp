#define REP(i, s, e) for (int i = s; i <= e; i++)
#define DEBUG fprintf(stderr, "Passing [%s] in Line %d\n", __FUNCTION__, __LINE__)

#include <bits/stdc++.h>
#define int long long

using namespace std;
const int maxn = 3000 + 10;
const double eps = 1e-8, inf = 1e20;

bool same(double x, double y) {return fabs(x-y) < eps;}

int n, c[maxn], id[3][maxn];
struct Vector
{
	double x, y;
	Vector(double _x = 0, double _y = 0) : x(_x), y(_y){}
	inline Vector operator + (Vector B) {return Vector(x + B.x, y + B.y);}
	inline Vector operator - (Vector B) {return Vector(x - B.x, y - B.y);}
	inline Vector operator +=(Vector B) {return *this = *this + B;}
	inline Vector operator -=(Vector B) {return *this = *this - B;}
	inline double operator * (Vector B) {return x * B.y - B.x * y;}
	inline pair <pair <double, double>, double> operator & (Vector B)
	{
		if (same(x, B.x)) return make_pair(make_pair(233,666),inf-1);
		else return make_pair(make_pair((y - B.y) / (x - B.x), y - (y - B.y) / (x - B.x) * x), inf);
	}
	inline Vector operator ^ (double Theta)
	{
		double S = sin(Theta), C = cos(Theta);
		return Vector(x * C - y * S, y * C - x * S);
	}
	inline Vector operator ^= (double Theta) {return *this = *this ^ Theta;}
}p[maxn];
#define point Vector

bool judge(point A, point B, point C, point D)
{
	pair <pair <double, double>, double> res1;
	pair <pair <double, double>, double> res2;
	bool p1, p2;
	do
	{
		double Theta = rand();
		res1 = (A ^= Theta) & (B ^= Theta);	res2 = (C ^= Theta) & (D ^= Theta);
		p1 = !same(res1.second, inf);		p2 = !same(res2.second, inf);
	}while (p1 || p2);
	double k1 = res1.first.first, b1 = res1.first.second;
	double k2 = res2.first.first, b2 = res2.first.second;
	if (same(k1, k2)) return same(b1, b2);
	double x = (b2 - b1) / (k1 - k2), y = k1 * x + b1;
	return (A.x <= x + eps && x <= B.x + eps || B.x <= x + eps && x <= A.x + eps) && (C.x <= x + eps && x <= D.x + eps || D.x <= x + eps && x <= C.x + eps);
}
inline bool inside(Vector A, Vector u, Vector v, Vector w)
{
	return same(fabs((u-v) * (u-w)), fabs((A-u)*(A-v))+fabs((A-v)*(A-w))+fabs((A-w)*(A-u)));
}
int ans;

signed main()
{
#ifndef ONLINE_JUDGE
	freopen("B.in", "r", stdin);
	freopen("B.out", "w", stdout);
#endif
	srand(time(0));
	cin >> n;
	REP(i, 1, n)
	{
		double &x = p[i].x, &y = p[i].y;
		scanf("%lf%lf%lld", &x, &y, c + i);
		id[c[i]][++id[c[i]][0]] = i;
	}
	REP(i, 1, id[0][0])
		REP(j, 1, id[1][0])
		REP(k, 1, id[2][0])
		REP(u, 1, id[0][0])if(u^i)
		REP(v, 1, id[1][0])if(v^j)
		REP(w, 1, id[2][0])if(w^k)
		{
			bool flag = 1;
			point t[] = {p[id[0][i]], p[id[1][j]], p[id[2][k]], p[id[0][u]], p[id[1][v]], p[id[2][w]]};
#ifndef ONLINE_JUDGE
			puts("==============");
			printf("%c %c %c %c %c %c\n", -1+'A'+id[0][i], -1+'A'+id[1][j], -1+'A'+id[2][k], -1+'A'+id[0][u], -1+'A'+id[1][v], -1+'A'+id[2][w]);
#endif
			REP(A, 0, 2)
				if (inside(t[A], t[3], t[4], t[5]))
				{
#ifndef ONLINE_JUDGE
					cout << "Wrong on 1: " << A +1<< endl;
#endif
					flag = 0;goto ne;
				}
			REP(A, 3, 5)
				if (inside(t[A], t[0], t[1], t[2]))
				{
#ifndef ONLINE_JUDGE
					cout << "Wrong on 2: " << A +1<< endl;
#endif
					flag = 0;
					goto ne;
				}
			REP(A, 0, 1)
				REP(B, A+1, 2)
				REP(C, 3, 4)
				REP(D, C+1, 5)
				if (judge(t[A], t[B], t[C], t[D]))
				{
#ifndef ONLINE_JUDGE
					cout << "Wrong on 3: " << A +1<< ' ' << B+1 << ' ' << C +1<< ' ' << D+1 << ' '<<endl;
#endif
					flag = 0;goto ne;
				}
			ans++;
			ne:;
		}
	cout << ans / 2 << endl;
	return 0;
}
