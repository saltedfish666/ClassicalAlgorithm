#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

long long multiply(long long x,long long y,int n);

void enter(){
	long long X,Y;
	int n=0;
    printf("请输入两个大整数：\nX=");
    scanf("%lld",&X);
    printf("Y=");
    scanf("%lld",&Y);
    printf("请输入两个大整数的长度：n=");
    scanf("%d",&n);
 
    long long sum = multiply(X, Y, n);
    printf("普通乘法 X*Y=%lld*%lld=%lld\n",X,Y,X*Y);
    printf("分治乘法 X*Y=%lld*%lld=%lld\n",X,Y,sum);
}

long long multiply(long long x,long long y,int n){
	if(x==0||y==0)
		return 0;
	else if(n==1)
		return x*y;
	else{
		long long a=(long long)(x/pow(10,n/2));
		long long b=(x%(long long)pow(10,n/2));
		long long c=(long long)(y/pow(10,n/2));
		long long d=(y%(long long)pow(10,n/2));
		
		long long ac = multiply(a, c, n / 2);
        long long bd = multiply(b, d, n / 2);
        long long abcd = multiply((a - b), (d - c), n / 2) + ac + bd;
        return (long long)(ac * pow(10, n) + abcd * pow(10, n / 2) + bd);
	}
}

int main() {
	enter();
	//system("pause"); 
	return 0;
}
