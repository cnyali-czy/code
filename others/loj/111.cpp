#define DREP(i, s, e) for(int i = s; i >= e ;i--)
#define  REP(i, s, e) for(int i = s; i <= e ;i++)

#define DEBUG fprintf(stderr, "Passing [%s] in Line %d\n", __FUNCTION__, __LINE__)
#define chkmax(a, b) a = max(a, b)
#define chkmin(a, b) a = min(a, b)

#include <bits/extc++.h>

using namespace std;
const int maxn = 1.26e6 + 10;

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

int turn(char c)
{
	return c;
	if ('a' <= c && c <= 'z') return c - 'a';
	if ('A' <= c && c <= 'Z') return c - 'A' + 26;
	return c - '0' + 52;
}

const int siz = 125;
struct Node
{
	__gnu_pbds::gp_hash_table<int,Node *>ch;
	Node *ne;
	int Max, id, x;bool mark;
	Node(int _Max = 0, int _id = 0, int _x = 0) : x(_x), Max(_Max), id(_id), ne(NULL), mark(0) {ch.clear();}
}pool[maxn], *cur = pool;
int cnt = -1;
Node *newnode(int _Max = 0, int _id = 0)
{
	*cur = Node(_Max, _id, ++cnt);
	return cur++;
}

Node *start, *last;
void init() {start = last = newnode();}
Node *extend(char c, int id)
{
	Node *u = newnode(last -> Max + 1, id), *v = last;
	for (;v && !v -> ch[c];v = v -> ne) v -> ch[c] = u;
	if (!v) u -> ne = start;
	else if (v -> ch[c] -> Max == v -> Max + 1) u -> ne = v -> ch[c];
	else
	{
		Node *n = newnode(v -> Max + 1), *o = v -> ch[c];
		n -> ch = o -> ch;
		//		n -> id = o -> id;
		n -> ne = o -> ne;
		o -> ne = u -> ne = n;
		for (; v && v -> ch[c] == o; v = v -> ne) v -> ch[c] = n;
	}
	return last = u;
}

int n;
char s[1000000 + 10];
bitset <maxn> vis;
int top, c[siz+5], rk[maxn];

struct state{int x, y, z;}q[maxn];

vector <int> ne, to;

int bg[maxn], e;
void add(int x, int y)
{
	if (!e) ne.push_back(0), to.push_back(0);
	e++;
	to.push_back(y);
	ne.push_back(bg[x]);
	bg[x] = e;
}

void dfs(int x)
{
	if (pool[x].id) cout << pool[x].id << ' ';
	for(int i=bg[x];i;i=ne[i])
		dfs(to[i]);
}

int main()
{
#ifdef CraZYali
	freopen("111.in", "r", stdin);
	freopen("111.out", "w", stdout);
#endif
	scanf("%s", s + 1);
	n = strlen(s + 1);
	init();
	DREP(i, n, 1) extend(turn(s[i]), i);
	vis[0] = 1;
	REP(i, 1, cnt)
		if (pool[i].id && !vis[i])
		{
			Node temp = pool[i];
			for (int pos = n; !vis[temp.x]; vis[temp.x] = 1,temp = *temp.ne, --pos)
			{
				pos = pos - temp.Max + ((temp.ne == NULL) ? 0 : (*temp.ne).Max) + 1;
				q[++top] = (state){((temp.ne==NULL)?0:(*temp.ne).x),temp.x,turn(s[pos])};
				if(temp.ne==NULL)break;
			}
		}
	//REP(i,1,top)cout<<q[i].x<<' '<<q[i].y<<endl;
	REP(i, 1, top) c[q[i].z]++;
	REP(i, 1, siz) c[i] += c[i-1];
	DREP(i, top, 1) rk[c[q[i].z]--] = i;
	while(top) add(q[rk[top]].x, q[rk[top]].y),top--;
	dfs(0);
#ifndef ONLINE_JUDGE
#endif
	return 0;
}
