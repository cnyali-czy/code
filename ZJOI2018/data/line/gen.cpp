#include <bits/stdc++.h>
using namespace std;
struct bian{
	int u,v;
}A[6000];
int n=5000,K;
int a[6000],len;
void gentree(){
	for (int i=2;i<=1000;i++){
		int num=rand()%min(i-1,10)+1;
		A[++len]=(bian){num,i};
	}
	int K=rand()%1000+1;
	for (int i=1001;i<=3000;i++) A[++len]=(bian){K,i};
	int pre=rand()%10+1;
	for (int i=3001;i<=4000;i++){
		A[++len]=(bian){pre,i}; pre=i;
	}
	for (int i=4001;i<=n;i++){
		int num=rand()%(i-1)+1;
		A[++len]=(bian){num,i};
	}
}
int main(int argc,char** argv){
	K=atoi(argv[1]); 
	srand(atoi(argv[2]));
	n-=rand()%100; gentree();
	random_shuffle(A+1,A+len+1);
	for (int i=1;i<=n;i++) a[i]=i;
	random_shuffle(a+1,a+n+1);
	for (int i=1;i<=n;i++)
		if (rand()&1) swap(A[i].u,A[i].v);
	printf("%d %d\n",n,K);
	for (int i=1;i<n;i++) printf("%d %d\n",a[A[i].u],a[A[i].v]);
	return 0;
}
