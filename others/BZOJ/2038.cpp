#define DREP(i, s, e) for(register int i = s; i >= e ;i--)
#define  REP(i, s, e) for(register int i = s; i <= e ;i++)

#define DEBUG fprintf(stderr, "Passing [%s] in Line %d\n", __FUNCTION__, __LINE__)
#define chkmax(a, b) a = max(a, b)
#define chkmin(a, b) a = min(a, b)

#include <bits/stdc++.h>
#define int long long
#define node pair<pair<int,int>,int > 

using namespace std;
const int maxn = 50000 + 10, maxm = 50000 + 10, maxsiz = 233;
int a[maxn];

template <typename T> inline T read()
{
	T ans(0), p(1);
	char c = getchar();
	while (!isdigit(c))
	{
		if (c == '-') p = -1;
		c = getchar();
	}
	while (isdigit(c))
	{
		ans = ans * 10 + c - 48;
		c = getchar();
	}
	return ans * p;
}

template <typename T> void write(T x)
{
	if (x < 0) putchar('-'), write(-x);
	else if (x / 10) write(x / 10);
	putchar(x % 10 + '0');
}
int gcd(int a, int b) {return b ? gcd(b, a % b) : a;}

int m, n, k;
node q[maxn];
bool cmp(node A, node B) {return A.first.first < B.first.first || A.first.first == B.first.first && A.first.second < B.first.second;}

int block_siz, block_cnt;
int belong[maxm], Left[maxsiz], Right[maxsiz];;

void init()
{
	block_siz = sqrt(m);
	register int l = 1, r = block_siz;
	while (l <= m)
	{
		r = r > m ? m : r;
		block_cnt++;
		Left[block_cnt] = l;Right[block_cnt] = r;
		REP(i, l, r) belong[i] = block_cnt;
		l += block_siz;r += block_siz;
	}
}

int cnt[maxn];bool vis[maxn];
pair <int, int> Ans[maxm];

signed main()
{
#ifdef CraZYali
	freopen("2038.in", "r", stdin);
	freopen("2038.out", "w", stdout);
#endif
	cin >> n >> m;
	REP(i, 1, n) a[i] = read<int>();
	REP(i, 1, m) q[i].first.first = read<int>(), q[i].first.second = read<int>(), q[i].second = i;
	sort(q + 1, q + 1 + m , cmp);
	init();

	REP(j, 1, block_cnt)
	{
		int lastl = 0, lastr = 0, ans = 0;
		register int l = q[Left[j]].first.first, r = q[Left[j]].first.second;
		REP(i, 1, n) cnt[i] = 0;
		REP(i, l, r) cnt[a[i]]++;
		REP(i, l, r) vis[a[i]] = 0;
		REP(i, l, r)
			if (!vis[a[i]])
			{
				ans += cnt[a[i]] * (cnt[a[i]]-1) / 2;
				vis[a[i]] = 1;
			}
		int g = gcd(ans, (r - l + 1) * (r - l) / 2);
		if (ans&&(r-l)&&(r-l+1)) Ans[q[Left[j]].second] = make_pair(ans / g, (r - l + 1) * (r - l) / 2 / g);
		else Ans[q[Left[j]].second] = make_pair(0, 1);
		lastl = l;
		lastr = r;
		REP(i, Left[j] + 1, Right[j])
		{
			l = q[i].first.first;r = q[i].first.second;
			while (lastl < l) ans -= --cnt[a[lastl++]];
			while (lastr < r) ans += cnt[a[++lastr]]++;
			while (lastr > r) ans -= --cnt[a[lastr--]];
			int g = gcd(ans, (r - l + 1) * (r - l) / 2);
			if (ans && (r-l)&&(r-l+1)) Ans[q[i].second] = make_pair(ans / g, (r - l + 1) * (r - l) / 2 / g);
			else Ans[q[i].second] = make_pair(0,1);
		}
	}
	REP(i, 1, m) printf("%lld/%lld\n", Ans[i].first, Ans[i].second);
	return 0;
}
