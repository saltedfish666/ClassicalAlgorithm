/*
----什么是半数集？----
以自然数6为例，首先包括其本身{6}，然后包括6与其约数构成的2位数集合{16,26,36}，最后还有两个3位数集合{126,136}。
汇总之后得出6的半数集set(6)={6,16,26,36,126,136}.
同法可得8的半数集set(8)={8，18，28，38，48，128，138，148，248，1248}
*/

#include <stdio.h>

int f(int n){
	int sum=1;
	int i;
	if(n==1)
		return 1;
	else
		for(i=1;i<=n/2;i++){
			sum += f(i);
		}
	return sum;
}

int main(){
	int n = 0;
	printf("请输入一个自然数：");
	scanf("%d",&n);
	printf("其半数集的元素个数为%d个\n",f(n));
	system("pause");
}

