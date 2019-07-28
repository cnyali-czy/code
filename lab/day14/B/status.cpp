#define REP(i, s, e) for (int i = s; i <= e; i++)

#include <bits/stdc++.h>
using namespace std;
const int maxn = 500 + 5, maxm = 1000 + 5, maxk = 3e6;

int n, m;
char s[maxn][maxm];

int read()
{
	int ans(0), flag(1);
	char c = getchar();
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

int u, v, w, x;
int a[maxn][maxm], b[maxn][maxm];

bool vis[maxn][maxm];

int key, pro;

int main()
{
	freopen("tower3.in", "r", stdin);
	int z;
	cin >> n >> m;
	REP(i, 1, n) scanf("%s", s[i] + 1);
	while ((u = read()) + (v = read()) + (w = read())) a[u][v] = w;
	while ((u = read()) + (v = read()) + (w = read())) a[u][v] = w;
	while ((u = read()) + (v = read()) + (w = read()) + (z = read())) a[u][v] = w, b[u][v] = z;
	int hp = read();
	freopen("tower3.out", "r", stdin);
	freopen("status","w",stdout);
	int k;cin >> k;
	int x,y;
	REP(i,1,n)
		REP(j,1,m)
		if(s[i][j]=='P'){x=i,y=j;break;}
	vis[x][y]=1;
	while(k--)
	{
		int tx(read()),ty(read());
		if (!vis[tx][ty])
		{
			if(s[tx][ty]=='H')hp+=a[tx][ty];
			else if(s[tx][ty]=='M')hp -= max(0, b[tx][ty]-pro)*a[tx][ty];
			else if(s[tx][ty]=='K')key++;
			else if(s[tx][ty]=='D')key--;
			else if(s[tx][ty]=='J')pro+=a[tx][ty];
		}
		vis[tx][ty]=1;
		x=tx;y=ty;
	}
	printf("pos: (%d, %d)\n",x,y);
	printf("key: %d\n", key);
	printf("hp: %d\n", hp);
	printf("protect: %d\n", pro);
	return 0;
}
