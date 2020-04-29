#include <stdio.h>
#pragma warning(disable:4996)
#define subm(a,b)((a)-(b))
#define cubem(a)((a)*(a)*(a))
#define minm(a,b)((a<=b)?(a):(b))
#define oddm(a)((a%2==1)?1:0)

int subf(int a, int b){
	return  a - b;
}
int cubef(int a){
	return a*a*a;
}
int minf(int a, int b){
	if(a<=b) {
		return a;
	}else{
		return b;
	}
}
int oddf(int a){
	if(a%2 ==1){
		return 1;
	}else{
		return 0;
	}
}
int main(){
	int a; int b;
	a =5; b =7; 
	subf(a,b);
	printf("subf(a,b)= %d\n",subf(a,b));
	a=5;b=7;
	subm(a,b);
	printf("subm(a,b)= %d\n",subm(a,b));
	a=5;b=7;
	subf(a++,b--);
	printf("subf(a++,b--)= %d\n",subf(a++,b--));
	a=5; b=7;
	subm(a++,b--);
	printf("subm(a++,b--)= %d\n",subm(a++,b--));

	a =5; b = 7;
	cubef(a);
	printf("cubef(a)= %d\n",cubef(a));
	a=5;b=7;
	cubem(a);
	printf("cubem(a)= %d\n",cubem(a));
	a=5;b=7;
	cubef(--a);
	printf("cubef(--a)= %d\n",cubef(--a));
	a=5 ;b=7;
	cubem(--a);
	printf("cubem(--a)= %d\n",cubem(--a));

	a = 5; b =7;
	minf(a,b);
	printf("minf(a,b)= %d\n",minf(a,b));
	a=5;b=7;
	minm(a,b);
	printf("minm(a,b)= %d\n",minm(a,b));
	a=5;b=7;
	minf(--a,--b);
	printf("minf(--a,--b)= %d\n",minf(--a,--b));
	a=5;b=7;
	minm(--a,--b);
	printf("minm(--a,--b)= %d\n",minm(--a,--b));

	a=5;b=7;
	oddf(a);
	printf("oddf(a)= %d\n",oddf(a));
	a=5;b=7;
	oddm(a);
	printf("oddm(a)= %d\n",oddm(a));
	a=5;b=7;
	oddf(a++);
	a=5;b=7;
	printf("oddf(a++)= %d\n",oddf(a++));
	oddm(a++);
	printf("oddm(a++)= %d\n",oddm(a++));
	return 0;
}
