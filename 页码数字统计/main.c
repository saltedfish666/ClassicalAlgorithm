#include <stdio.h>
#include <stdlib.h>

static int r[10]={0};

int count(int num){
	while(num>0){
		r[num%10]++;
		num/=10;
	}
}

int main() {
	int num,i;
	printf("������ҳ����1-9999����");
	scanf("%d",&num);
	for(i=1;i<=num;i++){
		count(i);
	}
	for(i=0;i<10;i++){
		printf("%d�ĸ���Ϊ��%d\n",i,r[i]);
	}
	system("pause");
}
