#include<bits/stdc++.h>
#define de fprintf(stderr,"on-%d\n",__LINE__)
#define mk make_pair
#define fi first
#define se second
#define pdd pair<double,double>
#define fr(i,a,b) for(int i(a),end##i(b);i<=end##i;i++)
#define fd(i,a,b) for(int i(a),end##i(b);i>=end##i;i--)
using namespace std;
const int maxn=2000+5;
const double eps=1e-12,PI=3.1415926535898;
int n;
pair<pdd,double> a[maxn];
pdd operator +(pdd x,pdd y){
	return mk(x.fi+y.fi,x.se+y.se);   	
}
pdd operator -(pdd x,pdd y){
	return mk(x.fi-y.fi,x.se-y.se);   	
}
double Z(pdd x){
	return x.fi*x.fi+x.se*x.se;	
}
pdd E(pdd x){
	double s=sqrt(Z(x));
	return pdd(x.fi/s,x.se/s);	
}
double upd(double x){
	while(x<0)x+=2*PI;
	while(x>=2*PI)x-=2*PI;
	return x;
}
double angle(pdd x){
	return upd(atan2(x.se,x.fi));
}
double sq(double x){
	return x*x;
}
pdd st[maxn];
int top;
void insert(pdd x){
	//fprintf(stderr,"%.2lf %.2lf\n",x.fi,x.se);
	if(x.fi>x.se){
		st[++top]=mk(x.fi,2*PI);
		st[++top]=mk(0,x.se);
	}
	else st[++top]=x; 
}
double S(pdd x,double r){
	return .5*((x.se-x.fi)-sin(x.se-x.fi))*r*r;
}
double ans;
void print(pdd x){
	printf("(%lf,%lf)\n",x.fi,x.se);
}
bool check(pdd x,pdd y,double r1,double r2){
	double d=sqrt(Z(y-x));
	return d-r2<r1-eps&&r1+eps<d+r2&&r2+eps<d+r1; 
}
bool pd[maxn];
int main(){
	freopen("2178-new.in","r",stdin);
	freopen("std1.out","w",stdout);
	cin>>n;
	fr(i,1,n){
		scanf("%lf%lf%lf",&a[i].fi.fi,&a[i].fi.se,&a[i].se);
		fr(j,1,i-1)if(a[i].fi.fi==a[j].fi.fi&&a[i].fi.se==a[j].fi.se&&a[i].se==a[j].se){
			i--;n--;endi--;
			break;
		}
	}
	fr(i,1,n){
		fr(j,1,n)if(j!=i)if(sqrt(Z(a[j].fi-a[i].fi))+a[i].se<a[j].se+eps){
			pd[i]=1;
			break;	
		}
	}
	fr(i,1,n)if(!pd[i]){
		printf("%.2lf %.2lf %.2lf\n", a[i].fi.fi, a[i].fi.se, a[i].se);
		//printf("%lf %lf %lf\n",a[i].fi.fi,a[i].fi.se,a[i].se);
		top=0;
		fr(j,1,n)if(j!=i&&Z(a[j].fi-a[i].fi)>eps&&check(a[i].fi,a[j].fi,a[i].se,a[j].se)&&!pd[j]){
			double d=Z(a[j].fi-a[i].fi);
			//assert(d>eps);
			double T=angle(a[j].fi-a[i].fi),A=acos((sq(a[i].se)+d-sq(a[j].se))/(2*sqrt(d)*a[i].se));	
			//print(a[j].fi-a[i].fi);
//			printf("%d %d %.2lf %.2lf\n", i, j, upd(T - A), upd(T + A));
			insert(mk(upd(T-A),upd(T+A)));	
		}
		st[++top]=mk(2*PI,2*PI);
		sort(st+1,st+top+1);
		double last=0;
		fr(j,1,top){
			if(last<st[j].fi){
				double &l=last,&r=st[j].fi;
				printf("%.2lf %.2lf\n", l, r);
				ans+=S(mk(l,r),a[i].se)+.5*(2.*a[i].fi.se+a[i].se*(sin(l)+sin(r)))*a[i].se*(cos(l)-cos(r));
			}
			last=max(last,st[j].se);	
		}
	}
	printf("%.3lf\n",ans);
	return 0;
}
