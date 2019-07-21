#define  REP(i, s, e) for (int i = s; i <= e; i++)
#define DREP(i, s, e) for (int i = s; i >= e; i--)
#define DEBUG fprintf(stderr, "Passing [%s] in Line %d\n", __FUNCTION__, __LINE__)

#define chkmax(a, b) a = max(a, b)
#define chkmin(a, b) a = min(a, b)

#include <bits/stdc++.h>

using namespace std;
const int maxlen = 1e6 + 10, maxN = 100 + 5, maxn = 5e6;

char s[maxlen];
int len;

int fail[maxn], ch[maxn][26], rt, cur;
vector <int> End[maxn];

void insert(int &now, int pos, int id, int st)
{
	if (!now) now = ++cur;
	if (pos < st + len - 1) insert(ch[now][s[pos+1] - 'a'], pos + 1, id, st);
	else End[now].push_back(id);
}
void insert(int id)
{
	scanf("%s", s + 1);
	int Len = strlen(s + 1);
	REP(i, 1, Len - len + 1) insert(ch[rt][s[i]-'a'], i, id, i);
}

int q[maxn], head, tail;
void build()
{
	head = 1;tail = 0;
	REP(i, 0, 25)
		if (ch[1][i])
			fail[q[++tail] = ch[1][i]] = 1;
	while (head <= tail)
	{
		int x = q[head++];
		REP(i, 0, 25)
			if (ch[x][i]) fail[q[++tail] = ch[x][i]] = ch[fail[x]][i];
			else ch[x][i] = ch[fail[x]][i];
	}
}
int ans[maxn];
bool vis[maxn];
vector <int> clr;
string ss;
void query()
{
	int now = rt;
	REP(i, 0, len-1)
	{
		now = ch[now][ss[i]-'a'];
		for (int x = now; x && !vis[x]; x = fail[x])
		{
			vis[x] = 1;
			int siz = (int)End[x].size() - 1;
			REP(j, 0, siz) ans[End[x][j]]++;
			clr.push_back(x);
		}
	}
	int siz = (int)clr.size()-1;
	REP(i, 0, siz) vis[clr[i]] = 0;
}

int n;
unordered_map <string, bool> Vis;

int main()
{
#ifndef ONLINE_JUDGE
	freopen("B.in", "r", stdin);
	freopen("B.out", "w", stdout);
#endif
	cin >> ss;
	len = ss.size();
	cin >> n;
	REP(i, 1, n) insert(i);
	build();
	len = ss.size();
	REP(i, 0, len - 1)
	{
		ss = ss[len-1] + ss;
		ss.erase(--ss.end());
		if (!Vis[ss])
		{
			Vis[ss] = 1;
			query();
		}
	}
	REP(i, 1, n) printf("%d\n", ans[i]);
	return 0;
}
