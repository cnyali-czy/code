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

using namespace std;
const int maxn = 100000 + 10;

void file(string s)
{
	freopen((s + ".in").c_str(), "r", stdin);
	freopen((s + ".out").c_str(), "w", stdout);
}

int n, d, k, x;
/*
   namespace violence
   {
   bitset <21> b[maxn];
   void work()
   {
   REP(i, 1, n)
   REP(j, 1, d)
   {
   scanf("%d", &x);
   x %= k;
   if (x * x % k) b[i].set(j);
   }
   REP(i, 1, n)
   REP(j, i+1, n)
   if ((b[id[i]] & b[id[j]]).count() % k == 0)
   {
   cout << b[id[i]] << '\n' << b[id[j]] << endl;
   printf("%d %d\n", min(id[i], id[j]), max(id[i], id[j]));
   return;
   }
   cout << -1 << endl;
   }
   }
 */
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
		int res = 0;
		REP(i, 1, d) res += x[i] * B.x[i];
		return res;
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
			int res = v[i] * s & 1;
			if (res ^ ((i-1) & 1))
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
