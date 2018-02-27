#include<cstdio>
#include<algorithm>
using namespace std;

int num[400012],fir[400012],sec[400012],numf[400012],nums[400012];
int n,m;
char s[10012];

struct node{
	int a,b;
	bool operator<(const node &aa) const{
	  return a>aa.a||(a==aa.a&&b<aa.b);
	}
}q[12];

void build(int o,int l,int r){
	if (l==r)
	{
	  scanf("%d",&num[o]);
	  fir[o]=-2147483640;
	  sec[o]=-2147483640;
	  numf[o]=0;
	  nums[o]=0;
	  return ;
	}
	int mid=(l+r)/2;
	build(o*2,l,mid);
	build(o*2+1,mid+1,r);
	q[1].a=fir[o*2],q[1].b=numf[o*2];
	q[2].a=sec[o*2],q[2].b=nums[o*2];
	q[3].a=fir[o*2+1],q[3].b=numf[o*2+1];
	q[4].a=sec[o*2+1],q[4].b=nums[o*2+1];
	sort(q+1,q+1+4);
	fir[o]=q[1].a,numf[o]=q[1].b;
	sec[o]=q[2].a,nums[o]=q[2].b;
}

void add(int o,int l,int r,int x,int v){
	if (l==r)
	{
	  fir[o]=v-num[o];
	  num[o]=v;
	  numf[o]=l;
	  return ;
	}
	int mid=(l+r)/2;
	if (x<=mid)
	  add(o*2,l,mid,x,v);
	else
	  add(o*2+1,mid+1,r,x,v);
	q[1].a=fir[o*2],q[1].b=numf[o*2];
	q[2].a=sec[o*2],q[2].b=nums[o*2];
	q[3].a=fir[o*2+1],q[3].b=numf[o*2+1];
	q[4].a=sec[o*2+1],q[4].b=nums[o*2+1];
	sort(q+1,q+1+4);
	fir[o]=q[1].a,numf[o]=q[1].b;
	sec[o]=q[2].a,nums[o]=q[2].b;
}

int main(){
	freopen("invest.in","r",stdin);
	freopen("invest.out","w",stdout);
	scanf("%d",&n);
	build(1,1,n);
	while (true)
	{
	  char ch=getchar();
	  while (ch!='R'&&ch!='E'&&!(ch>='0'&&ch<='9'))
	    ch=getchar();
	  if (ch=='R')
	  {
	  	scanf("%s",s);
	  	printf("%d %d\n",numf[1],nums[1]);
	  	continue;
	  }
	  if (ch=='E')
	    break;
	  if (ch>='0'&&ch<='9')
	  {
	  	int x=ch-'0',v=0;
	  	ch=getchar();
	  	while (ch>='0'&&ch<='9')
	  	{
	  	  x=(x<<1)+(x<<3)+(ch^'0');
	  	  ch=getchar();
	    }
	    scanf("%d",&v);
	    add(1,1,n,x,v);
	  }
	}
	/*scanf("%d",&m);
	while (m--)
	{
	  int p,x,v;
	  scanf("%d",&p);
	  if (p==1)
	  {
	  	scanf("%d%d",&x,&v);
	  	add(1,1,n,x,v);
	  }
	  if (p==2)
	  	printf("%d %d\n",numf[1],nums[1]);
	  if (p==3)
	    break;
	}*/
	
	return 0;
}
