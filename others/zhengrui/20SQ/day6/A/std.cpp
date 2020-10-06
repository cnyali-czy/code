
#include <cstdio>
#include <vector>
using namespace std;
const int MAXN=100005;
const int MAXK=85;
const int P=998244353;
int n, m, k, l;
int c[MAXK][MAXK], s[MAXK][MAXK];
bool b[MAXN];
vector<int> G[MAXN];
int f[MAXN][2], g[MAXK];
void DFS(int u, int fa, int x)
{
	f[u][0]=1, f[u][1]=!b[u];
	for (int v: G[u]) if (v!=fa)
	{
		DFS(v, u, x);
		f[u][0]=(1ll*(m-x-1)*f[v][0]+1ll*x*f[v][1])%P*f[u][0]%P;
		f[u][1]=(1ll*(m-x)*f[v][0]+1ll*(x-1)*f[v][1])%P*f[u][1]%P;
	}
}
int main()
{
	freopen("A.in", "r", stdin);
	freopen("std.out", "w", stdout);
	scanf("%d%d%d%d", &n, &m, &k, &l);
	c[0][0]=s[0][0]=1;
	for (int i=1; i<=k; i++)
	{
		c[i][0]=1;
		for (int j=1; j<=i; j++)
		{
			c[i][j]=(c[i-1][j]+c[i-1][j-1])%P;
			s[i][j]=(1ll*j*s[i-1][j]+s[i-1][j-1])%P;
		}
	}
	for (int i=1, x; i<=l; i++)
		scanf("%d", &x), b[x]=1;
	for (int i=1, u, v; i<n; i++)
	{
		scanf("%d%d", &u, &v);
		G[u].push_back(v);
		G[v].push_back(u);
	}
	for (int i=0; i<=k; i++)
		DFS(1, 0, i), g[i]=(1ll*(m-i)*f[1][0]+1ll*i*f[1][1])%P;
	int ans=0;
	for (int i=0, t=1; i<=k; t=1ll*t*(m-i)%P, i++)
	{
		int sum=0;
		for (int j=0; j<=i; j++)
			sum=(sum+(j&1?-1ll:1ll)*c[i][j]*g[j])%P;
		ans=(ans+1ll*s[k][i]*t%P*(sum+P))%P;
	}
	printf("%d\n", ans);
	return 0;
}
