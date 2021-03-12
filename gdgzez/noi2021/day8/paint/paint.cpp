#define REP(i, s, e) for (register int i(s), end_##i(e); i <= end_##i; i++)
#define DEP(i, s, e) for (register int i(s), end_##i(e); i >= end_##i; i--)

#include <vector>
#include <algorithm>
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

bool gennew()
{
	REP(i, 1, n) mat[i] = 0;
	int cnt = 0;
	REP(i, 1, n * 5) if (cnt < n / 2)
	{
		vector <int> v;
		REP(i, 1, n) if (!mat[i]) v.emplace_back(i);
		REP(ccc,1,10)
		{
			int i = v[rand()%v.size()],j=v[rand()%v.size()];
			if(mat[i]||mat[j])continue;
			if(ok(i,j))
			{
				mat[i]=j;
				mat[j]=i;
				cnt++;
			}
		}
	}
	REP(i,1,n)if(!mat[i])return 0;
	return 1;
}

signed main()
{
	freopen("paint4.in", "r", stdin);
	freopen("paint4.out", "w", stdout);
	cin >> n;n <<= 1;
	srand(2333);
	REP(i, 1, n) scanf("%lld%lld", x + i, y + i), v[i] = Vec(x[i], y[i]);

	static int id[maxn];REP(i, 1, n) id[i] = i;
	const double pi = acos(-1);
	double thta = rand(), co = cos(thta), si = sin(thta);
	sort(id + 1, id + 1 + n, [&](int i, int j) {return co * x[i] + si * y[i] < co * x[j] + si * y[j];});

	double cur = 0, ans = 0;
	for (int i = 1; i + 1 <= n; i += 2)
	{
		mat[id[i]] = id[i + 1], mat[id[i + 1]] = id[i];
		cur += (v[id[i]] - v[id[i + 1]]).len();
	}
	ans = cur;

	int times = 1e9;
	srand(time(0));
	int cnt = n / 2;
	double T = 1044255960795.0821579
	;const double eps = 1e-9;
	while (T > eps)
	{
		if (rand() % 50 == 0)
		{
			int times = min(cnt, 100ll);
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
				if (ok(a, b) && (cur >= ans || exp((ans - cur) / T) < 1. * rand() / RAND_MAX))
				{
					mat[a] = b;
					mat[b] = a;
					cerr<<666<<endl;
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
				if (ok(a, b) && (cur >= ans || exp((ans - cur) / T) < 1. * rand() / RAND_MAX))// || cnt < n / 2 - st))
				{
					mat[a] = b;
					mat[b] = a;
					cnt++;
					cerr<<666<<endl;
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
				if (ok(a, b) && (cur >= ans || exp((ans - cur) / T) < 1. * rand() / RAND_MAX ))//|| cnt < n / 2 - st))
				{
					mat[a] = b;
					mat[b] = a;
					cnt++;
					cerr<<666<<endl;
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
		if (cnt == n / 2 && cur >= ans)
		{
			ans = cur;
			copy(mat, mat + n + 1, aat);
			cerr << Case << ' ' << cnt << ' '  << T << ' ' << cur << endl;
			system("rm fuck");FILE *tmp=fopen("fuck","w");
			if (cnt==n/2)
			{
				REP(i,1,n)fprintf(tmp,"%lld%c",mat[i],i==end_i?'\n':' ');
//				REP(i,1,n)cerr<<mat[i]<<' ';cerr<<endl<<endl;
			}
			fclose(tmp);
		}
		T *= .9999;
	}
	REP(i, 1, n) printf("%lld\n", aat[i]);
	return 0;
}
