#define REP(i, s, e) for (register int i(s), end_##i(e); i <= end_##i; i++)
#define DEP(i, s, e) for (register int i(s), end_##i(e); i >= end_##i; i--)

#include <cmath>
#include <iostream>
#include <cstdio>
#define int long long

using namespace std;
const int maxn = 1e5 + 10;

int n, x[maxn], y[maxn];
struct Vec
{
	int x, y;
	Vec() {}
	Vec(int x, int y) : x(x), y(y) {}
	Vec operator + (Vec B) {return Vec(x + B.x, y + B.y);}
	Vec operator - (Vec B) {return Vec(x - B.x, y - B.y);}
	int operator * (Vec B) {return x * B.y - y * B.x;}
	double len() {return sqrt((double)x * x + (double)y * y);}
}v[maxn];

bool gg(Vec s1, Vec t1, Vec s2, Vec t2)
{
	int r1 = (t1 - s1) * (s2 - s1), r2 = (t1 - s1) * (t2 - s1);
	if ((r1 > 0) == (r2 > 0)) return 0;
	swap(s1, s2);swap(t1, t2);
	r1 = (t1 - s1) * (s2 - s1), r2 = (t1 - s1) * (t2 - s1);
	if ((r1 > 0) == (r2 > 0)) return 0;
//	printf("ok (%lld, %lld) -> (%lld, %lld) (%lld, %lld) -> (%lld, %lld)\n", s1.x,s1.y,t1.x,t1.y,s2.x,s2.y,t2.x,t2.y);
	return 1;
}

int mat[maxn], aat[maxn];
bool ok(int i, int j)
{
	REP(k, 1, n) if (mat[k])
		if (gg(v[i], v[j], v[k], v[mat[k]])) return 0;
	return 1;
}
const double LIM = 500;

signed main()
{
	freopen("paint3.in", "r", stdin);
	freopen("paint3.out", "w", stdout);
	cin >> n;n <<= 1;
	REP(i, 1, n) scanf("%lld%lld", x + i, y + i), v[i] = Vec(x[i], y[i]);
	
	double cur = 0, ans = 0;
	int times = 1e9;
	srand(time(0));
	int cnt = 0, st = 10;
	double T = 400000000000.0;
	const double eps = 1e-5;
	while (T > eps)
	{
		if (rand() % 5000 == 0)
		{
			int times = min(cnt, 5ll);
			while(times--)
			{
				int x = rand()%n+1;
				if(!mat[x]){times++;continue;}
				cnt--;
				cur-=(v[x]-v[mat[x]]).len();
				mat[mat[x]]=0;mat[x]=0;
			}
		}
		int a = rand() % n + 1;
//		while (cnt < n / 2 - 50 && mat[a]) a = rand() % n + 1;
		if (!mat[a])
		{
			int b = rand() % n + 1;
			while (a == b) b = rand() % n + 1;
			if (!mat[b])
			{
				if (ok(a, b))
				{
					mat[a] = b;
					mat[b] = a;
					cur += (v[a] - v[b]).len();
					cnt++;
				}
			}
			else
			{
				int B = mat[b];
				mat[b] = mat[B] = 0;

				cur -= (v[b] - v[B]).len();
				cur += (v[a] - v[b]).len();
				if (ok(a, b) && (cur >= ans || exp((ans - cur) / T) > 1. * rand() / RAND_MAX || cnt < n / 2 - st))
				{
					mat[a] = b;
					mat[b] = a;
				}
				else
				{
					cur -= (v[a] - v[b]).len();
					mat[b] = B;mat[B] = b;
					cur += (v[b] - v[B]).len();
				}
			}
		}
		else
		{
			int A = mat[a];

			cnt--;cur -= (v[a] - v[A]).len();
			mat[a] = mat[A] = 0;

			int b = rand() % n + 1;
			while (b == a) b = rand() % n + 1;

			cur += (v[a] - v[b]).len();
			if (!mat[b])
			{
				if (ok(a, b) && (cur >= ans || exp((ans - cur) / T) > 1. * rand() / RAND_MAX || cnt < n / 2 - st))
				{
					mat[a] = b;
					mat[b] = a;
					cnt++;
				}
				else
				{
					cur -= (v[a] - v[b]).len();
					mat[a] = A;mat[A] = a;
					cnt++;cur += (v[a] - v[A]).len();
				}
			}
			else
			{
				int B = mat[b];

				cnt--;cur -= (v[b] - v[B]).len();
				mat[b] = mat[B] = 0;
				if (ok(a, b) && (cur >= ans || exp((ans - cur) / T) > 1. * rand() / RAND_MAX || cnt < n / 2 - st))
				{
					mat[a] = b;
					mat[b] = a;
					cnt++;
				}
				else
				{
					cnt += 2;
					cur -= (v[a] - v[b]).len();
					mat[a] = A;mat[A] = a;cur += (v[a] - v[A]).len();
					mat[b] = B;mat[B] = b;cur += (v[b] - v[B]).len();
				}
			}
		}
		static int Case = 0;Case++;
		if ((Case & 2047) == 0 && cnt < n / 2)
		{
			cerr << cnt << ' ' << cur << endl;
		}
		if (cnt == n / 2 && cur >= ans)
		{
			ans = cur;
			copy(mat, mat + n + 1, aat);
			cerr << Case << ' ' << T << ' ' << cur << endl;
			REP(i, 1, n) cerr << mat[i] << ' ' ;cerr << endl;
		}
		if (cnt >= n / 2 - 5) T *= .99999;
	}
	REP(i, 1, n) printf("%d\n", aat[i]);
	return 0;
}
