#include<bits/stdc++.h>
using namespace std;
int e,to[33343],begin[787],next[33343],_w[33343],t[787],q[33343],b[787],c[787],n,m;
void add(int x,int y,int z)
{
	to[++e]=y;
	next[e]=begin[x];
	begin[x]=e;
	_w[e]=z;
}
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
int js(int x,int y,int z)
{
	if(y==n+1)
		return 0;
	if((t[x]+_w[z])%(b[y]+c[y])>=c[y])
		return b[y]-(t[x]+_w[z])%(b[y]+c[y])+c[y];
	else
		return 0;
}
int main()
{
	freopen("d.in","r",stdin);
	freopen("d.out","w",stdout);
	for(;;)
	{
		scanf("%d",&n);
		if(feof(stdin))
			return 0;
		memset(to,0,sizeof(to));
		memset(b,0,sizeof(b));
		memset(c,0,sizeof(c));
		memset(begin,0,sizeof(begin));
		memset(q,0,sizeof(q));
		memset(_w,0,sizeof(_w));
		e=0;
		for(register int i=1;i<=n;i++)
		{
			read(b[i]);
			read(c[i]);
		}
		read(m);
		for(register int i=1;i<=m;i++)
		{
			int x,y,z;
			read(x);
			read(y);
			read(z);
			add(x+1,y+1,z);
		}
		int h=0,l=1;
		q[1]=1;
		t[1]=0;
		for(register int i=2;i<=n+1;i++)
			t[i]=1000000000;
		while(h<l)
		{
			h++;
			for(register int i=begin[q[h]];i;i=next[i])
				if(t[to[i]]>js(q[h],to[i],i)+t[q[h]]+_w[i])
				{
					t[to[i]]=js(q[h],to[i],i)+t[q[h]]+_w[i];
					q[++l]=to[i];
				}
		}
		printf("%d\n",t[n+1]);
	}
	return 0;
}
