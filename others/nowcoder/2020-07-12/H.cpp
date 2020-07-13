#define  REP(i, s, e) for (register int i = s; i <= e; i++)
#define DREP(i, s, e) for (register int i = s; i >= e; i--)
#define DEBUG fprintf(stderr, "Passing [%s] in Line %d\n", __FUNCTION__, __LINE__)

#define chkmax(a, b) a = max(a, b)
#define chkmin(a, b) a = min(a, b)

#include <bits/stdc++.h>
using namespace std;
const int maxn = 60 + 5, maxm = 100 + 10, inf = 1e9;

#define int __int128
struct Int
{
	int x, y;
	Int(int xx = 0, int yy = 1) 
	{
		x = xx;y = yy;
		int g = __gcd(x, y);
		x /= g;y /= g;
	}
	inline Int operator + (Int B)
	{
		return Int(x * B.y + B.x * y, y * B.y);
	}
	inline Int operator - (Int B)
	{
		return Int(x * B.y - B.x * y, y * B.y);
	}
	inline Int operator +=(Int B) {return *this = *this + B;}
	inline Int operator -=(Int B) {return *this = *this - B;}
	inline Int operator * (Int B)
	{
		return Int(x * B.x, y * B.y);
	}
	inline Int operator / (Int B)
	{
		return Int(x * B.y, y * B.x);
	}
	inline bool operator < (const Int &B) const
	{
		return x * B.y < B.x * y;
	}
	inline bool operator > (const Int &B) const
	{
		return B < *this;
	}
};
#undef int
int bg[maxn], ne[maxm << 1], to[maxm << 1], cost[maxm << 1], e = 1;
int w[maxm << 1];
inline void add(int x, int y, int z, int c)
{
	e++;
	to[e] = y;
	ne[e] = bg[x];
	bg[x] = e;
	w[e] = z;
	cost[e] = c;
}

template <typename T> T read()
{
	T ans = 0, p = 1;
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

int n, m, S, T, Q;

int dis[maxn], pre[maxn];bool vis[maxn];
int Max[maxn];
queue <int> q;

bool spfa()
{
	REP(i, 1, n + 1) vis[i] = 0, dis[i] = inf;
	dis[S] = 0;Max[S] = inf;
	q.push(S);
	while (!q.empty())
	{
		register int x = q.front();vis[x] = 0;q.pop();
		for (register int i = bg[x]; i ; i = ne[i])
			if (w[i] > 0 && dis[to[i]] > dis[x] + cost[i])
			{
				dis[to[i]] = dis[x] + cost[i];
				if (x == S) Max[to[i]] = w[i];
				else Max[to[i]] = min(Max[x], w[i]);
				pre[to[i]] = i;
				if (!vis[to[i]])
				{
					vis[to[i]] = 1;
					q.push(to[i]);
				}
			}
	}
	return dis[T] != inf;
}

long long int max_flow, jjs;
void update()
{
	jjs += Max[T];
	max_flow = max_flow + 1ll * Max[T] * dis[T];
	register int x = T;
	while (x ^ S)
	{
		w[pre[x]] -= Max[T];
		w[pre[x] ^ 1] += Max[T];
		x = to[pre[x] ^ 1];
	}
}
Int ans[100005];
bool IsNan[100005];
int X[10005], Y[10005], C[10005];
long long mem[110];

void rebuild()
{
	max_flow = 0;jjs = 0;
	REP(i, 1, n + 1) bg[i] = 0;e = 1;
	REP(i, 1, m)
	{
		int x = X[i], y = Y[i], c = C[i];
		add(x, y, 1, c);
		add(y, x, 0, -c);
	}
	add(S, 1, 0, 0);
	add(1, S, 0, 0);
}

signed main()
{
#ifdef CraZYali
	freopen("H.in", "r", stdin);
	freopen("H.out", "w", stdout);
#endif
	/*
	   cin >> n >> m >> S >> T;
	   while (m --> 0)
	   {
	   register int x, y, z, c;
	   x = read<int>();y = read<int>();z = read<int>();c = read<int>();
	   add(x, y, z, c);
	   add(y, x, 0, -c);
	   }
	   while (spfa()) update();
	   cout << max_flow <<  ' ' << min_cost << endl;
	   */
	while (scanf("%d%d", &n, &m) != EOF)
	{
		REP(i, 1, n + 1) bg[i] = 0;e = 1;
		REP(i, 1, m)
		{
			int x(read<int>()), y(read<int>()), c(read<int>());
			X[i] = x;Y[i] = y;C[i] = c;
			add(x, y, 1, c);
			add(y, x, 0, -c);
		}
		S = n + 1;T = n;
		int qaq = e + 1;
		add(S, 1, 10000, 0);
		add(1, S, 0, 0);
		max_flow = 0;jjs = 0;
		while (spfa()) update();
		long long int JJS = jjs;
		rebuild();
		REP(i, 1, 105)
		{
			w[qaq]++;
			while (spfa()) update();
			mem[i] = max_flow;
		}
		/*
		   Int last = 0;
		   REP(i, 1, Q)
		   {
		   IsNan[i] = 0;
		   if (Qry[i].first > JJS)
		   {
		   IsNan[i] = 1;
		   continue;
		   }
		   Int delta = Qry[i].first - last;
		   last = Qry[i].first;
		   w[qaq] += delta;
		   while (spfa())
		   {
		   update();
		//			cerr << Max[T].x << ' '<< Max[T].y<<endl;
		}
		if (w[qaq] > 0) IsNan[Qry[i].second] = 1;
		else ans[Qry[i].second] = max_flow / Qry[i].first;
		}
		REP(i, 1, Q)
		{
		if (IsNan[i]) puts("NaN");
		else
		{
		int g = __gcd(ans[i].x, ans[i].y);
		printf("%lld/%lld\n", (long long)(ans[i].x / g), (long long)(ans[i].y / g));
		}
		}
		*/
		Q = read<int>();
		REP(i, 1, Q)
		{
			int u = read<int>(), v = read<int>(), g = __gcd(u, v);
			u /= g;v /= g;
			if (1ll * v > 1ll * JJS * u) puts("NaN");
			else
			{
				int x = floor(1. * v / u), y = ceil(1. * v / u);
				//				cerr << x << ' ' << y << endl;
				int w1 = mem[x], w2 = mem[y];
//				Int ans = (Int(v, u) - x) * (w2 - w1) + w1;
//				ans = ans / Int(v, u);
				int g = 1;//__gcd(ans.x, ans.y);
				Int ans = Int((v - (__int128)u * x) * (w1 - w1) + 1ll * w1 * u, v)
				printf("%lld/%lld\n", (long long)(ans.x / g), (long long)(ans.y / g));
			}
		}
	}
	return 0;
}
