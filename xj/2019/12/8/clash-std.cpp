/****************************************************************
 *   Author: huhao
 *   Email: 826538400@qq.com
 *   Create time: 2019-12-08 10:52:44
 ****************************************************************/
#include<stdio.h>
#include<string.h>
#include<math.h>
#include<algorithm>
#define fr(i,a,b) for(int i=(a),end_##i=(b);i<=end_##i;i++)
#define fd(i,a,b) for(int i=(a),end_##i=(b);i>=end_##i;i--)
int read()
{
	int r=0,t=1,c=getchar();
	while(c<'0'||c>'9')
	{
		t=c=='-'?-1:1;
		c=getchar();
	}
	while(c>='0'&&c<='9')
	{
		r=(r<<3)+(r<<1)+(c^48);
		c=getchar();
	}
	return r*t;
}
#include<vector>
#define arr std::vector
#define pdi std::pair<double,int>
const int N=100010,K=120;
const double eps=1e-12;
int n,k,q,m,typ;
int x[N],y[N],X[N],Y[N],op[N],ans;
arr<double> r[K];//cos
arr<pdi> a;
double dis(double x,double y,double X,double Y)
{
	return sqrt((x-X)*(x-X)+(y-Y)*(y-Y));
}
double Cos(double x,double y,double X,double Y)
{
	return (X-x)/dis(x,y,X,Y);
}
int main()
{
	n=read(); k=read(); q=read(); typ=read();
	fr(i,1,n){ x[i]=read(); y[i]=read(); }
	fr(i,1,k)
	{
		int a=read(),b=read(),c=read();
		m++; X[m]=a; Y[m]=c; op[m]=-1;
		m++; X[m]=b; Y[m]=c; op[m]=1;
	}
	fr(i,1,n)
	{
		a.clear();
		fr(j,1,m) if(Y[j]<y[i]) a.push_back(pdi(Cos(x[i],y[i],X[j],Y[j])+op[j]*eps,j));
		sort(a.begin(),a.end());
		//      printf("%d\n",i);
		//      for(auto i:a) printf("%lf %d\n",i.first,op[i.second]);
		int s=0;
		fr(j,0,a.size()-1)
		{
			if(!s) r[a[j].second].push_back(a[j].first);
			s+=op[a[j].second];
			if(!s) r[a[j].second].push_back(a[j].first);
		}
	}
	fr(i,1,m) sort(r[i].begin(),r[i].end());
	/*  fr(i,1,m)
		{
		printf("%d %d %d\n",x[i],y[i],op[i]);
		for(auto j:r[i]) printf("%lf ",j);
		putchar(10);
		}*/
	while(q--)
	{
		int x_=read()^(typ*ans),y_=read()^(typ*ans);
		ans=n;
		fr(i,1,m) ans+=op[i]*(upper_bound(r[i].begin(),r[i].end(),Cos(X[i],Y[i],x_,y_))-r[i].begin());
		printf("%d\n",ans);
	}
	return 0;
}
