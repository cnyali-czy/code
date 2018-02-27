#include<bits/stdc++.h>
#define N 77777
using namespace std;
inline void read(int &x)
{
	x=0;
	static int p;p=1;
	static char c;c=getchar();
	while(!isdigit(c)){if(c=='-')p=-1;c=getchar();}
	while(isdigit(c)) {x=(x<<1)+(x<<3)+(c-48);c=getchar();}
	x*=p;
}
int n,m;
int c[N],b[N];
int to[N],beg[1000],nex[N],w[N],e;
int vis[N],dis[N];
const int inf=0x7f7f7f7f;
void add(int x,int y,int z)
{
	to[++e]=y;
	nex[e]=beg[x];
	beg[x]=e;
	w[e]=z;
}
void spfa()
{
	for(int i=1;i<=n;i++)dis[i]=0x7f7f7f7f;
	queue<int>q;
	q.push(1);vis[1]=1;dis[1]=0;
	while(!q.empty())
	{
		int k=q.front();
		q.pop();
		vis[k]=0;
		for(int i=beg[k];i;i=nex[i])
		{
			int y=to[i];
			int now=(dis[k]+w[i])%(c[y]+b[y]);
			if(now>=0&&now<c[y])
			{
				if(dis[y]>dis[k]+w[i])
				{
					dis[y]=dis[k]+w[i];
					if(!vis[y]){vis[y]=1;q.push(y);}
				}
			}
			else 
			{
				if(dis[y]>dis[k]+w[i]+(b[y]-(now-c[y])))
				{
					dis[y]=dis[k]+w[i]+(b[y]-(now-c[y]));
					if(!vis[y]){vis[y]=1;q.push(y);}
				}
			}
		}
	}
	printf("%d\n",dis[n]);
}
int main()
{
	freopen("d.in","r",stdin);
	freopen("d.out","w",stdout);
	read(n);n++;
	for(int i=1;i<=n-1;i++)read(b[i]),read(c[i]);
	c[n]=b[n]=inf;
	read(m);
	for(int i=1;i<=m;i++)
	{
		static int x,y,z;
		read(x);read(y);read(z);
		x++;y++;
		add(x,y,z);
		add(y,x,z);
	}
	spfa();
	return 0;
}
