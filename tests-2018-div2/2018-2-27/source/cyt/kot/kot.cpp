#include<bits/stdc++.h>
using namespace std;
char s[500010];
int i,j,k,l;
char a1[21]={'`','1','2','3','4','5','6','7','8','9','0','-','='};
char a2[51]={'Q','W','E','R','T','Y','U','I','O','P','[',']','q','w','e','r','t','y','u','i','o','p'};
char a3[51]={'A','S','D','F','G','H','J','K','L',';','a','s','d','f','g','h','j','k','l'};
char a4[51]={'Z','X','C','V','B','N','M',',','.','/','z','x','c','v','b','n','m'};
char a5[21]={' '};
int main()
{
	freopen("kot.in","r",stdin);
	freopen("kot.out","w",stdout);
	gets(s);
	for(i=0;i<strlen(s);i++){
	int f=0;
	if(s[i]==92){f=1;printf("2");}
	if(s[i]==39){f=1;printf("3");}
	if(f==1)continue;
	 for(j=0;j<strlen(a1);j++){
	 if(a1[j]==s[i]){f=1;printf("1");break;}
	 }
	 if(f==1)continue;
	 
	 for(j=0;j<strlen(a2);j++){
	 if(a2[j]==s[i]){f=1;printf("2");break;}
	 }
	 if(f==1)continue;
	 
	 for(j=0;j<strlen(a3);j++){
	 if(a3[j]==s[i]){f=1;printf("3");break;}
	 }
	 if(f==1)continue;
	 
	 for(j=0;j<strlen(a4);j++){
	 if(a4[j]==s[i]){f=1;printf("4");break;}
	 }
	 if(f==1)continue;
	 
	 if(s[i]==' ')printf("5");
	}
	return 0;
}
