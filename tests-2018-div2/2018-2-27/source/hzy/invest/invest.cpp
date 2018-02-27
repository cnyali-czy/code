#include<bits/stdc++.h>
using namespace std;
int b[100010];
char s[20];
struct node
{
	int bh,k,pre,aft;
}a[100010],c;
void read(int &x)
{
	x=0;
	bool f=0;
	char c=getchar();
	while(c!='-' && (c<'0' || c>'9'))
		c=getchar();
	if(c=='-')
	{
		f=1;
		c=getchar();
	}
	while(c>='0' && c<='9')
	{
		x=x*10+c-48;
		c=getchar();
	}
	if(f)
		x=-x;
}
int main()
{
	int n;
	freopen("invest.in","r",stdin);
	freopen("invest.out","w",stdout);
	read(n);
	for(register int i=1;i<=n;i++)
	{
		read(a[i].aft);
		b[i]=i;
		a[i].bh=i;
	}
	for(;;)
	{
		scanf("%s",&s);
		if(s[0]=='E')
			return 0;
		if(s[0]=='R')
		{
			printf("%d",a[1].bh);
			if(a[2].k>a[3].k || a[2].k==a[3].k && a[2].bh<a[3].bh)
				printf(" %d\n",a[2].bh);
			else
				printf(" %d\n",a[3].bh);
		}
		if(s[0]>='0' && s[0]<='9')
		{
			int x=0,y,i=0;
			while(s[i]>='0' && s[i]<='9')
				x=x*10+s[i++]-48;
			read(y);
			a[b[x]].pre=a[b[x]].aft;
			a[b[x]].aft=y;
			a[b[x]].k=a[b[x]].aft-a[b[x]].pre;
			int u=b[x];
			while(u*2<=n && (a[u].k<a[u*2].k || a[u].k==a[u*2].k && a[u].bh>a[u*2].bh) || u*2+1<=n && (a[u].k<a[u*2+1].k || a[u].k==a[u*2+1].k && a[u].bh>a[u*2+1].bh))
			{
				int v=u*2;
				if(v+1<=n && (a[v].k<a[v+1].k || a[v].k==a[v+1].k && a[v].bh>a[v+1].bh))
					v++;
				c=a[u];
				a[u]=a[v];
				a[v]=c;
				u=v;
			}
			while(u>1 && (a[u].k>a[u/2].k || a[u].k==a[u/2].k && a[u].bh<a[u/2].bh))
			{
				c=a[u/2];
				a[u/2]=a[u];
				a[u]=c;
				u/=2;
			}
			b[x]=u;
		}
	}
	return 0;
}
