#include <bits/stdc++.h>
using namespace std;
int n,m;
struct op{
	int where,w;
};
vector<op>A;
const int N=500000;
int father[N],a[N],len,reva[N],w[N],shu;
vector<pair<int,int> >b;
void print(){
	for (int i=1;i<=n;i++) a[i]=i;
	if (shu) random_shuffle(a+2,a+n+1);
	printf("%d %d\n",n,m);
	for (int i=1;i<=n;i++) reva[a[i]]=i;
	for (int i=1;i<=n;i++){
		printf("%d",w[reva[i]]); if (i==n) puts(""); else putchar(' ');
	}
	for (int i=2;i<=n;i++)
		if (rand()&1) b.push_back(make_pair(a[father[i]],a[i])); else b.push_back(make_pair(a[i],a[father[i]]));
	if (shu) random_shuffle(b.begin(),b.end());
	assert(A.size()==m);
	for (int i=0;i<b.size();i++) printf("%d %d\n",b[i].first,b[i].second);
	for (int i=0;i<A.size();i++) printf("%d %d\n",a[A[i].where],A[i].w);
}
const int lim=10000000;
vector<int> dfs(int k1,int k2){ 
	if (k1*2>k2) return {k1};
	vector<int>l=dfs(k1*2,k2);
	vector<int>r=dfs(k1*2+1,k2);
	vector<int>ans;
	for (int i=0;i<l.size();i++) ans.push_back(l[i]),ans.push_back(r[i]);
	return ans;
}
void gen1(int n){
	if (n==0) return;
	for (int i=1;i<=n;i++) a[i]=++len;
	for (int i=2;i<=n;i++) father[a[i]]=a[i/2];
	for (int i=1;i<=n;i++) w[a[i]]=rand()%lim+1;
	vector<int>x=dfs(1,n);
	for (int i=0;i<x.size();i++) A.push_back((op){a[x[i]],1});
	for (int i=x.size();i<n;i++){
		int k1=rand()%n+1,k2=rand()%lim+1;
		A.push_back((op){a[i],1});
	}
	cerr<<"fin"<<endl;
}
int C[N];
void add(int k1,int k2,int n){
	for (;k1<=n;k1+=k1&(-k1)) C[k1]+=k2;
}
int find(int k1){
	int ans=0; for (;k1;k1-=k1&(-k1)) ans+=C[k1]; return ans;
}
void gen2(int n){// cerr<<"in"<<endl;
	if (n==0) return;// cerr<<"gen2"<<endl;
	for (int i=1;i<=n;i++) a[i]=++len;
	father[a[1]]=1; for (int i=2;i<=n;i++) father[a[i]]=a[i-1];
	int m=5;
	for (int i=m+1;i<=n;i++) w[a[i]]=1;
	int pre=n-m;
	for (int i=m;i;i--) w[a[i]]=pre+1,pre+=w[a[i]];
	int num=n*2/3; int D=0; long long C[10];
	memset(C,0x00,sizeof C); //cerr<<"in"<<endl;
	for (int i=1;i<=num;i++){
		if (rand()&1){
			int k1=rand()%m+1; long long k2=D;
			for (int i=k1+1;i<=m;i++) k2+=C[i];
			k2=max(min(k2-C[k1],1ll*lim),1ll); C[k1]+=k2;
			A.push_back((op){a[k1],k2}); //cerr<<k1<<" "<<k2<<endl;
		} else {
			int k1=rand()%(n-m)+m+1; D+=2; A.push_back((op){a[k1],2});// cerr<<k1<<" "<<1<<endl;
		}	
	}
//	cerr<<"end"<<endl;
	for (int i=num+1;i<=n;i++){
		int k1=rand()%n+1,k2=rand()%lim+1; A.push_back((op){a[k1],k2});
	}
}
void gen3(int n){
	if (n==0) return;
	for (int i=1;i<=n;i++) a[i]=++len;
	father[a[1]]=1; for (int i=2;i<=n;i++) father[a[i]]=a[1];
	for (int i=1;i<=n;i++) w[a[i]]=rand()%lim+1;
	long long tot=n; int k1=rand()%n+1,k2=rand()%n+1;
	long long w1=1,w2=1;
	while (k1==k2) k2=rand()%n+1;
	int num=n*2/3;
	for (int i=1;i<=num;i++)
		if (i&1){
			long long rem=tot-w1;
			long long k3=rem-w1+1;
			assert(k3<=lim); w1+=k3; tot+=k3;
			assert(w1*2>tot);
			A.push_back((op){a[k1],k3});
		} else {
			long long rem=tot-w2;
			long long k3=rem-w2+1;
			assert(k3<=lim); w2+=k3; tot+=k3;
			assert(w2*2>tot); A.push_back((op){a[k2],k3});
		}
	for (int i=num+1;i<=n;i++){
		int k1=rand()%n+1,k2=rand()%lim+1; A.push_back((op){a[k1],k2});
	}
}
void gen4(int n){
	if (n==0) return;
	for (int i=1;i<=n;i++) a[i]=++len; father[a[1]]=1;
	for (int i=2;i<=n;i++) father[a[i]]=a[rand()%(i-1)+1];
	for (int i=1;i<=n;i++) w[a[i]]=rand()%lim+1;
}
int main(int argc,char **argv){
	cerr<<argc<<endl;
	srand(atoi(argv[2]));
	n=atoi(argv[1]); m=n-rand()%100; m=0;
	int num0=atoi(argv[3]),num1=atoi(argv[4]),num2=atoi(argv[5]); //cerr<<num0<<" "<<num1<<" "<<num2<<endl;
	int rem=n-num0-num1-num2; //cerr<<rem<<endl;
	shu=atoi(argv[6]);
	gen1(num0); gen2(num1); gen3(num2); gen4(rem);
	while (A.size()<m){
		int k1=rand()%n+1,k2=rand()%lim+1;
		A.push_back((op){k1,k2});
	}
	while (A.size()>m) A.pop_back();
	print();
}
