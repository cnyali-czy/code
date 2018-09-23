#include<cstdio>
#include<cmath>
#include<cstdlib>
#include<algorithm>
#include<cstring>
#include<queue>
using namespace std;
const int mod=1e9+9;

int n,h;

int now,old;
int f[2][2][33][33][33];

#define nex(x) ((x)==h ? h:(x)+1)
void MOD(int &x) 
{
	if (x>=mod) x-=mod;
}
int main()
{
//	freopen("ladder.in","r",stdin);
//	freopen("ladder.out","w",stdout);
	
	scanf("%d%d",&n,&h);
	
	old=0,now=1;
	f[old][1][0][0][0]=1;
	
	int tmp;
	
	for (int i=1;i<=n;i++)
	{
		for (int j=0;j<=1;j++)
			for (int x=0;x<=h;x++)
				for (int y=0;y<=h;y++)
					for (int z=0;z<=h;z++)
					if (tmp=f[old][j][x][y][z])
					{
						MOD(f[now][j][nex(x)][nex(y)][nex(z)]+=tmp);
						
						MOD(f[now][x<h][nex(y)][nex(z)][j==1?1:h]+=tmp);
						MOD(f[now][y<h][nex(x)][nex(z)][j==1?1:h]+=tmp);
						MOD(f[now][z<h][nex(x)][nex(y)][j==1?1:h]+=tmp);
						
						f[old][j][x][y][z]=0;
					}
		swap(now,old);
	}
	
	int ans=0;
	for (int j=0;j<=1;j++)
		for (int x=0;x<=h;x++)
			for (int y=0;y<=h;y++)
				for (int z=0;z<=h;z++) 
				if (j==1||x<h||y<h||z<h)
					ans+=f[old][j][x][y][z],MOD(ans);
	printf("%d",ans);
	return 0;
}
