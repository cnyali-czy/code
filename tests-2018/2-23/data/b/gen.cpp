#include<bits/stdc++.h>
using namespace std;
#define work system(s)

char s[100];
const int l[]={6,7,8,16,18,20,90,100,300,360,390,8e2,8e2,8e2,8e2,950,950,950,950,1e3};
const int r[]={6,7,8,17,19,20,99,100,350,385,400,1e3,1e3,1e3,1e3,1e3,1e3,1e3,1e3,1e3};
const int type[]={0,0,0,0,0,0,0,0,0,0,0,1,2,3,4,5,0,0,0,0};

int main(){
	for(int t=1;t<=20;++t){
		sprintf(s,"./data %d %d %d %d\n",l[t-1],r[t-1],type[t-1],time(NULL)+t*t*t*t);
		work;
		sprintf(s,"./b");
		work;
		sprintf(s,"rm b%d.in",t);
		work;
		sprintf(s,"rm b%d.ans",t);
		work;
		sprintf(s,"mv b.in b%d.in",t);
		work;
		sprintf(s,"mv b.out b%d.ans",t);
		work;
		cerr<<t<<endl;
	}
	return 0;
}
