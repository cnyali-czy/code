#define  REP(i, s, e) for(register int i = s; i <= e ;i++)
#define DREP(i, s, e) for(register int i = s; i >= e ;i--)

#define DEBUG fprintf(stderr, "Passing [%s] in LINE %d\n", __FUNCTION__, __LINE__)
#define chkmin(a, b) a = min(a, b)
#define chkmax(a, b) a = max(a, b)

#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>

using namespace std;

const int maxn = 1e5 + 10, maxm = 1e5 + 10, inf = 1e9;

int m, n, k;
long long a[maxn];
int p[maxn], aw[maxn];

__gnu_pbds::tree <int, int, less<int>, __gnu_pbds::rb_tree_tag, __gnu_pbds::tree_order_statistics_node_update> W, temp;
__gnu_pbds::tree <int, int, less<int>, __gnu_pbds::rb_tree_tag, __gnu_pbds::tree_order_statistics_node_update> :: iterator it;

inline bool chk(long long x)
{
	temp.clear();
	temp = W;
	REP(i, 1, n)
	{
		register long long hp = a[i];
		register int order = temp.order_of_key(hp + 1), atk;
		if (order) it = temp.find_by_order(temp.order_of_key(hp) - 1), atk = it -> first;
		else it = temp.lower_bound(a[i]), atk = it -> first;
		hp -= x * atk;
		if (hp == 0) goto ne;
		else if (hp > 0) return 0;
		else if ((-hp) % p[i]) return 0;
ne:		temp.insert(make_pair(aw[i], it -> second));
		temp.erase(it);
	}
	return 1;
}

inline long long gcd(long long a, long long b) {return !b ? a : gcd(b, a % b);}

inline void exgcd(long long a, long long b, long long &x, long long &y)
{
	if (!b) {x = 1;y = 0;}
	else {exgcd(b, a % b, y, x); y -= x * (a / b);}
}

int main()
{
	freopen("dragon.in", "r", stdin);
	freopen("dragon.out", "w", stdout);
	register int T;
	cin >> T;
	while (T --> 0)
	{
		scanf("%d%d", &n, &m);
		register bool n_is_one = (n == 1), m_is_one = (m == 1), p_is_one(1);
		REP(i, 1, n) scanf("%lld", a + i);
		REP(i, 1, n)
		{
			scanf("%d", p + i);
			if (p[i] ^ 1) p_is_one = 0;
		}
		REP(i, 1, n) scanf("%d", aw + i);
		if (m_is_one && p_is_one)
		{
			register int atk, ans(-1);
			scanf("%d", &atk);
			REP(i, 1, n)
			{
				chkmax(ans, (int)(a[i] / atk + (a[i] % atk == 0 ? 0 : 1)));
				atk = aw[i];
			}
			printf("%d\n", ans);
			continue;
		}
		if (n_is_one && m_is_one)
		{
			register long long atk;
			scanf("%lld", &atk);
			register long long g = gcd(atk, (long long)p[1]);
			if (a[1] % g)
			{
				printf("-1\n");
				continue;
			}
			register long long x, y;
			exgcd((long long)atk, (long long)p[1], x, y);
			x *= a[1] / g;
			y *= a[1] / g;
			//atk * x + p[1] * y = a[1]
			register long long temp = p[1] / g;

			if (x < 0)
			{
				register long long fff = (-x) / temp;
				x += fff * temp;
				while (x < 0) x += temp;
			}
			else
			{
				register long long fff = x / temp;
				x -= fff * temp;
				while (x - temp > 0) x -= temp;
			}
			printf("%lld\n", x);
			continue;
		}
		W.clear();
		REP(i, 1, m)
		{
			scanf("%d", &k);
			W.insert(make_pair(k, i));
		}
		register bool flag = 0;
		for (register long long i = 1; i <= 12345 ;i++)
			if (chk(i))
			{
				printf("%lld\n", i);
				flag = 1;
				break;
			}
		if (!flag) printf("-1\n");
	}
	return 0;
}
