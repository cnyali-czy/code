#define DREP(i, s, e) for(register int i = s; i >= e ;i--)
#define  REP(i, s, e) for(register int i = s; i <= e ;i++)

#define DEBUG fprintf(stderr, "Passing [%s] in Line %d\n", __FUNCTION__, __LINE__)
#define chkmax(a, b) a = max(a, b)
#define chkmin(a, b) a = min(a, b)

#include <bits/stdc++.h>

using namespace std;
const int maxn = 11, maxN = 4 << maxn, maxm = 40;

struct Graph
{
	int bg[maxN];
	vector <int> to, ne;
	void add(int x, int y)
	{
		if (to.empty()) to.push_back(0);
		to.push_back(y);
		if (ne.empty()) ne.push_back(0);
		ne.push_back(bg[x]);
		bg[x] = ne.size() - 1;
	}
}G1, G2;
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

int m, n, k;

map <string, int> M;
string S[4 << maxn];

int cnt = 0;
void dfs_s(int u, string now = "")
{
	if (u == n) M[S[++cnt] = now] = cnt;
	else
	{
		u++;
		REP(i, 1, 4)
		{
			register string SSS = now;
			SSS += (char)i + 'A' - 1;
			dfs_s(u, SSS);
		}
	}
}

pair <string, string> P[maxm];

int pre[maxN], low[maxN], dfs_clock;

stack <int> s;
bool vis[maxN];

int belong[maxN], scc_cnt;

void dfs(int u)
{
	pre[u] = low[u] = ++dfs_clock;
	s.push(u);
	vis[u] = 1;
	for (register int i = G1.bg[u]; i ; i = G1.ne[i])
		if (!pre[G1.to[i]])
		{
			dfs(G1.to[i]);
			chkmin(low[u], low[G1.to[i]]);
		}
		else if (vis[G1.to[i]]) chkmin(low[u], low[G1.to[i]]);
	if (pre[u] == low[u])
	{
		belong[u] = ++scc_cnt;
		vis[u] = 0;
		while (s.top() ^ u)
		{
			register int x = s.top();
			s.pop();
			belong[x] = scc_cnt;
			vis[x] = 0;
		}
		s.pop();
	}
}

int size[maxN];
bool G[maxN][maxN];

int in[maxN], A[maxN], dp[maxN]

;

queue <int> q;
int main()
{
#ifdef CraZYali
	freopen("string.in", "r", stdin);
	freopen("string.out", "w", stdout);
#endif

	ios::sync_with_stdio(false);
	cin >> n >> m;

	REP(i, 1, m) cin >> P[i].first >> P[i].second;

	dfs_s(0);

	REP(x, 1, cnt)
	{
		string now = S[x], s = now;

		REP(i, 1, n - 1)
			if (s[i-1] ^ s[i])
			{
				swap(s[i-1], s[i]);
				G1.add(M[now], M[s]);
				swap(s[i-1], s[i]);
			}

		REP(i, 1, m)
			if (P[i].first != P[i].second)
			{
				register int pos = -1;
				while (1)
				{
					pos = now.find(P[i].first, pos + 1);
					if (pos == string::npos) break;
					else
					{
						s = now;
						REP(j, pos, pos + P[i].first.size() - 1)
							s[j] = P[i].second[j - pos];
						if (now != s) G1.add(M[now], M[s]);
					}
				}
			}
	}

	REP(i, 1, cnt)
		if (!pre[i]) dfs(i);

	REP(i, 1, cnt) ++size[belong[i]];
	REP(x, 1, cnt)
		for (register int i = G1.bg[x]; i ; i = G1.ne[i])
			if (belong[x] ^ belong[G1.to[i]] && !G[belong[x]][belong[G1.to[i]]])
			{
				G[belong[x]][belong[G1.to[i]]] = 1;
				G2.add(belong[x], belong[G1.to[i]]);
				in[belong[G1.to[i]]]++;
			}

	REP(i, 1, scc_cnt)
		if (!in[i])
		{
			dp[i] = size[i];
			q.push(i);
		}

	register int now = 0;
	while (!q.empty())
	{
		register int x = q.front();
		A[++now] = x;
		q.pop();
		for (register int i = G2.bg[x]; i ; i = G2.ne[i])
			if (in[G2.to[i]])
			{
				in[G2.to[i]]--;
				if (!in[G2.to[i]]) q.push(G2.to[i]);
			}	
	}

	REP(i, 1, now)
	{

		register int x = A[i];
		for (register int i = G2.bg[x]; i ; i = G2.ne[i])
		{
			if (dp[G2.to[i]] < dp[x] + size[G2.to[i]])
				dp[G2.to[i]] = dp[x] + size[G2.to[i]];
		}
	}

	int Max = dp[1];
	REP(i, 2, scc_cnt) chkmax(Max, dp[i]);
	cout << Max;
	return 0;
}
