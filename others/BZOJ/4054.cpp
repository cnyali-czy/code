#define  REP(i, s, e) for (int i = s; i <= e; i++)
#define DREP(i, s, e) for (int i = s; i >= e; i--)
#define DEBUG fprintf(stderr, "Passing [%s] in Line %d\n", __FUNCTION__, __LINE__)

#define chkmax(a, b) a = max(a, (b))
#define chkmin(a, b) a = min(a, (b))

#include <bits/extc++.h>
#define int long long
using namespace std;
const int maxn = 2e5 + 10, maxm = maxn, inf = 9999999999999999ll;

int bg[maxn], ne[maxm << 1], to[maxm << 1], e;
void add(int x, int y)
{
	e++;
	to[e] = y;
	ne[e] = bg[x];
	bg[x] = e;
}

template <typename T> T read()
{
	T ans(0), flag(1);
	char c(getchar());
	while (!isdigit(c))
	{
		if (c == '-') flag = -1;
		c = getchar();
	}
	while (isdigit(c))
	{
		ans = ans * 10 + c - 48;
		c = getchar();
	}
	return ans * flag;
}

void file(string s)
{
	freopen((s + ".in").c_str(), "r", stdin);
	freopen((s + ".out").c_str(), "w", stdout);
}

int n, End, delta[maxn];

struct node
{
	int x, y;
	bool operator < (node B) const {return x > B.x;}
};
__gnu_pbds::priority_queue <node> q[maxn];

void dfs(int x, int fa = -1)
{
	while (!q[x].empty()) q[x].pop();
	if (x == End)
	{
		q[x].push((node){max(0ll, -delta[x]), inf});
		return;
	}
	for (int i = bg[x]; i ; i = ne[i])
		if (to[i] ^ fa)
		{
			dfs(to[i], x);
			q[x].join(q[to[i]]);
		}
	if (delta[x] < 0)
	{
		node temp = (node){-delta[x], 0};
		while (!q[x].empty() && (temp.x > q[x].top().x || temp.x >= temp.y))
		{
			if (temp.y >= q[x].top().x) temp.y -= q[x].top().x - q[x].top().y;
			else
			{
				temp.x += q[x].top().x - temp.y;
				temp.y = q[x].top().y;
			}
			q[x].pop();
		}
#ifdef CraZYali
		cout << temp.x << ' ' << temp.y << endl;
#endif
		if (temp.x < temp.y) q[x].push(temp);
		else 
			while (!q[x].empty()) q[x].pop();
	}
	else
	{
		int sum = delta[x];
		while (!q[x].empty() && q[x].top().x <= sum)
		{
			sum += q[x].top().y - q[x].top().x;
			q[x].pop();
		}
#ifdef CraZYali
		cout << sum << endl;
#endif
		q[x].push((node){0ll, sum});
	}
}

signed main()
{
#ifdef CraZYali
	file("4054");
#endif
	int T = read<int>();
	while (T--)
	{
		n = read<int>();End = read<int>();
		REP(i, 1, n) delta[i] = read<int>();
		REP(i, 1, n) bg[i] = 0;e = 0;
		REP(i, 2, n)
		{
			int x(read<int>()), y(read<int>());
			add(x, y);add(y, x);
		}
		dfs(1);
#ifdef CraZYali
		cout << q[1].top().x << ' '<<q[1].top().y<<endl;
#endif
		puts(q[1].top().y > 999999999999ll ? "escaped" : "trapped");
	}
	return 0;
}
