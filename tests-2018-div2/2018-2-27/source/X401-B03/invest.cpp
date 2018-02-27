#include<bits/stdc++.h>
#define N 100100
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
int n;
int a[N],sum[N];
struct node
{
	int fir,sec;
	bool operator <(const node &ss)const
	{
		if(fir!=ss.fir)return fir<ss.fir;
		return sec>ss.sec;
	}
};
multiset<node>s;
int main()
{
	freopen("invest.in","r",stdin);
	freopen("invest.out","w",stdout);
	read(n);
	for(int i=1;i<=n;i++)read(a[i]),s.insert((node){0,i});
	char ss[30];
	set<node>::iterator it;
	while(1)
	{
		scanf("%s",ss+1);
		if(ss[1]=='E')return 0;
		if(isdigit(ss[1]))
		{
			static int x,y;x=0;
			static int len;len=strlen(ss+1);
			for(int i=1;i<=len;i++)x=(x<<1)+(x<<3)+(ss[i]-48);
			read(y);
			s.erase((node){sum[x],x});
			s.insert((node){y-a[x],x});	
			sum[x]=y-a[x];
			a[x]=y;
		}
		else if(ss[1]=='R')
		{
			it=--s.end();
			printf("%d ",it->sec);--it;
			printf("%d\n",it->sec);
		}
	}
	return 0;
}
