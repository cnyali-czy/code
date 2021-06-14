#define  REP(i, s, e) for (int i = s; i <= e; i++)
#define DREP(i, s, e) for (int i = s; i >= e; i--)
#define DEBUG fprintf(stderr, "Passing [%s] in Line %d\n", __FUNCTION__, __LINE__)

#define chkmax(a, b) a = max(a, (b))
#define chkmin(a, b) a = min(a, (b))

#include <algorithm>
#include <iostream>
#include <cstring>
#include <cstdlib>
#include <bitset>
#include <cstdio>
#define i64 long long

using namespace std;
const int maxn = 100000 + 10;

void file(string s)
{
	freopen((s + ".in").c_str(), "r", stdin);
	freopen((s + ".out").c_str(), "w", stdout);
}

int n, d, k, x;
struct vector
{
	int *x;
	void init() {x = new int[d+5];}
	void clear() {REP(i, 1, d) x[i] = 0;}
	vector operator + (vector B)
	{
		vector C = *this;
		REP(i, 1, d) C.x[i] += B.x[i];
		return C;
	}
	vector operator += (vector B) {return *this = *this + B;}
	int operator * (vector B)
	{
		int sum = 0;
		REP(i, 1, d) sum += x[i] * B.x[i];
		return sum;
	}
}v[maxn], s;
namespace two
{
	void work()
	{
		REP(i, 1, n)
			REP(j, 1, d)
			{
				scanf("%d", v[i].x + j);
				v[i].x[j] &= 1;
			}
		REP(i, 1, n)
		{
			int sum = v[i] * s & 1;
			if (sum ^ ((i-1) & 1))
				REP(j, 1, i-1)
					if (v[i] * v[j] % 2 == 0)
					{
						cout << j << ' ' << i << endl;
						return;
					}
			s += v[i];
		}
		cout << -1 << endl;
	}
}
namespace three
{
	void work()
	{
		REP(i, 1, n)
			REP(j, 1, d)
			{
				scanf("%d", v[i].x + j);
				v[i].x[j] %= 3;
			}
		REP(i, 1, n)
		{
			i64 sum = 0;
			/*
			REP(j, 1, i - 1)
			{
				int x = 0;
				REP(l, 1, d) x += v[i].x[l] * v[j].x[l];
				sum += x * x;
			}*/
			static int s[105][105];
			REP(l1, 1, d) REP(l2, 1, d)
			{
				i64 res = s[l1][l2];
//				REP(j, 1, i - 1)
//					res += v[j].x[l1] * v[j].x[l2];
				(sum += res * v[i].x[l1] * v[i].x[l2]) %= 3;
			}
			if (sum % 3 != (i - 1) % 3)
				REP(j, 1, i - 1) if (v[i] * v[j] % 3 == 0)
				{
					printf("%d %d\n", j, i);
					return;
				}
			REP(l1, 1, d) REP(l2, 1, d)
				(s[l1][l2] += v[i].x[l1] * v[i].x[l2]) %= 3;
		}
		cout << -1 << endl;
	}
}

int main()
{
#ifdef CraZYali
	file("1224");
#endif
	cin >> n >> d >> k;
	REP(i, 1, n) v[i].init();
	s.init();s.clear();
	if (k == 2) two::work();
	else three::work();
	return 0;
}
