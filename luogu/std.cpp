#include<cstdio>
#include<algorithm>
using namespace std;const int N=1048580;typedef double db;db eps=1e-10;
int n;db a[N];db res;int up;int siz[N];
int main()
{
	scanf("%d",&n);up=(1<<n);
	for(int i=0;i<up;i++)scanf("%lf",&a[i]);
	for(int k=1;k<up;k<<=1)//\\FMT板子
		for(int s=0;s<up;s+=k<<1)
			for(int i=s;i<s+k;i++)
			{db a0=a[i];db a1=a[i+k];a[i]=a0;a[i+k]=a0+a1;}
	for(int i=0;i<up;i++)printf("%.2lf ",a[i]);
	for(int i=1;i<up;i++){siz[i]+=siz[i>>1]+(i&1);}
	for(int i=1;i<up;i++)//\\min-max容斥
	{
		if(1-a[(up-1)^i]<eps){printf("INF\n");return 0;}
		db ex=1/(1-a[(up-1)^i]);if(siz[i]%2){res+=ex;}else {res-=ex;}
	}printf("%.10lf",res);return 0;//\\拜拜程序~
}
