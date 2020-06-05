#include <cstdio>
using namespace std;

typedef long long LL;
typedef long double ld;
const int N=233;
ld C[N][N],D[N][N],F[N];
int n,m,a[N],b[N],c[N],p[N];
LL k[N];

LL gcd(LL a,LL b) {return (b==0 ? a : gcd(b,a%b));}
LL lcm(LL a,LL b) {return a/gcd(a,b)*b;}

int main() {
	FILE* IN=fopen("secret.in","r");
	
	fscanf(IN,"%d%d",&n,&m);
	for(int i=1;i<=10;++i) fscanf(IN,"%d%Lf",&p[i],&F[i]);
	for(int i=1;i<=n;++i) {
		for(int j=1;j<=10;++j) fscanf(IN,"%Lf",&C[i][j]);
		for(int j=1;j<=10;++j) fscanf(IN,"%Lf",&D[i][j]);
	}
	ld ans=1;
	for(int i=1;i<=n;++i) {
		scanf("%lld",&k[i]);
		for(int j=1;j<=10;++j) {
			if((k[i]%p[j])==0) ans*=C[i][j]; else ans*=D[i][j];
		}
	}
	for(int i=1,a,b,c;i<=m;++i) {
		fscanf(IN,"%d%d%d",&a,&b,&c);
		if((lcm(k[a],k[b])%p[c])==0&&(gcd(k[a],k[b])%p[c])!=0) ans*=F[c];
	}
	printf("%.5Lf\n",ans);
	
	return 0;
}

